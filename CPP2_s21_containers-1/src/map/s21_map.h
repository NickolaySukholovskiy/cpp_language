#ifndef S21_MAP_H
#define S21_MAP_H

#include <iostream>

#include "../s21_containers.h"
#include "s21_binary_tree.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = typename std::pair<const key_type, mapped_type>;
  using reference = value_type;
  using cosnt_reference = const value_type&;
  using iterator = typename S21RBTree<Key, T>::Iterator;

 public:
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map<Key, T>&);
  map(map&& other);

  ~map();

  void operator=(map&&);

  T& At(const key_type key);
  T& operator[](const key_type& key);
  bool Contains(const Key& key);

  iterator Begin();
  iterator Begin() const;

  iterator End();
  iterator End() const;

  bool Empty() noexcept;
  size_t Size() noexcept;

  void Clear();
  std::pair<iterator, bool> Insert(const value_type& value);
  std::pair<iterator, bool> Insert(const Key& key, const T& obj);
  std::pair<iterator, bool> InsertOrAssign(const Key& key, const T& obj);
  template <typename... Types>
  vector<std::pair<iterator, bool>> InsertMany(Types&&... args);

  void Erase(iterator pos);
  void Swap(map& other);
  void Merge(map& other);

  void PrintMap();

 private:
  S21RBTree<Key, T>* tree_;
};

template <typename Key, typename T>
map<Key, T>::map() : tree_(new S21RBTree<Key, T>()) {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items)
    : tree_(new S21RBTree<Key, T>()) {
  for (const value_type *inListPtr = items.begin(), *listEnd = items.end();
       inListPtr != listEnd; inListPtr++) {
    Insert(*inListPtr);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map<Key, T>& other) : tree_(new S21RBTree<Key, T>()) {
  for (iterator iter = other.Begin(), iterEnd = other.End(); iter != iterEnd;
       ++iter) {
    Insert(*iter);
  }
}

template <typename Key, typename T>
map<Key, T>::map(map&& other) {
  tree_ = other.tree_;
  other.tree_ = nullptr;
}

template <typename Key, typename T>
map<Key, T>::~map() {
  delete tree_;
}

template <typename Key, typename T>
T& map<Key, T>::At(const key_type key) {
  S21RBTreeNode<Key, T>* node = tree_->Find(key);
  if (node == nullptr) {
    throw std::out_of_range("The tree doesn't contain the passed key");
  }
  return node->GetValue();
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const key_type& key) {
  S21RBTreeNode<Key, T>* node = tree_->Find(key);
  if (node == nullptr) {
    throw std::out_of_range("The tree doesn't contain the passed key");
  }
  return node->GetValue();
}

template <typename Key, typename T>
bool map<Key, T>::Empty() noexcept {
  return tree_->Empty();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::Insert(
    const Key& key, const T& obj) {
  if (Contains(key) == true)
    return std::pair<iterator, bool>(iterator(tree_, nullptr), false);
  S21RBTreeNode<Key, T>* node = tree_->Insert(key, obj);
  bool isInserted = (node != nullptr ? true : false);
  return std::pair<iterator, bool>(iterator(tree_, node), isInserted);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::Insert(
    const value_type& value) {
  return Insert(value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::InsertOrAssign(
    const Key& key, const T& obj) {
  S21RBTreeNode<Key, T>* node = tree_->Find(key);

  if (node != nullptr) {
    node->SetValue(obj);
    return std::pair<iterator, bool>(iterator(tree_, node), true);
  } else {
    return Insert(key, obj);
  }
}

// TODO: identify how this shit works
template <typename Key, typename T>
void map<Key, T>::Erase(iterator pos) {
  if (pos == nullptr) {
    throw std::out_of_range("Iterator is nullptr");
  }
  tree_->Delete(pos);
}

template <typename Key, typename T>
void map<Key, T>::operator=(map<Key, T>&& other) {
  delete tree_;
  tree_ = other.tree_;
  other.tree_ = nullptr;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::Begin() {
  return tree_->Begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::End() {
  return tree_->End();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::Begin() const {
  return tree_->Begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::End() const {
  return tree_->End();
}

template <typename Key, typename T>
void map<Key, T>::PrintMap() {
  tree_->PrintTree();
}

template <typename Key, typename T>
size_t map<Key, T>::Size() noexcept {
  iterator iter = tree_->Begin();
  size_t Size = 0;
  for (; iter != tree_->End(); ++iter) {
    ++Size;
  }
  return Size;
}

template <typename Key, typename T>
bool map<Key, T>::Contains(const Key& key) {
  return tree_->Find(key) != nullptr;
}

template <typename Key, typename T>
void map<Key, T>::Merge(map<Key, T>& other) {
  for (iterator it = other.Begin(); it != other.End();) {
    if (Contains((*it).first) == false) {
      Insert(*it);
      other.Erase(it);
      it = other.Begin();
    } else {
      ++it;
    }
  }
}

template <typename Key, typename T>
void map<Key, T>::Swap(map& other) {
  if (this != &other) {
    std::swap(tree_, other.tree_);
  }
}

template <typename Key, typename T>
template <typename... Types>
vector<std::pair<typename map<Key, T>::iterator, bool>> map<Key, T>::InsertMany(
    Types&&... args) {
  std::pair<iterator, bool> returnedPair;
  vector<std::pair<iterator, bool>> returnVec;

  for (value_type i : {value_type(args)...}) {
    returnedPair = Insert(i);
    returnVec.push_back(returnedPair);
  }
  return returnVec;
}

template <typename Key, typename T>
void map<Key, T>::Clear() {
  tree_->RemoveTreeInPostOrder();
}

}  // namespace s21
#endif