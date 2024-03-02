#ifndef S21_MULTISET
#define S21_MULTISET
#include "../set/s21_set.h"

namespace s21 {

template <class Key>
class multiset : public set<Key> {
 public:
  multiset() {}
  multiset(const multiset& s);
  multiset(multiset&& s);
  multiset(std::initializer_list<Key> const& items);
  std::pair<typename set<Key>::iterator, bool> Insert(const Key& value);
  ~multiset() {}
};

template <class Key>
multiset<Key>::multiset(const multiset& s) : set<Key>() {
  for (typename set<Key>::iterator it = s.Begin(); it != s.End(); ++it) {
    this->Insert(*it);
  }
}

template <class Key>
multiset<Key>::multiset(multiset&& s) {
  delete this->data_;
  this->data_ = s.data_;
  s.data_ = nullptr;
}

template <class Key>
multiset<Key>::multiset(std::initializer_list<Key> const& items) {
  for (const Key* list_ptr = items.begin(); list_ptr != items.end();
       list_ptr++) {
    this->Insert(*list_ptr);
  }
}

template <class Key>
std::pair<typename set<Key>::iterator, bool> multiset<Key>::Insert(
    const Key& value) {
  bool res = true;
  typename set<Key>::RBTree::iterator r_it(set<Key>::data_->Insert(value));
  std::pair<typename set<Key>::RBTree::iterator, bool> r_p{r_it, res};
  return r_p;
}

}  // namespace s21

#endif
