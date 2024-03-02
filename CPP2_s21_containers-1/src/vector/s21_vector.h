#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstdarg>
#include <iostream>
#include <tuple>
#include <vector>

namespace s21 {

template <typename Type>
class vector {
 public:
  vector();
  vector(int length);
  vector(int length, Type variable);
  vector(std::initializer_list<Type> nameList);
  vector(s21::vector<Type> &copy);
  vector(s21::vector<Type> *copy);
  ~vector();

  Type operator[](int i);
  Type *At(int i);
  Type *front();
  Type *Back();
  bool Empty();
  int capacity();
  int size();
  void clear();
  void erase(int index);
  void erase(int index_1, int index_2);
  void push_back(Type value);

  struct vector_iterator {
    vector_iterator();
    vector_iterator(Type *l);
    vector_iterator(s21::vector<Type>::vector_iterator &other);

    Type operator*();
    void operator++();
    void operator--();
    void operator=(Type *a);
    void operator=(s21::vector<Type>::vector_iterator a);
    friend bool operator==(vector_iterator a, vector_iterator b) {
      return a.m_ptr == b.m_ptr;
    };
    friend bool operator!=(vector_iterator a, vector_iterator b) {
      return a.m_ptr != b.m_ptr;
    };
    Type *m_ptr;
  };

  template <typename... Types>
  void insert_many(vector_iterator pos, Types &&...args);

 private:
  long unsigned int massive_size;
  long unsigned int elements_size;
  Type *massive;
};

template <typename Type>
s21::vector<Type>::vector() {
  massive_size = 100;
  elements_size = 0;
  try {
    massive = new Type[100];
  } catch (...) {
    std::cout << "Memory allocation error." << std::endl;
    massive_size = 0;
    massive = nullptr;
  }
}

template <typename Type>
s21::vector<Type>::vector(int length) {
  if (length < 0) {
    throw std::invalid_argument{"Impossible list length."};
  }
  this->massive_size = length;
  this->elements_size = 0;
  try {
    massive = new Type[length];
  } catch (...) {
    std::cout << "Memory allocation error." << std::endl;
    massive_size = 0;
    massive = nullptr;
  }
}

template <typename Type>
s21::vector<Type>::vector(int length, Type variable) {
  if (length < 0) {
    throw std::invalid_argument{"Impossible list length."};
  }
  this->massive_size = length;
  this->elements_size = length;
  try {
    massive = new Type[length];
    for (int i = 0; i < length; i++) {
      massive[i] = variable;
    }
  } catch (...) {
    std::cout << "Memory allocation error." << std::endl;
    massive_size = 0;
    elements_size = 0;
    massive = nullptr;
  }
}

template <typename Type>
s21::vector<Type>::vector(std::initializer_list<Type> nameList) {
  const Type *pointer = nameList.begin();
  this->massive_size = nameList.size();
  this->elements_size = nameList.size();
  try {
    massive = new Type[nameList.size()];
    for (long unsigned int i = 0; i < nameList.size(); i++) {
      massive[i] = *pointer;
      ++pointer;
    }
  } catch (...) {
    std::cout << "Memory allocation error." << std::endl;
    massive_size = 0;
    elements_size = 0;
    massive = nullptr;
  }
}

template <typename Type>
s21::vector<Type>::vector(s21::vector<Type> &copy) {
  this->massive_size = copy.massive_size;
  this->elements_size = copy.elements_size;
  try {
    this->massive = new Type[copy.massive_size];
    for (long unsigned int i = 0; i < copy.massive_size; i++) {
      massive[i] = copy.massive[i];
    }
  } catch (...) {
    std::cout << "Memory allocation error." << std::endl;
    massive_size = 0;
    elements_size = 0;
    massive = nullptr;
  }
}

template <typename Type>
s21::vector<Type>::vector(s21::vector<Type> *copy) {
  this->massive_size = copy->massive_size;
  this->elements_size = copy->elements_size;
  this->massive = copy->massive;
  copy->massive_size = 0;
  copy->elements_size = 0;
  copy->massive = nullptr;
}

template <typename Type>
s21::vector<Type>::~vector() {
  this->massive_size = 0;
  this->elements_size = 0;
  delete[] this->massive;
  this->massive = nullptr;
}

template <typename Type>
Type s21::vector<Type>::operator[](int i) {
  if ((long unsigned int)i >= elements_size) {
    throw std::out_of_range{"Incorrect index."};
  }
  return massive[i];
}

template <typename Type>
Type *s21::vector<Type>::At(int i) {
  if ((long unsigned int)i >= elements_size) {
    throw std::out_of_range{"Incorrect index."};
  }
  return &massive[i];
}

template <typename Type>
Type *s21::vector<Type>::front() {
  if (massive_size == 0) {
    return nullptr;
  } else {
    return &massive[0];
  }
}

template <typename Type>
Type *s21::vector<Type>::Back() {
  if (massive_size == 0) {
    return nullptr;
  } else {
    return &massive[elements_size - 1];
  }
}

template <typename Type>
bool s21::vector<Type>::Empty() {
  if (elements_size == 0) {
    return true;
  } else {
    return false;
  }
}

template <typename Type>
int s21::vector<Type>::capacity() {
  return massive_size;
}

template <typename Type>
int s21::vector<Type>::size() {
  return elements_size;
}

template <typename Type>
void s21::vector<Type>::clear() {
  this->elements_size = 0;
}

template <typename Type>
void s21::vector<Type>::erase(int index) {
  if (this->size() <= 0) {
    throw std::invalid_argument{"Impossible list length."};
  } else if (index >= this->size()) {
    throw std::invalid_argument{"Range out of bounds."};
  } else if (index < 0) {
    throw std::invalid_argument{"Impossible index."};
  }
  for (long unsigned int i = index; i < elements_size - 1; i++) {
    massive[i] = massive[i + 1];
  }
  this->elements_size -= 1;
}

template <typename Type>
void s21::vector<Type>::erase(int index_1, int index_2) {
  if (this->size() <= 0) {
    throw std::invalid_argument{"Impossible list length."};
  } else if (index_1 >= this->size() || index_2 >= this->size()) {
    throw std::invalid_argument{"Range out of bounds."};
  } else if (index_2 < index_1) {
    throw std::invalid_argument{"Start index is bigger than end index."};
  } else if (index_1 < 0 || index_2 < 0) {
    throw std::invalid_argument{"Impossible index."};
  }
  for (long unsigned int i = index_1;
       i + (index_2 - index_1) + 1 < elements_size; i++) {
    massive[i] = massive[i + (index_2 - index_1) + 1];
  }
  this->elements_size -= index_2 - index_1 + 1;
}

template <typename Type>
void s21::vector<Type>::push_back(Type value) {
  if (massive_size == elements_size) {
    try {
      Type *temp = massive;
      massive = new Type[massive_size + 50];
      for (long unsigned int i = 0; i < massive_size; i++) {
        massive[i] = temp[i];
      }
      massive[elements_size] = value;
      massive_size += 50;
      elements_size += 1;
      delete[] temp;
    } catch (...) {
      std::cout << "Memory allocation error." << std::endl;
    }
  } else {
    massive[elements_size] = value;
    elements_size += 1;
  }
}

template <typename Type>
s21::vector<Type>::vector_iterator::vector_iterator() {
  m_ptr = nullptr;
}

template <typename Type>
s21::vector<Type>::vector_iterator::vector_iterator(Type *l) {
  m_ptr = l;
}

template <typename Type>
s21::vector<Type>::vector_iterator::vector_iterator(
    s21::vector<Type>::vector_iterator &other) {
  m_ptr = other.m_ptr;
}

template <typename Type>
Type s21::vector<Type>::vector_iterator::operator*() {
  if (m_ptr != nullptr) {
    return *m_ptr;
  } else {
    return (Type)NULL;
  }
}

template <typename Type>
void s21::vector<Type>::vector_iterator::operator++() {
  ++m_ptr;
}

template <typename Type>
void s21::vector<Type>::vector_iterator::operator--() {
  --m_ptr;
}

template <typename Type>
void s21::vector<Type>::vector_iterator::operator=(Type *a) {
  this->m_ptr = a;
}

template <typename Type>
void s21::vector<Type>::vector_iterator::operator=(
    s21::vector<Type>::vector_iterator a) {
  this->m_ptr = a.m_ptr;
}

template <typename Type>
template <typename... Types>
void s21::vector<Type>::insert_many(vector_iterator pos, Types &&...args) {
  long unsigned int counter = 0;
  s21::vector<Type> first;
  s21::vector<Type> second({args...});
  s21::vector<Type> third;
  s21::vector<Type>::vector_iterator pointer(this->front());
  s21::vector<Type>::vector_iterator position_copy(pos);
  while (pointer != pos) {
    if ((int)counter >= this->size()) {
      throw std::out_of_range{"Iterator is out of bounds."};
    }
    ++pointer;
    counter += 1;
  }
  while (this->size() + second.size() > this->capacity()) {
    Type *temp = massive;
    massive = new Type[this->massive_size + 50];
    for (long unsigned int i = 0; i < massive_size; i++) {
      massive[i] = temp[i];
    }
    massive_size += 50;
    delete[] temp;
  }
  pos = this->At(counter);
  for (long unsigned int i = 0; i < counter; i++) {
    first.push_back(this->massive[i]);
  }
  for (; counter < this->elements_size; counter++) {
    third.push_back(this->massive[counter]);
  }
  this->clear();
  for (int i = 0; i < first.size(); i++) {
    this->push_back(first[i]);
  }
  for (int i = 0; i < second.size(); i++) {
    this->push_back(second[i]);
  }
  for (int i = 0; i < third.size(); i++) {
    this->push_back(third[i]);
  }
}

}  // namespace s21

#endif  // VECTOR_H_
