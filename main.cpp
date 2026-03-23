#include <iostream>
#include "vector-top-it.hpp"

using topit::Vector;

bool test1() {
  Vector< int > v;
  return v.isEmpty();
}

bool test2() {
  Vector< int > v;
  return v.getSize() == 0;
}

bool test3() {
  constexpr size_t size = 3ull;
  Vector< int > v(size);
  return v.getSize() == size;
}

int main() {
  using test_f = bool(*)();
  using case_t = std::pair< test_f, const char* >;
  case_t tests[] = {
    {test1, "Default constructed vector must be empty"},
    {test2, "Default constructed vector size is zero"},
    {test2, "Vector constructed with size has non-zero size"}
  };

  size_t count = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;

  for (size_t i = 0; i < count; ++i) {
    std::cout << tests[i].first << " : " << tests[i].second << '\n';
  }
}

