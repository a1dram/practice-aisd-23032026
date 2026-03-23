#include <iostream>
#include "vector-top-it.hpp"

bool test1() {
  using topit::Vector;
  Vector< int > v;
  return v.isEmpty();
}

int main() {
  using test_f = bool(*)();
  test_f tests[] = {
    test1,
  };

  size_t count = sizeof(tests) / sizeof(test_f);
  std::cout << std::boolalpha;

  for (size_t i = 0; i < count; ++i) {
    std::cout << tests[i]() << " : " << i << '\n';
  }
}

