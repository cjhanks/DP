#ifndef FLOYD_WARSHALL_HH_
#define FLOYD_WARSHALL_HH_

#include <cassert>
#include "matrix.hh"

template <typename Cost_>
class FloydWarshall {
 public:
  using Cost = Cost_;
  using DenseMatrix = Matrix2D<Cost>;

  static void
  Solve(DenseMatrix& matrix) {
    assert(matrix.Rows() == matrix.Cols());

    for (std::size_t k = 0; k < matrix.Rows(); ++k) {
      for (std::size_t i = 0; i < matrix.Rows(); ++i) {
        for (std::size_t j = 0; j < matrix.Cols(); ++j) {
          const auto& a = matrix.At(i, j);
          const auto& b = matrix.At(k, j);
          const auto& c = matrix.At(i, k);

          if (b == std::numeric_limits<Cost>::infinity()
           || c == std::numeric_limits<Cost>::infinity())
            continue;

          if (b + c < a)
            matrix.At(i, j) = b + c;
        }
      }
    }
  }
};

#endif // FLOYD_WARSHALL_HH_
