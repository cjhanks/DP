#ifndef SPARSE_MATRIX_HH_
#define SPARSE_MATRIX_HH_

#include <cstring>
#include <map>
#include <utility>

#include "matrix.hh"

template <typename Type_>
class COOMatrix {
  using Coordinate = std::pair<std::size_t, std::size_t>;

 public:
  using Type = Type_;

  explicit COOMatrix(const Matrix2D<Type>& old_mat)
   : rows(old_mat.Rows()),
     cols(old_mat.Cols())
  {
    static Type identity = {};
    for (std::size_t r = 0; r < old_mat.Rows(); ++r) {
      for (std::size_t c = 0; c < old_mat.Cols(); ++c) {
        const auto& val = old_mat.At(r, c);
        if (val != identity) {
          At(r, c) = val;
        }
      }
    }
  }

  COOMatrix(std::size_t rows, std::size_t cols)
   : rows(rows),
     cols(cols)
  {}

  COOMatrix()
   : COOMatrix(0, 0) {}

  Type&
  At(std::size_t row, std::size_t col) {
    assert(row < rows);
    assert(col < cols);
    return data[std::make_pair(row, col)];
  }

  const Type&
  At(std::size_t row, std::size_t col) const {
    assert(row < rows);
    assert(col < cols);
    const auto& elem = data.find(std::make_pair(row, col));
    if (elem == data.end()) {
      static Type zero = {};
      return zero;
    } else {
      return elem.second;
    }
  }

  std::size_t
  Rows() const {
    return rows;
  }

  std::size_t
  Cols() const {
    return cols;
  }

 private:
  std::size_t rows;
  std::size_t cols;
  std::map<Coordinate, Type> data;
};

// ---------------------------------------------------------------- //

enum class ColSparse {
  ROW = 1,
  COL = 2
};

template <typename Type, ColSparse SparseOrder = ColSparse::ROW>
class CSRMatrix {
 public:
  explicit CSRMatrix(const Matrix2D<Type>& old)
    : rows(old.Rows()),
      cols(old.Cols())
  {
    if (SparseOrder == ColSparse::ROW) {
      for (std::size_t maj = 0; maj < old.Rows(); ++maj) {
        std::size_t offset_r = min_offset.size();
        maj_offset.push_back(offset_r);

        for (std::size_t min = 0; min < old.Cols(); ++min) {
          static Type identity = {};
          const auto& val = old.At(maj, min);
          if (val != identity) {
            min_offset.push_back(min);
            data.push_back(val);
          }
        }
      }
    } else {
      for (std::size_t maj = 0; maj < old.Cols(); ++maj) {
        std::size_t offset_r = min_offset.size();
        maj_offset.push_back(offset_r);

        for (std::size_t min = 0; min < old.Rows(); ++min) {
          static Type identity = {};
          const auto& val = old.At(min, maj);
          if (val != identity) {
            min_offset.push_back(min);
            data.push_back(val);
          }
        }
      }
    }
  }

  const Type&
  At(std::size_t row, std::size_t col) const {
    assert(row < rows);
    assert(col < cols);

    std::size_t maj;
    std::size_t min;
    if (SparseOrder == ColSparse::ROW) {
      maj = row;
      min = col;
    } else {
      maj = col;
      min = row;
    }

    std::size_t head = maj_offset[maj];
    std::size_t tail = (maj == (maj - 1)) ? head : maj_offset[maj + 1];
    std::size_t curr = head;

    while (min_offset[curr] != min) {
      curr = head + (tail - head) / 2;
      if (min_offset[curr] < min) {
        head = curr;
      } else
      if (min_offset[curr] > min) {
        tail = curr;;
      } else {
        break;
      }
    }

    if (min_offset[curr] == min) {
      return data[curr];
    } else {
      static Type identity = {};
      return identity;
    }
  }

 private:
  std::size_t rows;
  std::size_t cols;

  std::vector<std::size_t> maj_offset;
  std::vector<std::size_t> min_offset;
  std::vector<Type>        data;
};

// ---------------------------------------------------------------- //

template <typename Type>
class BSRMatrix {
 public:
  BSRMatrix(const Matrix2D<Type>& old, std::size_t block_size)
    : rows(old.Rows()),
      cols(old.Cols()),
      blks(block_size)
  {
    assert(rows % blks == 0);
    assert(cols % blks == 0);

    // Figure out which blocks will be occupied.
    std::size_t block_count = 0;
    Matrix2D<bool> grid_occupancy(
        old.Rows() / blks,
        old.Cols() / blks,
        false
    );

    for (std::size_t r = 0; r < old.Rows(); r += blks) {
      for (std::size_t c = 0; c < old.Cols(); c += blks) {
        // Look in inner loop.
        for (std::size_t i = 0; i < blks; ++i) {
          for (std::size_t j = 0; j < blks; ++j) {
            const auto val = old.At(r + i, c + j);
            if (val != Type(0)) {
              grid_occupancy.Set(r / blks, c / blks, true);
              ++block_count;
              goto exit_inner;
            }
          }
        }

exit_inner:
        continue;
      }
    }

    // Create the BSR structures.
    data.resize(block_count * blks * blks);
    row_index.resize(grid_occupancy.Rows());

    for (std::size_t r = 0; r < grid_occupancy.Rows(); ++r) {
      row_index[r] = col_index.size();

      for (std::size_t c = 0; c < grid_occupancy.Cols(); ++c) {
        if (grid_occupancy.Get(r, c)) {
          col_index.push_back(c);

          for (std::size_t i = 0; i < blks; ++i) {
            for (std::size_t j = 0; j < blks; ++j) {
              data.push_back(old.At(r * blks + i, c * blks + j));
            }
          }
        }
      }
    }

    for (const auto r: row_index)
      std::cerr << r << " ";
    std::cerr << "\n";

    for (const auto c: col_index)
      std::cerr << c << " ";
    std::cerr << "\n";

    for (const auto d: data)
      std::cerr << d << " ";
    std::cerr << "\n";
  }

 private:
  std::size_t rows;
  std::size_t cols;
  std::size_t blks;

  std::vector<std::size_t> row_index;
  std::vector<std::size_t> col_index;
  std::vector<Type>        data;
};


#endif // SPARSE_MATRIX_HH_
