#ifndef S21_CONTAINERS_ARRAY_S21_ARRAY_H
#define S21_CONTAINERS_ARRAY_S21_ARRAY_H

#include <exception>
#include <iostream>

namespace s21 {
template <typename Type, std::size_t N>
class array {
 public:
  class iterator;

  explicit array() : mas_size_(N) {
    if (N != 0) this->arr_ = new Type[N];
  }

  ~array() { this->ClearMas_(); }

  array(std::initializer_list<Type> const &l) : mas_size_(N) {
    if (l.size() > this->mas_size_) {
      throw std::out_of_range("Number of numbers is more than array Size");
    }

    this->arr_ = new Type[mas_size_];
    int i = 0;
    for (auto it : l) {
      *(this->arr_ + i) = it;
      i++;
    }
  }

  array(const array &other) noexcept : mas_size_(other.mas_size_) {
    this->arr_ = new Type[this->mas_size_];

    for (size_t i = 0; i < this->mas_size_; i++) {
      this->arr_[i] = other.arr_[i];
    }
  }

  array(array &&other) noexcept {
    this->arr_ = other.arr_;
    this->mas_size_ = other.mas_size_;
    other.arr_ = nullptr;
    other.mas_size_ = 0;
  }

  bool operator==(const array &other) noexcept {
    if (this->mas_size_ != other.mas_size_) {
      return rFAIL;
    }

    for (size_t i = 0; i < this->mas_size_; i++) {
      if (*(this->arr_ + i) != *(other.arr_ + i)) {
        return rFAIL;
      }
    }
    return rSUCCESS;
  }

  array &operator=(const array &other) noexcept {
    if (*this == other) {
      return *this;
    }

    this->ClearMas_();
    array buf(other);
    *this = buf;

    return *this;
  }

  array &operator=(array &&other) noexcept {
    if (*this == other) {
      return *this;
    }

    this->ClearMas_();
    this->arr_ = other.arr_;
    this->mas_size_ = other.mas_size_;

    other.arr_ = nullptr;
    other.mas_size_ = 0;

    return *this;
  }

  Type &At(size_t pos) {
    if (pos >= this->mas_size_) {
      throw std::out_of_range("This index is not in the array");
    }
    return *(this->arr_ + pos);
  }

  Type &operator[](size_t pos) { return *(this->arr_ + pos); }

  const Type &Front() { return *(this->arr_); }

  const Type &Back() { return *(this->arr_ + this->mas_size_ - 1); }

  bool Empty() const noexcept {
    return this->mas_size_ == 0 ? rSUCCESS : rFAIL;
  }

  size_t Size() const noexcept { return this->mas_size_; }

  size_t Max_size() const noexcept { return N; }

  Type *Begin() noexcept { return this->arr_; }

  Type *End() noexcept { return this->arr_ + this->mas_size_; }

  Type *Data() { return this->arr_; }

  void Swap(array &other) noexcept {
    array buf(std::move(other));
    other = std::move(*this);
    *this = std::move(buf);
  }

  void Fill(const Type value) {
    for (auto it = this->Begin(); it != this->End(); it++) {
      *it = value;
    }
  }

  class iterator {
   public:
    explicit iterator() : cur_(nullptr) {}
    explicit iterator(Type *first) : cur_(first) {}

    Type &operator+(int n) noexcept { return *(this->cur_ + n); }

    Type &operator-(int n) noexcept { return *(this->cur_ - n); }

    Type &operator++(int) noexcept { return *this->cur_++; }
    Type &operator--(int) noexcept { return *this->cur_--; }

    Type &operator++() noexcept { return *++this->cur_; }
    Type &operator--() noexcept { return *--this->cur_; }

    Type operator*() noexcept { return *this->cur_; }

    bool operator==(iterator &it) noexcept { return this->cur_ == it.cur_; }

    bool operator!=(iterator &it) noexcept { return this->cur_ != it.cur_; }

    bool operator!=(Type *pointer) noexcept { return this->cur_ != pointer; }

    iterator &operator=(iterator &other) noexcept {
      if (*this == other) {
        return *this;
      }

      *this = other;
    }

    iterator &operator=(Type *pointer) noexcept {
      if (this->cur_ == pointer) {
        return *this;
      }

      this->cur_ = pointer;
      return *this;
    }

   private:
    Type *cur_;
  };

 private:
  void ClearMas_() noexcept {
    if (this->mas_size_ != 0) {
      delete[] this->arr_;
      this->mas_size_ = 0;
    }
  }

  Type *arr_;
  size_t mas_size_;
  enum { rFAIL, rSUCCESS };
};
}  // namespace s21

#endif