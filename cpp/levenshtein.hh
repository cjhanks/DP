#ifndef LEVENSHTEIN_HH_
#define LEVENSHTEIN_HH_

#include "matrix.hh"
#include "type_map.hh"


template <typename Token>
class Levenshtein {
 public:
  using Vector = typename impl::Vector<Token>::Type;

  static std::size_t
  Solve(const Vector& veca, const Vector& vecb) {
    // Initialize the matrix.
    Matrix2D<unsigned> matrix(veca.size() + 1, vecb.size() + 1, 0U);

    for (std::size_t r = 0; r < matrix.Rows(); ++r)
      matrix.At(r, 0) = r;

    for (std::size_t c = 0; c < matrix.Cols(); ++c)
      matrix.At(0, c) = c;

    for (std::size_t r = 1; r < matrix.Rows(); ++r) {
      for (std::size_t c = 1; c < matrix.Cols(); ++c) {
        const auto& token1 = veca[r - 1];
        const auto& token2 = vecb[c - 1];

        if (token1 == token2) {
          matrix.At(r, c) = matrix.At(r - 1, c - 1);
          continue;
        }

        constexpr unsigned Neighbors = 3;
        unsigned neighbors[Neighbors] = {
          matrix.At(r - 1, c - 0),
          matrix.At(r - 0, c - 1),
          matrix.At(r - 1, c - 1),
        };

        unsigned maximum = std::numeric_limits<unsigned>::max();
        for (std::size_t n = 0; n < Neighbors; ++n)
          maximum = std::min(neighbors[n], maximum);

        matrix.At(r, c) = maximum + 1;
      }
    }

    return matrix.At(veca.size(), vecb.size());
  }
};

#endif // LEVENSHTEIN_HH_
