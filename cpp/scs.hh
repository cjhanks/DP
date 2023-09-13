#ifndef SCS_HH_
#define SCS_HH_

#include <algorithm>

#include "backtrack.hh"
#include "lcs.hh"
#include "matrix.hh"
#include "type_map.hh"


template <typename Token>
class ShortestCommonSubsequence {
 public:
  using Vector = typename impl::Vector<Token>::Type;

  static Vector
  Solve(Vector veca, Vector vecb) {
    using LCS = LongestCommonSubsequence<Token>;
    Matrix2D<unsigned> mat(veca.size() + 1, vecb.size() + 1, 0U);
    LCS::Solve(veca, vecb, mat);

    std::size_t r;
    std::size_t c;
    Vector output = Backtrack<Token>(veca, vecb, mat, r, c);

    while (r > 0)
      output.push_back(veca[--r]);

    while (c > 0)
      output.push_back(vecb[--c]);

    std::reverse(output.begin(), output.end());
    return output;
  }
};

#endif // SCS_HH_
