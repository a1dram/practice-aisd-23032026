#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP

#include <stdexcept>

namespace topit {
  template < class T >
  struct Vector
  {
    Vector();
    explicit Vector(size_t s);
    Vector(size_t s, const T& val);
    ~Vector();

    Vector(const Vector< T >& rhs);
    Vector< T >& operator=(const Vector< T >& );
    Vector(Vector<T>&&) noexcept;
    Vector<T>& operator=(Vector<T>&&) noexcept;
    
    size_t getSize() const noexcept;
    bool isEmpty() const noexcept;
    void swap(Vector<T>& rhs) noexcept;

    size_t getCapacity() const noexcept;

    void pushFront(const T& val);
    void pushBack(const T& val);

    /// Классная работа 30032026 (copy/swap, swap уже после того как всё получилось), всё протестировать
    void insert(size_t pos, const T& val);
    void insert(size_t pos, const Vector< T >& rhs, size_t b, size_t e); // в заданную позицию вставить диапозон значений, как я понял от b до e
    void erase(size_t pos);
    /// Домашняя работа
    /// 1. Реализовать итераторы для вектора, итераторы не тестировать
    /// 2. Придумать по 3 штуки insert/erase с итераторами ()
    struct VectorIterator; // с const/ не const итераторами
    void insert(VectorIterator pos, const T& val); // 3 штуки (первый)
    void erase(VectorIterator pos); // 3 штуки


    template< class IT >
    void insert(VectorIterator pos, IT begin, IT end); // второй

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    private:
      T* data_;
      size_t size_;
      size_t capacity_;       
  };

  /// дзшка  
  template< class T >
  bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
  template< class T >
  bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);
  ///
}

template< class T >
T& topit::Vector< T >::at(size_t id) {
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

// template< class T >
// T& topit::Vector< T >::at(size_t id) {
//   return const_cast< T& >(static_cast< const Vector < T >* >(this)->at(id));
// }
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// можно и так, но лучше дублирование кода, которое выше

template< class T >
const T& topit::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

template< class T >
topit::Vector< T >::Vector() : data_(nullptr), size_(0), capacity_(0)
{}

template< class T >
topit::Vector< T >::~Vector() {
  delete[] data_;
}

template< class T >
topit::Vector< T >::Vector(size_t size) : 
  data_(size ? new T[size] : nullptr), 
  size_(size),
  capacity_(size) 
{}

// template< class T >
// topit::Vector< T >::Vector(size_t size, const T& val) : 
//   data_(size ? new T[size] : nullptr), 
//   size_(size),
//   capacity_(size)
// {
//   for (size_t i = 0; i < size; ++i) {
//     try {
//       data_[i] = val;
//     } catch (...) {
//       delete[] data_;
//       throw;
//     }
//   }
// }
// template< class T >

template< class T >
topit::Vector< T >::Vector(size_t size, const T& val) : 
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = val;
  }
}

template< class T>
topit::Vector< T >::Vector(const Vector< T >& rhs) : Vector(rhs.getSize()) {
  for (size_t i = 0; i < getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}

template < class T >
topit::Vector<T>::Vector(Vector<T>&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept {
  // if (this == std::addressof(rhs)) {
  //   return *this;
  // }

  Vector< T > cpy(std::move(rhs)); // тут был один объект и остался один из-за std::move, 
  // здесь ссылки не сломаются без проверки, так что можно не писать
  swap(cpy);
  return *this;
}

template< class T >
void topit::Vector< T >::swap(Vector<T>& rhs) noexcept {
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs) {
  if (this == std::addressof(rhs)) {
    return *this;
  }
  // при v = v с итераторами, они сломаются из-за замены адресов, несмотря на то, что == не выдаёт различий
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}
// template< class T>
// topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs) {
//   T* d = new T[rhs.getSize()];

//   try {
//     for (size_t i = 0; i < rhs.getSize(); ++i) {
//       d[i] = rhs.data_[i];
//     }
//   } catch (...) {
//     delete[] d;
//     throw;
//   }

//   delete[] data_;
//   data_ = d;
//   size_ rhs.getSize();
//   capacity_ = rhs.getSize();
//   return *this;
// }

template< class T >
T& topit::Vector<T>::operator[](size_t id) noexcept {
  return data_[id];
} 
template< class T >
const T& topit::Vector<T>::operator[](size_t id) const noexcept {
  return data_[id];
} 

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept {
  return !size_;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept {
  return size_;
}
template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept {
  return capacity_;
}

template< class T >
void topit::Vector< T >::pushFront(const T& val) {
  Vector< T > result(getSize() + 1);
  result[0] = val;
  for (size_t i = 0; i < getSise(); ++i) {
    retult[i + 1] = (*this)[i];
  }
  // менять копию
  // Если были исключения -> деструктор копирования освободит ресурсы, вектор не изменится
  swap(result);
}

template< class T >
void topit::Vector< T >::pushBack(const T& val)
{
  if (size_ == capacity_) {
    size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;

    T* tmp_data = new T[new_cap];

    try {
      for (size_t i = 0; i < size_; ++i) {
        tmp_data[i] = data_[i];
      }
    } catch (...) {
      delete[] tmp_data;
      throw;
    }

    delete[] data_;
    data_ = tmp_data;
    capacity_ = new_cap;
  }

  data_[size_] = val;
  ++size_;
}

template< class T >
bool topit::operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
  if (lhs.getSize() != rhs.getSize()) {
    return false;
  }

  for (size_t i = 0; i < rhs.getSize(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template< class T >
bool topit::operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs == rhs);
}

#endif


