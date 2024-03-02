#ifndef S21_CONTAINERS_STACK_S21_STACK_H
#define S21_CONTAINERS_STACK_S21_STACK_H

#include <iostream>

namespace s21 {
template <typename Type>
class stack {
 public:
  explicit stack() noexcept { this->top_ = nullptr; }

  stack(std::initializer_list<Type> const &l) {
    this->top_ = nullptr;
    for (auto it : l) {
      this->Push(it);
    }
  }

  stack(const stack &other) noexcept {
    StackElemants_ *other_top_buf_pointer = other.top_;

    if (other_top_buf_pointer != nullptr) {
      this->top_ = new StackElemants_;
      StackElemants_ *this_top_buf_pointer = this->top_;
      while (other_top_buf_pointer != nullptr) {
        this_top_buf_pointer->stored_value =
            other_top_buf_pointer->stored_value;
        other_top_buf_pointer = other_top_buf_pointer->previous_element;
        if (other_top_buf_pointer == nullptr) {
          this_top_buf_pointer->previous_element = nullptr;
        } else {
          StackElemants_ *new_element = new StackElemants_;
          this_top_buf_pointer->previous_element = new_element;
          this_top_buf_pointer = new_element;
        }
      }
    }
  }

  stack(stack &&other) noexcept {
    if (other.top_ != nullptr) {
      this->top_ = other.top_;
      other.top_ = nullptr;
    } else {
      this->top_ = nullptr;
    }
  }

  ~stack() { this->ClearStack_(); }

  bool Empty() const noexcept {
    if (this->top_ == nullptr) {
      return true;
    }

    return false;
  }

  void Pop() noexcept {
    if (this->top_ == nullptr) {
      return;
    }
    StackElemants_ *buf = this->top_->previous_element;
    delete this->top_;
    this->top_ = buf;
  }

  void Push(const Type &value) noexcept {
    StackElemants_ *buf = new StackElemants_;
    buf->stored_value = value;
    buf->previous_element = this->top_;
    this->top_ = buf;
  }

  size_t Size() const noexcept {
    StackElemants_ *buf = this->top_;
    size_t size = 0;

    while (buf != nullptr) {
      size++;
      buf = buf->previous_element;
    }
    return size;
  }

  const Type &Top() const noexcept { return top_->stored_value; }

  void Swap(stack &other) {
    StackElemants_ *buf = other.top_;
    other.top_ = this->top_;
    this->top_ = buf;
  }

  bool &operator==(const stack &other) const noexcept {
    if (this->Size() != other.Size()) {
      return rFAIL;
    }

    StackElemants_ *ptr_1 = this->top_;
    StackElemants_ *ptr_2 = other.top_;

    for (size_t i = 0; i < this->Size(); i++) {
      if (ptr_1->stored_value != ptr_2->stored_value) {
        return rFAIL;
      }
      ptr_1 = ptr_1->previous_element;
      ptr_2 = ptr_2->previous_element;
    }

    return rSUCCESS;
  }

  stack &operator=(const stack &other) noexcept {
    if (*this == other) {
      return *this;
    }

    this->ClearStack_();
    stack buf(other);
    *this = buf;

    return *this;
  }

  stack &operator=(stack &&other) noexcept {
    if (*this == other) {
      return *this;
    }

    this->ClearStack_();
    this->Swap(other);
  }

  template <typename... Types>
  void insert_many_front(Types &&...args) {
    for (Type i : {Type(args)...}) {
      this->Push(i);
    }
  }

 private:
  struct StackElemants_ {
    Type stored_value;
    StackElemants_ *previous_element;
  };
  StackElemants_ *top_;
  enum { rFAIL, rSUCCESS };

  void ClearStack_() noexcept {
    while (this->top_ != nullptr) {
      this->Pop();
    }
  }
};
}  // namespace s21

#endif