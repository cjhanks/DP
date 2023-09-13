#ifndef MAX_PATH_SUM_HH_
#define MAX_PATH_SUM_HH_

#include "matrix.hh"

#include <algorithm>
#include <vector>

template <typename Type_>
class MaxPathSum {
 public:
  using Type = Type_;

  static Type
  Solve(const Matrix2D<Type>& mat, std::size_t start_row, std::size_t start_col) {
    Matrix2D<bool> visited(mat.Rows(), mat.Cols(), false);

    return SolveRecurse(mat, visited, start_row, start_col);
  }

 private:
  static Type
  SolveRecurse(
      const Matrix2D<Type>& mat,
      Matrix2D<bool>& visited,
      std::size_t row,
      std::size_t col) {
    if (visited.Get(row, col))
      return 0;

    visited.Set(row, col, true);

    struct Coord {
      Type        val;
      std::size_t row;
      std::size_t col;
    };

    std::vector<Coord> coords;

    Type val = mat.At(row, col);

    if (row > 0) {
      std::size_t r = row - 1;
      std::size_t c = col;
      Type        v = mat.At(r, c);

      if (v > val)
        coords.push_back({v, r, c});
    }

    if (col > 0) {
      std::size_t r = row;
      std::size_t c = col - 1;
      Type        v = mat.At(r, c);

      if (v > val)
        coords.push_back({v, r, c});
    }

    if (row < mat.Rows() - 1) {
      std::size_t r = row + 1;
      std::size_t c = col;
      Type        v = mat.At(r, c);

      if (v > val)
        coords.push_back({v, r, c});
    }

    if (col < mat.Cols() - 1) {
      std::size_t r = row;
      std::size_t c = col + 1;
      Type        v = mat.At(r, c);

      if (v > val)
        coords.push_back({v, r, c});
    }

    Type max_score = 0;
    for (const auto& coord: coords) {
      Type score = SolveRecurse(
              mat,
              visited,
              coord.row,
              coord.col
          );
      max_score = std::max(max_score, score);
    }

    visited.Set(row, col, false);
    return mat.At(row, col) + max_score;
  }
};

#endif // MAX_PATH_SUM_HH_
