#ifndef TYPE_MAP_HH_
#define TYPE_MAP_HH_

#include <string>
#include <vector>


namespace impl {
template <typename Token>
struct Vector {
  using Type = std::vector<Token>;
};

template <>
struct Vector<char> {
  using Type = std::string;
};
} // ns impl

#endif // TYPE_MAP_HH_
