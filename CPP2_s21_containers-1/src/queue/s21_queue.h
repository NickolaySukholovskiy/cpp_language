#ifndef S21_CONTAINERS_QUEUE_S21_QUEUE_H
#define S21_CONTAINERS_QUEUE_S21_QUEUE_H

#include <iostream>

namespace s21 {

template <typename Type>
class queue {
  using value_type = Type;
  using reference = Type &;
  using const_reference = const Type &;
  using size_type = size_t;

 public:
  queue() : size_(0) {
    this->top_ = nullptr;
    this->end_ = nullptr;
  }

  queue(std::initializer_list<Type> const &l) : top_(nullptr), size_(0) {
    for (auto it : l) {
      this->Push(it);
    }
  }

  ~queue() { ClearQueue_(); }

  queue(const queue &q) : size_(0) {
    QueueElements_ *buf = q.top_;
    while (buf != nullptr) {
      this->Push(buf->stored_value);
      buf = buf->next_element;
    }
  }

  queue(queue &&q) : top_(q.top_), end_(q.end_), size_(q.size_) {
    q.top_ = nullptr;
    q.end_ = nullptr;
    q.size_ = 0;
  }

  queue &operator=(const queue &q) {
    if (*this == q) {
      return *this;
    }

    this->ClearQueue_();
    queue buf(q);
    *this = buf;
    return *this;
  }

  queue &operator=(queue &&q) {
    if (*this == q) {
      return *this;
    }

    this->ClearQueue_();
    this->top_ = q.top_;
    this->end_ = q.end_;
    this->size_ = q.size_;

    q.top_ = nullptr;
    q.end_ = nullptr;
    q.size_ = 0;
    return *this;
  }

  void Swap(queue &other) {
    queue buf(std::move(other));
    other = std::move(*this);
    *this = std::move(buf);
  }

  const_reference Front() { return this->top_->stored_value; }

  const_reference Back() { return this->end_->stored_value; }

  bool Empty() {
    if (this->size_ == 0) {
      return rSUCCESS;
    }

    return rFAIL;
  }

  size_type Size() { return this->size_; }

  void Push(const_reference value) {
    if (size_ != 0) {
      QueueElements_ *new_element = new QueueElements_;
      new_element->stored_value = value;
      new_element->next_element = nullptr;
      this->end_->next_element = new_element;
      this->end_ = new_element;
    } else {
      this->top_ = new QueueElements_;
      this->top_->stored_value = value;
      this->top_->next_element = nullptr;
      this->end_ = this->top_;
    }
    this->size_ += 1;
  }

  void Pop() {
    if (this->top_ != nullptr) {
      if (this->top_ == this->end_) {
        this->end_ = nullptr;
      }
      QueueElements_ *buf = this->top_->next_element;
      delete this->top_;
      this->top_ = buf;
      this->size_ -= 1;
    }
  }

  bool operator==(const queue &other) {
    if (this->size_ != other.size_) {
      return rFAIL;
    }

    QueueElements_ *buf_1 = this->top_;
    QueueElements_ *buf_2 = other.top_;

    while (buf_1 != nullptr) {
      if (buf_1->stored_value != buf_2->stored_value) {
        return rFAIL;
      }
      buf_1 = buf_1->next_element;
      buf_2 = buf_2->next_element;
    }

    return rSUCCESS;
  }

  template <typename... Types>
  void insert_many_back(Types &&...args) {
    for (Type i : {Type(args)...}) {
      this->Push(i);
    }
  }

 private:
  void ClearQueue_() {
    while (this->top_ != nullptr && this->size_ != 0) {
      this->Pop();
    }
  }

  struct QueueElements_ {
    Type stored_value;
    QueueElements_ *next_element;
  };

  QueueElements_ *top_;
  QueueElements_ *end_;
  size_type size_;

  enum { rFAIL, rSUCCESS };
};
};  // namespace s21

#endif
