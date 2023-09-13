#ifndef MATRIX_HH_
#define MATRIX_HH_

#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>


template <typename Type_>
class Matrix2D {
 public:
  using Type = Type_;

  Matrix2D(std::size_t rows, std::size_t cols, Type default_value)
   : rows(rows),
     cols(cols),
     data(rows * cols, default_value)
  {}

  Matrix2D(std::size_t rows, std::size_t cols)
   : Matrix2D(rows, cols, {}) {}

  Matrix2D()
   : Matrix2D(0, 0) {}

  Type&
  At(std::size_t row, std::size_t col) {
    return data[Index(row, col)];
  }

  void
  Set(std::size_t row, std::size_t col, Type val) {
    data[Index(row, col)] = val;
  }

  Type
  Get(std::size_t row, std::size_t col) {
    return data[Index(row, col)];
  }

  const Type&
  At(std::size_t row, std::size_t col) const {
    return data[Index(row, col)];
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
  std::vector<Type> data;

  std::size_t
  Index(std::size_t row, std::size_t col) const {
    assert(row < rows);
    assert(col < cols);
    return (row * cols) + col;
  }
};

template <typename Type>
std::ostream&
operator<<(std::ostream& ostr, const Matrix2D<Type>& mat) {
  for (std::size_t r = 0; r < mat.Rows(); ++r) {
    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      ostr << std::setw(3) << mat.At(r, c) << " ";
    }

    ostr << "\n";
  }

  return ostr;
}

#endif // MATRIX_HH_
