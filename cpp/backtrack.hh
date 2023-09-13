#ifndef BACKTRACK_HH_
#define BACKTRACK_HH_

#include "matrix.hh"
#include "type_map.hh"

template <typename Token, typename Vector = typename impl::Vector<Token>::Type>
Vector
Backtrack(
    const Vector& row,
    const Vector& col,
    const Matrix2D<unsigned>& mat,
    bool reverse=true
) {
  Vector out;

  std::size_t r = row.size();
  std::size_t c = col.size();

  while (r > 0 && c > 0) {
    const auto& val_r = row[r];
    const auto& val_c = col[c];

    if (val_r == val_c) {
      out.push_back(val_r);
      --r;
      --c;
    } else {
      const auto& a = mat.At(r - 1, c - 0);
      const auto& b = mat.At(r - 0, c - 1);

      if (a > b) {
        out.push_back(val_r);
        --r;
      } else {
        out.push_back(val_c);
        --c;
      }
    }
  }

  if (reverse)
    std::reverse(out.begin(), out.end());

  return out;
}

template <typename Token, typename Vector = typename impl::Vector<Token>::Type>
Vector
Backtrack(
    const Vector& row,
    const Vector& col,
    const Matrix2D<unsigned>& mat,
    std::size_t& r,
    std::size_t& c
) {
  Vector out;

  r = row.size();
  c = col.size();

  while (r > 0 && c > 0) {
    const auto& val_r = row[r];
    const auto& val_c = col[c];

    if (val_r == val_c) {
      out.push_back(val_r);
      --r;
      --c;
    } else {
      const auto& a = mat.At(r - 1, c - 0);
      const auto& b = mat.At(r - 0, c - 1);

      if (a > b) {
        out.push_back(val_r);
        --r;
      } else {
        out.push_back(val_c);
        --c;
      }
    }
  }

  return out;
}

#endif // BACKTRACK_HH_
