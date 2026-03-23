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

bool test4() {
  constexpr size_t size = 3ull;
  Vector< int > v(size);
  try {
    v.at(0);
    return true;
  } catch (...) {
    return false;
  }
}
bool test5() {
  constexpr size_t size = 3ull;
  Vector< int > v(size);
  try {
    v.at(size + 10);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

int main() {
  using test_f = bool(*)();
  using case_t = std::pair< test_f, const char* >;
  case_t tests[] = {
    {test1, "Default constructed vector must be empty"},
    {test2, "Default constructed vector size is zero"},
    {test3, "Vector constructed with size has non-zero size"},
    {test4, "In range access does not generate exceptions"},
    {test5, "Out of range access generates std::out_of_range exception"}
  };

  size_t count = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;

  for (size_t i = 0; i < count; ++i) {
    std::cout << tests[i].first << " : " << tests[i].second << '\n';
  }
}

