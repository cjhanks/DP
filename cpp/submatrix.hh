#ifndef SUBMATRIX_HH_
#define SUBMATRIX_HH_

#include "matrix.hh"

template <typename Type_>
class IntegralImage : public Matrix2D<Type_> {
 public:
  using Type = Type_;

  explicit IntegralImage(const Matrix2D<Type>& mat)
   : Matrix2D<Type>(mat.Rows(), mat.Cols()) {

    for (std::size_t r = 0; r < mat.Rows(); ++r) {
      Type running = 0;
      for (std::size_t c = 0; c < mat.Cols(); ++c) {
        running += mat.At(r, c);
        this->At(r, c) = running;
      }
    }

    for (std::size_t c = 0; c < mat.Cols(); ++c) {
      for (std::size_t r = 1; r < mat.Rows(); ++r) {
        this->At(r, c) += this->At(r - 1, c);
      }
    }
  }

  Type
  Area(std::size_t r_head, std::size_t c_head,
       std::size_t r_tail, std::size_t c_tail) const {
    // AB
    // CD
    // D - B - C + A
    Type a = 0;
    Type b = 0;
    Type c = 0;
    Type d = this->At(r_tail - 0, c_tail - 0);

    if (r_head > 0 && c_head > 0)
      a = this->At(r_head - 1, c_head - 1);

    if (r_head > 0)
      b = this->At(r_head - 1, c_tail - 0);

    if (c_head > 0)
      c = this->At(r_tail - 0, c_head - 1);

    return (d - b - c + a);
  }
};

template <typename Type_>
class Submatrix {
 public:
  using Type = Type_;

  static std::size_t
  Solve(const Matrix2D<Type>& mat, Type val) {
    IntegralImage<Type> imat(mat);

    std::cerr << mat  << "\n";
    std::cerr << imat << "\n";

    std::cerr << imat.Area(0, 0, 1, 1) << "\n";
    std::cerr << imat.Area(2, 1, 3, 3) << "\n";
  }
};

#endif // SUBMATRIX_HH_
