#ifndef LIST_H_
#define LIST_H_

#include <cstdarg>
#include <iostream>
#include <string>
#include <typeinfo>
// строка 91 с инициализацией кондишинал дажмпа может начать шалить со строками
namespace s21 {

template <typename Type>
struct list_elem {
  Type data;
  list_elem *next = nullptr, *prev = nullptr;
};

template <typename Type>
struct list_iterator {
  list_iterator();
  list_iterator(list_elem<Type> *l);
  list_iterator(s21::list_iterator<Type> *other);

  Type operator*();
  void operator++();
  void operator--();
  void operator=(list_elem<Type> *l) { this->m_ptr = l; };
  friend bool operator==(list_iterator a, list_iterator b) {
    return a.m_ptr == b.m_ptr;
  };
  friend bool operator!=(list_iterator a, list_iterator b) {
    return a.m_ptr != b.m_ptr;
  };

  list_elem<Type> *m_ptr;
};

template <typename Type>
class list {
 public:
  list();
  list(int Size);
  list(int Size, Type value);
  list(std::initializer_list<Type> nameList);
  list(s21::list<Type> &other);
  list(s21::list<Type> *other);
  ~list();

  Type operator[](int i) { return get_element(i); }

  Type get_element(int index);
  list_elem<Type> *get_beginning() { return begin; };
  list_elem<Type> *get_beginning_next() { return begin->next; };
  list_elem<Type> *get_end() { return end; };
  list_elem<Type> *get_end_prev() { return end->prev; };

  void push_back(Type end);
  void push_front(Type val);
  int Size();
  bool is_empty();
  void pop_back();
  void pop_front();
  void erase(int index);
  void erase(int index_1, int index_2);

  list_iterator<Type> first();
  list_iterator<Type> last();

  template <typename... Types>
  void insert_many(s21::list_iterator<Type> pos, Types &&...args);

 private:
  list_elem<Type> *begin, *end;
};

template <typename Type>
s21::list<Type>::list() {
  begin = nullptr;
  end = nullptr;
}

template <typename Type>
s21::list<Type>::list(int Size) {
  if (Size < 0) {
    throw std::invalid_argument{"Impossible list length."};
  } else if (Size == 0) {
    begin = nullptr;
    end = nullptr;
  } else if (Size == 1) {
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->data = (Type)0;
    end->data = (Type)0;
    begin->prev = nullptr;
    begin->next = nullptr;
    end->prev = nullptr;
    end->next = nullptr;
  } else {
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->data = (Type)0;
    end->data = (Type)0;
    begin->prev = nullptr;
    begin->next = end;
    end->prev = begin;
    end->next = nullptr;
    for (int i = 2; i < Size; i++) {
      push_back(begin->data);
    }
  }
}

template <typename Type>
s21::list<Type>::list(int Size, Type value) {
  if (Size < 0) {
    throw std::invalid_argument{"Impossible list length."};
  } else if (Size == 0) {
    begin = nullptr;
    end = nullptr;
  } else if (Size == 1) {
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->prev = nullptr;
    begin->next = nullptr;
    begin->data = value;
    end->prev = nullptr;
    end->next = nullptr;
    end->data = value;
  } else {
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->prev = nullptr;
    begin->next = end;
    begin->data = value;
    end->prev = begin;
    end->next = nullptr;
    end->data = value;
    for (int i = 2; i < Size; i++) {
      push_back(value);
    }
  }
}

template <typename Type>
s21::list<Type>::list(std::initializer_list<Type> nameList) {
  const Type *temp_p = nullptr;
  if (nameList.size() == 0) {
    begin = nullptr;
    end = nullptr;
  } else if (nameList.size() == 1) {
    temp_p = nameList.begin();
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->prev = nullptr;
    begin->next = nullptr;
    begin->data = *temp_p;
    end->prev = nullptr;
    end->next = nullptr;
    end->data = *temp_p;
  } else {
    s21::list_elem<Type> *temp = new list_elem<Type>;
    temp_p = nameList.begin();
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->prev = nullptr;
    begin->next = end;
    end->prev = begin;
    end->next = nullptr;
    for (long unsigned int i = 2; i < nameList.size(); i++) {
      push_back(begin->data);
    }
    temp->next = begin;
    for (long unsigned int i = 0; i < nameList.size(); i++) {
      temp->next->data = *temp_p;
      temp->next = temp->next->next;
      temp_p++;
    }
    delete temp;
  }
}

template <typename Type>
s21::list<Type>::list(s21::list<Type> &other) {
  s21::list_elem<Type> *temp1 = new list_elem<Type>;
  s21::list_elem<Type> *temp2 = new list_elem<Type>;
  if (other.Size() == 0) {
    begin = nullptr;
    end = nullptr;
  } else if (other.Size() == 1) {
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->data = other.begin->data;
    begin->prev = nullptr;
    begin->next = nullptr;
    end->prev = nullptr;
    end->next = nullptr;
  } else {
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->prev = nullptr;
    begin->next = end;
    end->prev = begin;
    end->next = nullptr;
    temp1->next = begin;
    temp2->next = other.begin;
    for (int i = 2; i < other.Size(); i++) {
      push_back(begin->data);
    }
    for (int i = 0; i < other.Size(); i++) {
      temp1->next->data = temp2->next->data;
      temp1->next = temp1->next->next;
      temp2->next = temp2->next->next;
    }
  }
  delete temp1;
  delete temp2;
}

template <typename Type>
s21::list<Type>::list(s21::list<Type> *other) {
  this->begin = other->begin;
  this->end = other->end;
  other->begin = nullptr;
  other->end = nullptr;
  other->~list();
}

template <typename Type>
s21::list<Type>::~list() {
  if (this->Size() == 0) {
    this->begin = nullptr;
    this->end = nullptr;
  } else if (this->Size() == 1) {
    delete this->begin;
    delete this->end;
    this->begin = nullptr;
    this->end = nullptr;
  } else {
    /*for (int i = 0; i < this->Size() ; i++) {
        std::cout << "\n Delete list item " << this->get_element(i) << "\n";
    }*/
    s21::list_elem<Type> *temp = this->get_beginning();
    while (temp->next != nullptr) {
      temp = temp->next;
      delete temp->prev;
    }
    delete temp;
    this->begin = nullptr;
    this->end = nullptr;
  }
}

template <typename Type>
void s21::list<Type>::push_back(Type val) {
  if (this->begin == nullptr) {
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->data = val;
    begin->prev = nullptr;
    begin->next = nullptr;
    end->prev = nullptr;
    end->next = nullptr;
  } else if (this->begin->next == nullptr) {
    this->end->data = val;
    this->end->prev = this->begin;
    this->begin->next = this->end;
  } else {
    list_elem<Type> *middle = new list_elem<Type>;
    middle->data = val;
    middle->next = nullptr;
    middle->prev = this->end;
    this->end->next = middle;
    this->end = middle;
  }
}

template <typename Type>
void s21::list<Type>::push_front(Type val) {
  if (this->begin == nullptr) {
    begin = new list_elem<Type>;
    end = new list_elem<Type>;
    begin->data = val;
    begin->prev = nullptr;
    begin->next = nullptr;
    end->prev = nullptr;
    end->next = nullptr;
  } else if (this->begin->next == nullptr) {
    this->end->data = this->begin->data;
    this->begin->data = val;
    this->end->prev = this->begin;
    this->begin->next = this->end;
  } else {
    list_elem<Type> *middle = new list_elem<Type>;
    middle->data = val;
    middle->next = this->begin;
    middle->prev = nullptr;
    this->begin->prev = middle;
    this->begin = middle;
  }
}

template <typename Type>
int s21::list<Type>::Size() {
  s21::list_elem<Type> *temp = new list_elem<Type>;
  int counter = 0;
  temp->next = begin;
  if (begin == nullptr) {
    delete temp;
    return counter;
  } else {
    while (temp->next != nullptr) {
      counter += 1;
      temp->next = temp->next->next;
    }
    delete temp;
    return counter;
  }
}

template <typename Type>
Type s21::list<Type>::get_element(int index) {
  Type result;
  s21::list_elem<Type> *temp = new list_elem<Type>;
  if (this->Size() <= 0) {
    delete temp;
    throw std::invalid_argument{"Impossible list length."};
  } else if (index >= this->Size()) {
    delete temp;
    throw std::invalid_argument{"Range out of bounds."};
  } else if (index < 0) {
    delete temp;
    throw std::invalid_argument{"Impossible index."};
  }
  temp->next = begin;
  temp->data = temp->next->data;
  for (int i = 0; i < index; i++) {
    temp->next = temp->next->next;
    temp->data = temp->next->data;
  }
  result = temp->data;
  delete temp;
  return result;
}

template <typename Type>
bool s21::list<Type>::is_empty() {
  return this->begin == nullptr;
}

template <typename Type>
void s21::list<Type>::pop_back() {
  if (this->is_empty()) {
    throw std::logic_error{"List is empty."};
  } else if (this->begin->next == this->end) {
    this->begin->next = nullptr;
  } else if (this->begin->next == nullptr) {
    delete this->begin;
    delete this->end;
    this->begin = nullptr;
    this->end = nullptr;
  } else {
    this->end = this->end->prev;
    delete this->end->next;
    this->end->next = nullptr;
  }
}

template <typename Type>
void s21::list<Type>::pop_front() {
  if (this->is_empty()) {
    throw std::logic_error{"List is empty."};
  } else if (this->begin->next == this->end) {
    this->begin->next = nullptr;
    this->begin->data = this->end->data;
  } else if (this->begin->next == nullptr) {
    delete this->begin;
    delete this->end;
    this->begin = nullptr;
    this->end = nullptr;
  } else {
    this->begin = this->begin->next;
    delete this->begin->prev;
    this->begin->prev = nullptr;
  }
}

template <typename Type>
void s21::list<Type>::erase(int index) {
  s21::list_elem<Type> *temp = new list_elem<Type>;
  if (this->Size() <= 0) {
    delete temp;
    throw std::invalid_argument{"Impossible list length."};
  } else if (index >= this->Size()) {
    delete temp;
    throw std::invalid_argument{"Range out of bounds."};
  } else if (index == 0) {
    this->pop_front();
  } else if (index == this->Size() - 1) {
    this->pop_back();
  } else {
    temp->next = begin;
    for (int i = 0; i < index; i++) {
      temp->next = temp->next->next;
    }
    temp->next->prev->next = temp->next->next;
    temp->next->next->prev = temp->next->prev;
    delete temp->next;
  }
  delete temp;
}

template <typename Type>
void s21::list<Type>::erase(int index_1, int index_2) {
  s21::list_elem<Type> *temp_1 = new list_elem<Type>;
  s21::list_elem<Type> *temp_2 = new list_elem<Type>;
  if (this->Size() <= 0) {
    delete temp_1;
    delete temp_2;
    throw std::invalid_argument{"Impossible list length."};
  } else if (index_1 >= this->Size() || index_2 >= this->Size()) {
    delete temp_1;
    delete temp_2;
    throw std::invalid_argument{"Range out of bounds."};
  } else if (index_2 < index_1) {
    delete temp_1;
    delete temp_2;
    throw std::invalid_argument{"Start index is bigger than end index."};
  } else {
    temp_1->next = begin;
    temp_2->next = begin;
    for (int i = 0; i < index_1; i++) {
      temp_1->next = temp_1->next->next;
    }
    for (int i = 0; i < index_2; i++) {
      temp_2->next = temp_2->next->next;
    }
    if (index_1 == 0 && index_2 == this->Size() - 1) {
      s21::list_elem<Type> *temp = this->get_beginning();
      while (temp->next != nullptr) {
        temp = temp->next;
        delete temp->prev;
      }
      delete temp;
      this->begin = nullptr;
      this->end = nullptr;
    } else if (index_1 == 0) {
      s21::list_elem<Type> *temp = this->get_beginning();
      temp_2->next->next->prev = nullptr;
      this->begin = temp_2->next->next;
      while (temp != temp_2->next) {
        temp = temp->next;
        delete temp->prev;
      }
      delete temp;
      if (this->begin == this->end) {
        this->end = new list_elem<Type>;
        end->data = (Type)0;
        begin->prev = nullptr;
        begin->next = nullptr;
        end->prev = nullptr;
        end->next = nullptr;
      }
    } else if (index_2 == this->Size() - 1) {
      s21::list_elem<Type> *temp = temp_1->next;
      temp_1->next->prev->next = nullptr;
      this->end = temp_1->next->prev;
      while (temp->next != nullptr) {
        temp = temp->next;
        delete temp->prev;
      }
      delete temp;
      if (this->begin == this->end) {
        this->begin = this->end;
        this->end = new list_elem<Type>;
        end->data = (Type)0;
        begin->prev = nullptr;
        begin->next = nullptr;
        end->prev = nullptr;
        end->next = nullptr;
      }
    } else {
      s21::list_elem<Type> *temp = temp_1->next;
      temp_1->next->prev->next = temp_2->next->next;
      temp_2->next->next->prev = temp_1->next->prev;
      while (temp != temp_2->next) {
        temp = temp->next;
        delete temp->prev;
      }
      delete temp;
    }
  }
  delete temp_1;
  delete temp_2;
}

template <typename Type>
list_iterator<Type> s21::list<Type>::first() {
  s21::list_iterator<Type> result(this->begin);
  return result;
}

template <typename Type>
list_iterator<Type> s21::list<Type>::last() {
  s21::list_iterator<Type> result(this->end);
  return result;
}

template <typename Type>
s21::list_iterator<Type>::list_iterator() {
  m_ptr = nullptr;
}

template <typename Type>
s21::list_iterator<Type>::list_iterator(list_elem<Type> *l) {
  m_ptr = l;
}

template <typename Type>
s21::list_iterator<Type>::list_iterator(s21::list_iterator<Type> *other) {
  m_ptr = other->m_ptr;
}

template <typename Type>
Type s21::list_iterator<Type>::operator*() {
  if (m_ptr != nullptr) {
    return m_ptr->data;
  } else {
    return (Type)NULL;
  }
}

template <typename Type>
void s21::list_iterator<Type>::operator++() {
  if (m_ptr == nullptr) {
    m_ptr = nullptr;
  } else if (m_ptr->next == nullptr) {
    while (m_ptr->prev != nullptr) {
      m_ptr = m_ptr->prev;
    }
  } else {
    m_ptr = m_ptr->next;
  }
}

template <typename Type>
void s21::list_iterator<Type>::operator--() {
  if (m_ptr == nullptr) {
    m_ptr = nullptr;
  } else if (m_ptr->prev == nullptr) {
    while (m_ptr->next != nullptr) {
      m_ptr = m_ptr->next;
    }
  } else {
    m_ptr = m_ptr->prev;
  }
}

template <typename Type>
template <typename... Types>
void s21::list<Type>::insert_many(s21::list_iterator<Type> pos,
                                  Types &&...args) {
  s21::list<Type> new_massive({args...});
  if (pos.m_ptr->prev == nullptr) {
    this->begin->prev = new_massive.get_end();
    this->begin->prev->next = this->begin;
    this->begin = new_massive.get_beginning();
    new_massive.begin = nullptr;
    new_massive.end = nullptr;
  } else {
    s21::list_elem<Type> *temp = this->end;
    this->end = pos.m_ptr->prev;
    this->end->next = nullptr;
    for (int i = 0; i < new_massive.Size(); i++) {
      this->push_back(new_massive[i]);
    }
    this->end->next = pos.m_ptr;
    pos.m_ptr->prev = this->end;
    this->end = temp;
  }
}

}  // namespace s21

#endif  // LIST_H_
