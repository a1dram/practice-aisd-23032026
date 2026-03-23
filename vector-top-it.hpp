#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP

namespace topit {
  template < class T >
  struct Vector
  {
    T* data;
    size_t size;
    size_t capacity;
  };

  template < class T >
  bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
}

#endif
