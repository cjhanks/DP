#ifndef LARGEST_ALL_1_HH_
#define LARGEST_ALL_1_HH_

#include "matrix.hh"
#include "submatrix.hh"


template <typename Type_>
class LargestAllK {
 public:
  using Type = Type_;

  static std::size_t
  Solve(const Matrix2D<Type>& mat, Type k) {
    IntegralImage<Type> img(mat);
    std::size_t max_size = 0;

    for (std::size_t r = 0; r < mat.Rows(); ++r) {
      for (std::size_t c = 0; c < mat.Cols(); ++c) {
        if (mat.At(r, c) != k)
          continue;

        std::size_t spec_area = InnerLoop(img, r, c, k);
        max_size = std::max(max_size, spec_area);
      }
    }

    return max_size;
  }

 private:
  static std::size_t
  InnerLoop(
      const IntegralImage<Type>& img,
      std::size_t r,
      std::size_t c,
      Type k) {
    std::size_t max_area = 0;
    std::size_t i;
    std::size_t j;
    for (i = r; i < img.Rows(); ++i) {
      bool found = false;
      for (j = c; j < img.Cols(); ++j) {
        std::size_t spec_area = (k * k) * (1 + i - r) * (1 + j - c);
        std::size_t real_area = img.Area(r, c, i, j);
        if (real_area != spec_area)
          break;
        else
          found = true;

        max_area = std::max(max_area, real_area);
      }

      if (!found) {
        break;
      }
    }

    return max_area;
  }
};

#endif // LARGEST_ALL_1_HH_
