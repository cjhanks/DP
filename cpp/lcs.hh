#ifndef LCS_HH_
#define LCS_HH_

#include "matrix.hh"
#include "type_map.hh"

template <typename Token>
class LongestCommonSubsequence {
 public:
  using Vector = typename impl::Vector<Token>::Type;

  static std::size_t
  Solve(Vector veca, Vector vecb, Matrix2D<unsigned>& mat) {
    mat = Matrix2D<unsigned>(veca.size() + 1, vecb.size() + 1);

    for (std::size_t r = 0; r < mat.Rows(); ++r)
      mat.At(r, 0) = 0;

    for (std::size_t c = 0; c < mat.Cols(); ++c)
      mat.At(0, c) = 0;

    for (std::size_t r = 1; r < mat.Rows(); ++r) {
      for (std::size_t c = 1; c < mat.Cols(); ++c) {
        if (veca[r - 1] == vecb[c - 1]) {
          // +-+-+
          // |C| |
          // +_+_+
          // | |X|
          // +_+_+
          mat.At(r, c) = mat.At(r - 1, c - 1) + 1;
        } else {
          // +-+-+
          // | |A|
          // +_+_+
          // |B|X|
          // +_+_+
          //
          const auto& a = mat.At(r - 1, c - 0);
          const auto& b = mat.At(r - 0, c - 1);
          mat.At(r, c) = std::max(a, b);
        }
      }
    }

    return mat.At(veca.size(), vecb.size());
  }

  static std::size_t
  Solve(Vector veca, Vector vecb) {
    Matrix2D<unsigned> mat;
    return Solve(veca, vecb, mat);
  }

};

#endif // LCS_HH_
