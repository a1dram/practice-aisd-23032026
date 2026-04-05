#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP

#include <stdexcept>
#include <utility>

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

    /// В конце пары делали
    // Vector< T >& move_assign(Vector< T >& rhs) noexcept;
    // Vector< T >& unstable_copy_assign(const Vector< T >& rhs);
    ///

    void pushFront(const T& val);
    void pushBack(const T& val);

        /// Домашка с 30032026 (copy/swap, swap уже после того как всё получилось), всё протестировать
    void insert(size_t pos, const T& val);
    void insert(size_t pos, const Vector< T >& rhs, size_t b, size_t e); // в заданную позицию вставить диапозон значений, как я понял от b до e
    void erase(size_t pos);
    /// Домашняя работа
    /// 1. Реализовать итераторы для вектора, итераторы не тестировать
    /// 2. Придумать по 3 штуки insert/erase с итераторами ()
    struct VectorIterator // с const/ не const итераторами
    {
      VectorIterator();
      explicit VectorIterator(T* ptr);

      T& operator*() const;
      T* operator->() const;
      VectorIterator& operator++();
      VectorIterator operator++(int);
      bool operator==(const VectorIterator& rhs) const noexcept;
      bool operator!=(const VectorIterator& rhs) const noexcept;

      T* ptr_;
    };

    struct ConstVectorIterator
    {
      ConstVectorIterator();
      explicit ConstVectorIterator(const T* ptr);
      ConstVectorIterator(VectorIterator rhs);

      const T& operator*() const;
      const T* operator->() const;
      ConstVectorIterator& operator++();
      ConstVectorIterator operator++(int);
      bool operator==(const ConstVectorIterator& rhs) const noexcept;
      bool operator!=(const ConstVectorIterator& rhs) const noexcept;

      const T* ptr_;
    };

    void insert(VectorIterator pos, const T& val); // 3 штуки (первый)
    void insert(VectorIterator pos, size_t count, const T& val); // второй
    template< class IT >
    void insert(VectorIterator pos, IT begin, IT end); // ( третий )

    void erase(VectorIterator pos); // 3 штуки
    void erase(VectorIterator first, VectorIterator last);
    void erase(VectorIterator pos, size_t count);
    ///

    VectorIterator begin() noexcept;
    VectorIterator end() noexcept;
    ConstVectorIterator begin() const noexcept;
    ConstVectorIterator end() const noexcept;
    ConstVectorIterator cbegin() const noexcept;
    ConstVectorIterator cend() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    private:
      size_t iteratorToIndex(VectorIterator pos) const;
      void insertRangeAtIndex(size_t pos, const T* src, size_t count);
      void eraseRangeAtIndex(size_t pos, size_t count);

      T* data_;
      size_t size_;
      size_t capacity_;       
  };

  template< class T >
  bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
  template< class T >
  bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);
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
  rhs.size_ = 0;
  rhs.capacity_ = 0;
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
  Vector< T > result(size_ + 1);
  result[0] = val;
  for (size_t i = 0; i < size_; ++i) {
    result[i + 1] = (*this)[i];
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

// insert и erase без векторов
template< class T >
void topit::Vector< T >::insert(size_t pos, const T& val)
{
  if (pos > size_) {
    throw std::out_of_range("bad insert position");
  }

  Vector< T > tmp(size_ + 1);
  for (size_t i = 0; i < pos; ++i) {
    tmp.data_[i] = data_[i];
  }
  tmp.data_[pos] = val;
  for (size_t i = pos; i < size_; ++i) {
    tmp.data_[i + 1] = data_[i];
  }
  swap(tmp);
}

template< class T >
void topit::Vector< T >::erase(size_t pos)
{
  if (pos >= size_) {
    throw std::out_of_range("bad erase position");
  }

  Vector< T > tmp(size_ - 1);
  for (size_t i = 0; i < pos; ++i) {
    tmp.data_[i] = data_[i];
  }
  for (size_t i = pos + 1; i < size_; ++i) {
    tmp.data_[i - 1] = data_[i];
  }
  swap(tmp);
}
// ^^^^^^^^^^^^^insert и erase без векторов

template< class T >
topit::Vector< T >::VectorIterator::VectorIterator():
  ptr_(nullptr)
{}

template< class T >
topit::Vector< T >::VectorIterator::VectorIterator(T* ptr):
  ptr_(ptr)
{}

template< class T >
T& topit::Vector< T >::VectorIterator::operator*() const
{
  return *ptr_;
}

template< class T >
T* topit::Vector< T >::VectorIterator::operator->() const
{
  return ptr_;
}

template< class T >
typename topit::Vector< T >::VectorIterator&
topit::Vector< T >::VectorIterator::operator++()
{
  ++ptr_;
  return *this;
}

template< class T >
typename topit::Vector< T >::VectorIterator
topit::Vector< T >::VectorIterator::operator++(int)
{
  VectorIterator tmp(*this);
  ++(*this);
  return tmp;
}

template< class T >
bool topit::Vector< T >::VectorIterator::operator==(const VectorIterator& rhs) const noexcept
{
  return ptr_ == rhs.ptr_;
}

template< class T >
bool topit::Vector< T >::VectorIterator::operator!=(const VectorIterator& rhs) const noexcept
{
  return !(*this == rhs);
}

template< class T >
topit::Vector< T >::ConstVectorIterator::ConstVectorIterator():
  ptr_(nullptr)
{}

template< class T >
topit::Vector< T >::ConstVectorIterator::ConstVectorIterator(const T* ptr):
  ptr_(ptr)
{}

template< class T >
topit::Vector< T >::ConstVectorIterator::ConstVectorIterator(VectorIterator rhs):
  ptr_(rhs.ptr_)
{}

template< class T >
const T& topit::Vector< T >::ConstVectorIterator::operator*() const
{
  return *ptr_;
}

template< class T >
const T* topit::Vector< T >::ConstVectorIterator::operator->() const
{
  return ptr_;
}

template< class T >
typename topit::Vector< T >::ConstVectorIterator&
topit::Vector< T >::ConstVectorIterator::operator++()
{
  ++ptr_;
  return *this;
}

template< class T >
typename topit::Vector< T >::ConstVectorIterator
topit::Vector< T >::ConstVectorIterator::operator++(int)
{
  ConstVectorIterator tmp(*this);
  ++(*this);
  return tmp;
}

template< class T >
bool topit::Vector< T >::ConstVectorIterator::operator==(const ConstVectorIterator& rhs) const noexcept
{
  return ptr_ == rhs.ptr_;
}

template< class T >
bool topit::Vector< T >::ConstVectorIterator::operator!=(const ConstVectorIterator& rhs) const noexcept
{
  return !(*this == rhs);
}

template< class T >
typename topit::Vector< T >::VectorIterator topit::Vector< T >::begin() noexcept
{
  return VectorIterator(data_);
}

template< class T >
typename topit::Vector< T >::VectorIterator topit::Vector< T >::end() noexcept
{
  if (data_ == nullptr) {
    return VectorIterator(nullptr);
  }
  return VectorIterator(data_ + size_);
}

template< class T >
typename topit::Vector< T >::ConstVectorIterator topit::Vector< T >::begin() const noexcept
{
  return ConstVectorIterator(data_);
}

template< class T >
typename topit::Vector< T >::ConstVectorIterator topit::Vector< T >::end() const noexcept
{
  if (data_ == nullptr) {
    return ConstVectorIterator(nullptr);
  }
  return ConstVectorIterator(data_ + size_);
}

template< class T >
typename topit::Vector< T >::ConstVectorIterator topit::Vector< T >::cbegin() const noexcept
{
  return ConstVectorIterator(data_);
}

template< class T >
typename topit::Vector< T >::ConstVectorIterator topit::Vector< T >::cend() const noexcept
{
  if (data_ == nullptr) {
    return ConstVectorIterator(nullptr);
  }
  return ConstVectorIterator(data_ + size_);
}

// вспомогательные insert и erase
template< class T >
void topit::Vector< T >::insertRangeAtIndex(size_t pos, const T* src, size_t count)
{
  if (pos > size_) {
    throw std::out_of_range("bad insert position");
  }

  Vector< T > tmp(size_ + count);
  for (size_t i = 0; i < pos; ++i) {
    tmp.data_[i] = data_[i];
  }
  for (size_t i = 0; i < count; ++i) {
    tmp.data_[pos + i] = src[i];
  }
  for (size_t i = pos; i < size_; ++i) {
    tmp.data_[i + count] = data_[i];
  }
  swap(tmp);
}

template< class T >
void topit::Vector< T >::eraseRangeAtIndex(size_t pos, size_t count)
{
  if (pos > size_ || pos + count > size_) {
    throw std::out_of_range("bad erase range");
  }

  Vector< T > tmp(size_ - count);
  for (size_t i = 0; i < pos; ++i) {
    tmp.data_[i] = data_[i];
  }
  for (size_t i = pos + count; i < size_; ++i) {
    tmp.data_[i - count] = data_[i];
  }
  swap(tmp);
}

template< class T >
size_t topit::Vector< T >::iteratorToIndex(VectorIterator pos) const
{
  if (size_ == 0) {
    if (pos.ptr_ == nullptr) {
      return 0;
    }
    throw std::out_of_range("bad iterator");
  }

  if (pos.ptr_ < data_ || pos.ptr_ > data_ + size_) {
    throw std::out_of_range("bad iterator");
  }

  return static_cast< size_t >(pos.ptr_ - data_);
}
// -------------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

template< class T >
void topit::Vector< T >::insert(size_t pos, const Vector< T >& rhs, size_t b, size_t e)
{
  if (pos > size_ || b > e || e > rhs.size_) {
    throw std::out_of_range("bad range insert");
  }
  insertRangeAtIndex(pos, rhs.data_ + b, e - b);
}

template< class T >
void topit::Vector< T >::insert(VectorIterator pos, const T& val)
{
  insert(iteratorToIndex(pos), val);
}

template< class T >
void topit::Vector< T >::insert(VectorIterator pos, size_t count, const T& val)
{
  size_t id = iteratorToIndex(pos);
  Vector< T > tmp(count, val);
  insert(id, tmp, 0, tmp.getSize());
}

template< class T >
template< class IT >
void topit::Vector< T >::insert(VectorIterator pos, IT beginIt, IT endIt)
{
  size_t id = iteratorToIndex(pos);
  Vector< T > tmp;

  for (IT it = beginIt; it != endIt; ++it) {
    tmp.pushBack(*it);
  }

  insert(id, tmp, 0, tmp.getSize());
}

template< class T >
void topit::Vector< T >::erase(VectorIterator pos)
{
  size_t id = iteratorToIndex(pos);
  if (id >= size_) {
    throw std::out_of_range("bad erase iterator");
  }
  eraseRangeAtIndex(id, 1);
}

template< class T >
void topit::Vector< T >::erase(VectorIterator first, VectorIterator last)
{
  size_t firstId = iteratorToIndex(first);
  size_t lastId = iteratorToIndex(last);

  if (firstId > lastId) {
    throw std::out_of_range("bad erase range");
  }

  eraseRangeAtIndex(firstId, lastId - firstId);
}

template< class T >
void topit::Vector< T >::erase(VectorIterator pos, size_t count)
{
  size_t id = iteratorToIndex(pos);
  if (id > size_ || id + count > size_) {
    throw std::out_of_range("bad erase count");
  }
  eraseRangeAtIndex(id, count);
}

#endif


