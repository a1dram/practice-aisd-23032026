#include <iostream>
#include <utility>
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
  Vector< int > v(size, 0);
  return v.getSize() == size;
}

bool test4() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  try {
    int value = v.at(0);
    return value == 1;
  } catch (...) {
    return false;
  }
}
bool test5() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  try {
    v.at(size + 10);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}
bool test6() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  try {
    const int& value = v.at(0);
    return value == 1;
  } catch (...) {
    return false;
  }
}

bool test7() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  try {
    v.at(size + 10);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}
/// дзшка
bool test8() {
  Vector< int > v;
  return v.getCapacity() == 0;
}

bool test9() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 7);
  return v.getCapacity() == size;
}

bool test10() {
  Vector< int > v;
  v.pushBack(10);
  return v.getSize() == 1 && v.getCapacity() == 1 && v.at(0) == 10;
}

bool test11() {
  Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);
  return v.getSize() == 2 && v.getCapacity() == 2 && v.at(0) == 10 && v.at(1) == 20;
}

bool test12() {
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
  v[1] = 42;
  return v[1] == 42;
}

bool test13() {
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 5);
  return v[0] == 5 && v[1] == 5 && v[2] == 5;
}

bool test14() {
  Vector< int > a(3, 4);
  Vector< int > b(3, 4);
  return a == b;
}

bool test15() {
  Vector< int > a(3, 4);
  Vector< int > b(2, 4);
  return a != b;
}

bool test16() {
  Vector< int > a(3, 4);
  Vector< int > b(3, 4);
  b[1] = 10;
  return a != b;
}

/// практика 30 03 2026

bool test17() {
  Vector< int > v(2, 0);
  Vector<int> yav = v;
  return yav == v;
}

bool test18() {
  Vector< int > v;
  Vector< int > yav(2, 0);
  bool res = v != yav;
  return res && v == yav;
}

bool test19() {
  Vector< int > v(2, 0);
  Vector< int > yav(3, 1);

  Vector< int > cpy_v(v);
  Vector< int > cpy_yav(yav);
  v.swap(yav);

  return cpy_v == yav && cpy_yav == v;
}

bool test20() {
  Vector< int > v(2, 0);
  Vector< int > cpy_v(v);

  Vector< int > yav = std::move(v);
  return yav == cpy_v;
}

bool test21() {
  Vector< int > v(2, 0);
  Vector< int > cpy(v);
  Vector< int > yav;

  yav = std::move(v);
  return yav == cpy;
}

/// домашка на 06042026
bool test22() {
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool test23() {
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.erase(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool test24() {
  Vector< int > v;
  v.pushBack(10);
  v.pushBack(20);

  Vector< int > rhs;
  rhs.pushBack(1);
  rhs.pushBack(2);
  rhs.pushBack(3);
  rhs.pushBack(4);

  v.insert(1, rhs, 1, 3);
  return v.getSize() == 4 && v[0] == 10 && v[1] == 2 && v[2] == 3 && v[3] == 20;
}

/// с итераторами
bool test25() {
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);

  Vector< int >::VectorIterator it = v.begin();
  ++it;
  v.insert(it, 2);

  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool test26() {
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(4);

  Vector< int >::VectorIterator it = v.begin();
  ++it;
  size_t idx = 2;
  v.insert(it, idx, 9);

  return v.getSize() == 4 && v[0] == 1 && v[1] == 9 && v[2] == 9 && v[3] == 4;
}

bool test27() {
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(4);

  int arr[2] = {2, 3};
  Vector< int >::VectorIterator it = v.begin();
  ++it;
  v.insert(it, arr, arr + 2);

  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4;
}

bool test28() {
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  Vector< int >::VectorIterator it = v.begin();
  ++it;
  v.erase(it);

  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool test29() {
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);

  Vector< int >::VectorIterator first = v.begin();
  ++first;
  Vector< int >::VectorIterator last = first;
  ++last;
  ++last;
  v.erase(first, last);

  return v.getSize() == 2 && v[0] == 1 && v[1] == 4;
}

bool test30() {
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);

  Vector< int >::VectorIterator it = v.begin();
  ++it;
  v.erase(it, 2);

  return v.getSize() == 2 && v[0] == 1 && v[1] == 4;
}
/// практика 06 04 2026
bool test31() {
  Vector< int > v{1, 2};
  return (v.getSize() == 2) && (v[0] == 1) && (v[1] == 2);
}
bool test32() {
  Vector< int > v{};
  return v.isEmpty();
}

int main() {
  using test_f = bool(*)();
  using case_t = std::pair< test_f, const char* >;
  case_t tests[] = {
    {test1, "Default constructed vector must be empty"},
    {test2, "Default constructed vector size is zero"},
    {test3, "Vector constructed with size has non-zero size"},
    {test4, "In range access does not generate exceptions"},
    {test5, "Out of range access generates std::out_of_range exception"},
    {test6, "In range access for const vector: same as non-const"},
    {test7, "Out of range access for const vector: same as non-const"},
    /// дзшка
    {test8, "Default constructed vector capacity is zero"},
    {test9, "Vector constructed with size has equal capacity"},
    {test10, "pushBack adds first element and updates size and capacity"},
    {test11, "pushBack reallocates and preserves previous elements"},
    {test12, "Non-const operator[] allows element modification"},
    {test13, "Const operator[] allows element access"},
    {test14, "Equal vectors compare equal"},
    {test15, "Vectors with different sizes compare not equal"},
    {test16, "Vectors with different elements compare not equal"},
    /// классная работа 30 03 2026
    {test17, "Copy constuctor"},
    {test18, "Copy assigment operator"},
    {test19, "Void swap func tests"},
    {test20, "Move constuctor"},
    {test21, "Move assigment operator"},
    /// домашка на 06042026
    {test22, "Insert by index"},
    {test23, "Erase by index"},
    {test24, "Insert vector range by index"},
    /// домашняя работа с итераторами
    {test25, "Insert one element by iterator"},
    {test26, "Insert count copies by iterator"},
    {test27, "Insert range by iterator"},
    {test28, "Erase one element by iterator"},
    {test29, "Erase range by iterators"},
    {test30, "Erase count elements by iterator"},
    {test31, "test31"},
    {test32, "test32"}
    ///
  };

  size_t count = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;
  bool result = true;
  size_t fails = 0, successes = 0;

  for (size_t i = 0; i < count; ++i) {
    // std::cout << tests[i].first << " : " << tests[i].second << '\n';
    bool case_result = tests[i].first();
    result = result && case_result;

    if (case_result) {
      ++successes;
    } else {
      ++fails;
    }

    std::cout << case_result;
    std::cout << ": ";
    std::cout << tests[i].second << '\n';
  }

  std::cout << "SUMMARY\n";
  std::cout << result << " : TEST RESULTS\n";
  std::cout << fails << " failed tests\n";
  std::cout << successes << " passed tests\n";
}

