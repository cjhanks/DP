#ifndef MATRIX_CHAIN_ORDER_HH_
#define MATRIX_CHAIN_ORDER_HH_

#include "matrix.hh"
#include "type_map.hh"

template <typename Type_>
class MatrixChainOrder {
 public:
  using Type = Type_;
  using Vector = typename impl::Vector<Type>::Type;


  static std::size_t
  SolveRecursive(
      const Vector& vec,
      std::size_t i,
      std::size_t j,
      Matrix2D<Type>& memo
  ) {
    if (i == j)
      return 0;

    std::cerr << "(" << i << ", " << j << ")\n";

    if (memo.At(i, j) != std::numeric_limits<Type>::max())
      return memo.At(i, j);

    Type min = std::numeric_limits<Type>::max();
    for (std::size_t k = i; k < j; ++k) {
      Type val = SolveRecursive(vec, i + 0, k, memo)
               + SolveRecursive(vec, k + 1, j, memo)
               + vec[i - 1] * vec[k] * vec[j];
      min = std::min(val, min);
      memo.At(i, j) = min;
    }

    return min;
  }

  static std::size_t
  SolveRecursive(Vector vec) {
    Matrix2D<Type> memo(
        vec.size() + 1,
        vec.size() + 1,
        std::numeric_limits<Type>::max()
    );
    return SolveRecursive(vec, 1, vec.size() - 1, memo);
  }

  static std::size_t
  Solve(Vector vec, Matrix2D<unsigned>& mat) {
    // Set the identity to 0.
    for (std::size_t n = 0; n < vec.size(); ++n)
      mat.At(n, n) = 0;

    for (std::size_t l = 2; l < vec.size(); ++l) {
      for (std::size_t i = 1; i < vec.size() - l + 1; ++i) {
        std::size_t j = i + l - 1;
        for (std::size_t k = i; k <= j - 1; ++k) {
          Type q = mat.At(i + 0, k)
                 + mat.At(k + 1, j)
                 + vec[i - 1] * vec[k] * vec[j];

          if (q < mat.At(i, j))
            mat.At(i, j) = q;
        }
      }
    }

    return mat.At(1, mat.Cols() - 1);
  }

  static std::size_t
  Solve(Vector vec) {
    Matrix2D<unsigned> mat(
        vec.size(),
        vec.size(),
        std::numeric_limits<Type>::max()
    );
    return Solve(vec, mat);
  }
};

#endif // MATRIX_CHAIN_ORDER_HH_
