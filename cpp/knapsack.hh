#ifndef KNAPSACK_HH_
#define KNAPSACK_HH_

#include "matrix.hh"

template <typename Element>
class Knapsack {
 public:
  std::size_t
  static Solve(std::size_t capacity, const std::vector<Element>& elems) {
    Matrix2D<double> matrix(elems.size() + 1, capacity + 1,  0.0);

    for (std::size_t n = 1; n < matrix.Rows(); ++n) {
      const auto& value  = elems[n - 1].value;
      const auto& weight = elems[n - 1].weight;

      for (std::size_t c = 1; c < matrix.Cols(); ++c) {
        if (weight <= c) {
          const auto& a = value
                        + matrix.At(n - 1, c - weight);
          const auto& b = matrix.At(n - 1, c);

          matrix.At(n, c) = std::max(a, b);
        } else {
          matrix.At(n, c) = matrix.At(n - 1, c);
        }
      }
    }

    return matrix.At(elems.size(), capacity);
  }


  //Knapsack(
};

#endif // KNAPSACK_HH_
