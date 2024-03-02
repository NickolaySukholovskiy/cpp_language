#ifndef S21_SET_H
#define S21_SET_H

#include <iostream>
#include <vector>

#define MAX_SIZE 461168601842738790

namespace s21 {

template <class Key>
class set {
 public:
  typedef Key value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  // nested Red-Black Binary Tree class
  class RBTree;
  typedef typename RBTree::RBTreeNode node_type;
  typedef typename RBTree::iterator iterator;
  // default constructor, creates Empty set
  set();
  // initializer list constructor, creates the set initizialized using
  // std::initializer_list
  set(std::initializer_list<value_type> const& items);
  // copy constructor
  set(const set& s);
  // move constructor
  set(set&& s);
  // assignment operator overload for moving object
  set<Key>& operator=(set&& s);
  // destructor
  ~set();
  // Set Iterators
  iterator Begin() const;
  iterator End() const;
  // Set Capacity
  bool Empty() const noexcept;
  size_type Size() const noexcept;
  size_type Max_size() const noexcept;
  // Set Modifiers
  void Clear() noexcept;
  std::pair<iterator, bool> Insert(const_reference value);
  void Erase(iterator pos);
  void Swap(set<Key>& other);
  void Merge(set& other);
  // Set Lookup
  size_type Count(const_reference key) const;
  iterator Find(const_reference key) const;
  bool Contains(const_reference key) const;
  std::pair<iterator, iterator> Equal_range(const_reference key) const;
  iterator Lower_bound(const_reference key) const;
  iterator Upper_bound(const_reference key) const;
  // Inserts new elements into the container
  template <class... Keys>
  std::vector<std::pair<iterator, bool>> Insert_many(Keys&&... args);

 protected:
  RBTree* data_;
};

template <class Key>
class set<Key>::RBTree {
 public:
  enum RBTreeColor { Black, Red };

  struct RBTreeNode {
    Key key_;
    RBTreeColor color_;
    RBTreeNode* left_;
    RBTreeNode* right_;
    RBTreeNode* parent_;
    RBTreeNode()
        : color_(Red), left_(nullptr), right_(nullptr), parent_(nullptr){};
    RBTreeNode(Key k, RBTreeColor c, RBTreeNode* p, RBTreeNode* l,
               RBTreeNode* r)
        : key_(k), color_(c), left_(l), right_(r), parent_(p){};
  };

  class iterator;

  RBTree();
  ~RBTree();
  RBTreeNode* Insert(Key key);
  void Remove(Key key);
  RBTreeNode* Search(Key key);
  RBTreeNode* Min();
  RBTreeNode* Max();
  void Destroy();

 private:
  void leftRotate(RBTreeNode*& root, RBTreeNode* x);
  void rightRotate(RBTreeNode*& root, RBTreeNode* y);

  RBTreeNode* Insert(RBTreeNode*& root, RBTreeNode* node);
  void InsertFixUp(RBTreeNode*& root, RBTreeNode* node);

  void Remove(RBTreeNode*& root, RBTreeNode* node);
  void RemoveFixUp(RBTreeNode*& root, RBTreeNode* node, RBTreeNode* parent);

  void Destroy(RBTreeNode*& node);

  RBTreeNode* Search(RBTreeNode* node, Key key) const;

  RBTreeNode* MinimalNode(RBTreeNode* subTreeRoot);
  RBTreeNode* MaximalNode(RBTreeNode* subTreeRoot);

  RBTreeNode* root_;
  RBTreeNode* header_;
};

template <class Key>
class set<Key>::RBTree::iterator {
 public:
  iterator() : node_(nullptr) {}
  iterator(RBTreeNode* other_node) : node_(other_node) {}
  iterator(const iterator& it) : node_(it.node_) {}
  iterator& operator=(const iterator& it);
  bool operator==(const iterator& it);
  bool operator!=(const iterator& it);
  iterator& operator++();
  iterator& operator--();
  Key& operator*() const { return node_->key_; }
  bool IsNull() { return !((bool)node_); }

 private:
  RBTreeNode* node_;
};

}  // namespace s21

template <class Key>
s21::set<Key>::set() {
  data_ = new RBTree;
}

template <class Key>
s21::set<Key>::set(std::initializer_list<value_type> const& items) {
  data_ = new RBTree;
  for (const value_type* list_ptr = items.begin(); list_ptr != items.end();
       list_ptr++) {
    this->Insert(*list_ptr);
  }
}

template <class Key>
s21::set<Key>::set(const set& s) {
  data_ = new RBTree;
  for (iterator it = s.Begin(); it != s.End(); ++it) {
    this->Insert(*it);
  }
}

template <class Key>
s21::set<Key>::set(set&& s) {
  data_ = s.data_;
  s.data_ = nullptr;
}

template <class Key>
s21::set<Key>& s21::set<Key>::operator=(set&& s) {
  if (data_) {
    delete data_;
    data_ = nullptr;
  }
  std::swap(data_, s.data_);
}

template <class Key>
s21::set<Key>::~set() {
  if (data_) {
    delete data_;
    data_ = nullptr;
  }
}

template <class Key>
typename s21::set<Key>::iterator s21::set<Key>::Begin() const {
  iterator it(data_->Min());
  return it;
}

template <class Key>
typename s21::set<Key>::iterator s21::set<Key>::End() const {
  iterator it(data_->Max());
  ++it;
  return it;
}

template <class Key>
bool s21::set<Key>::Empty() const noexcept {
  bool res = true;
  if (data_) {
    iterator it = this->Begin();
    return it.IsNull();
  }
  return res;
}

template <class Key>
typename s21::set<Key>::size_type s21::set<Key>::Size() const noexcept {
  size_type sz = 0;
  if (!Empty()) {
    for (iterator it = this->Begin(); it != this->End(); ++it) {
      sz++;
    }
  }
  return sz;
}

template <class Key>
typename s21::set<Key>::size_type s21::set<Key>::Max_size() const noexcept {
  return MAX_SIZE;
}

template <class Key>
void s21::set<Key>::Clear() noexcept {
  data_->Destroy();
}

template <class Key>
std::pair<typename s21::set<Key>::RBTree::iterator, bool> s21::set<Key>::Insert(
    const Key& value) {
  bool res = false;
  typename s21::set<Key>::RBTree::RBTreeNode* node = nullptr;
  if (data_->Search(value) == nullptr) {
    node = data_->Insert(value);
    res = true;
  }
  typename s21::set<Key>::RBTree::iterator r_it(node);
  std::pair<typename s21::set<Key>::RBTree::iterator, bool> r_p{r_it, res};
  return r_p;
}

template <class Key>  // TO FIX!
void s21::set<Key>::Erase(iterator pos) {
  if (pos == nullptr) {
    throw std::invalid_argument("Null iterator");
  } else {
    data_->Remove(*pos);
  }
}

template <class Key>
void s21::set<Key>::Swap(s21::set<Key>& other) {
  std::swap(data_, other.data_);
}

template <class Key>
void s21::set<Key>::Merge(set& other) {
  for (iterator it = other.Begin(), temp_it = other.Begin();
       it != other.End();) {
    if (!this->Contains(*it)) {
      this->Insert(*it);
      other.Erase(it);
      it = temp_it;
    } else {
      temp_it = it;
      ++it;
    }
  }
}

template <class Key>
typename s21::set<Key>::size_type s21::set<Key>::Count(
    const_reference key) const {
  size_type count = 0;
  if (!Empty()) {
    iterator it_1 = Lower_bound(key), it_2 = Upper_bound(key);
    for (; it_1 != End() && it_1 != it_2; ++it_1) {
      count++;
    }
  }
  return count;
}

template <class Key>
typename s21::set<Key>::iterator s21::set<Key>::Find(const Key& key) const {
  iterator r_it(data_->Search(key));
  return r_it;
}

template <class Key>
bool s21::set<Key>::Contains(const Key& key) const {
  return ((bool)data_->Search(key));
}

template <class Key>
std::pair<typename s21::set<Key>::RBTree::iterator,
          typename s21::set<Key>::RBTree::iterator>
s21::set<Key>::Equal_range(const Key& key) const {
  std::pair<iterator, iterator> range{Lower_bound(key), Upper_bound(key)};
  return range;
}

template <class Key>
typename s21::set<Key>::RBTree::iterator s21::set<Key>::Lower_bound(
    const Key& key) const {
  for (iterator it = Begin(); it != End(); ++it) {
    if (*it >= key) return it;
  }
  return End();
}

template <class Key>
typename s21::set<Key>::RBTree::iterator s21::set<Key>::Upper_bound(
    const Key& key) const {
  for (iterator it = Begin(); it != End(); ++it) {
    if (*it > key) return it;
  }
  return End();
}

template <class Key>
template <class... Keys>
std::vector<std::pair<typename s21::set<Key>::iterator, bool>>
s21::set<Key>::Insert_many(Keys&&... args) {
  std::vector<std::pair<iterator, bool>> ret_vect;
  for (const value_type key : {value_type(args)...}) {
    ret_vect.push_back(Insert(key));
  }
  return ret_vect;
}

template <class Key>
s21::set<Key>::RBTree::RBTree() : root_(nullptr) {
  header_ = new RBTreeNode;
}
template <class Key>
s21::set<Key>::RBTree::~RBTree() {
  Destroy(root_);
  delete header_;
}

template <class Key>
void s21::set<Key>::RBTree::leftRotate(s21::set<Key>::RBTree::RBTreeNode*& root,
                                       s21::set<Key>::RBTree::RBTreeNode* x) {
  s21::set<Key>::RBTree::RBTreeNode* y = x->right_;
  x->right_ = y->left_;
  if (y->left_ != nullptr) y->left_->parent_ = x;

  y->parent_ = x->parent_;
  if (x->parent_ == nullptr)
    root = y;
  else {
    if (x == x->parent_->left_)
      x->parent_->left_ = y;
    else
      x->parent_->right_ = y;
  }
  y->left_ = x;
  x->parent_ = y;
};

template <class Key>
void s21::set<Key>::RBTree::rightRotate(
    s21::set<Key>::RBTree::RBTreeNode*& root,
    s21::set<Key>::RBTree::RBTreeNode* y) {
  s21::set<Key>::RBTree::RBTreeNode* x = y->left_;
  y->left_ = x->right_;
  if (x->right_ != nullptr) x->right_->parent_ = y;

  x->parent_ = y->parent_;
  if (y->parent_ == nullptr)
    root = x;
  else {
    if (y == y->parent_->right_)
      y->parent_->right_ = x;
    else
      y->parent_->left_ = x;
  }
  x->right_ = y;
  y->parent_ = x;
};

template <class Key>
typename s21::set<Key>::RBTree::RBTreeNode* s21::set<Key>::RBTree::Insert(
    Key key) {
  s21::set<Key>::RBTree::RBTreeNode* z =
      new RBTreeNode(key, Red, nullptr, nullptr, nullptr);
  return Insert(root_, z);
};

template <class Key>
typename s21::set<Key>::RBTree::RBTreeNode* s21::set<Key>::RBTree::Insert(
    s21::set<Key>::RBTree::RBTreeNode*& root,
    s21::set<Key>::RBTree::RBTreeNode* node) {
  s21::set<Key>::RBTree::RBTreeNode* x = root;
  s21::set<Key>::RBTree::RBTreeNode* y = nullptr;  // header_;
  while (x != nullptr) {
    y = x;
    if (node->key_ > x->key_)
      x = x->right_;
    else
      x = x->left_;
  }
  node->parent_ = y;
  if (y != nullptr) {  //!= header_
    if (node->key_ > y->key_)
      y->right_ = node;
    else
      y->left_ = node;
  } else {
    root = node;
    header_->left_ = root;
    root->parent_ = header_;
  }
  node->color_ = Red;

  InsertFixUp(root, node);
  return node;
};
template <class Key>
void s21::set<Key>::RBTree::InsertFixUp(
    s21::set<Key>::RBTree::RBTreeNode*& root,
    s21::set<Key>::RBTree::RBTreeNode* node) {
  s21::set<Key>::RBTree::RBTreeNode* parent;
  root_->parent_ = nullptr;
  parent = node->parent_;
  while (node != root_ && parent->color_ == Red) {
    s21::set<Key>::RBTree::RBTreeNode* gparent = parent->parent_;
    if (gparent->left_ == parent) {
      s21::set<Key>::RBTree::RBTreeNode* uncle = gparent->right_;
      if (uncle != nullptr && uncle->color_ == Red) {
        parent->color_ = Black;
        uncle->color_ = Black;
        gparent->color_ = Red;
        node = gparent;
        parent = node->parent_;
      } else {
        if (parent->right_ == node) {
          leftRotate(root, parent);
          std::swap(node, parent);
        }
        rightRotate(root, gparent);
        gparent->color_ = Red;
        parent->color_ = Black;
        break;
      }
    } else {
      s21::set<Key>::RBTree::RBTreeNode* uncle = gparent->left_;
      if (uncle != nullptr && uncle->color_ == Red) {
        gparent->color_ = Red;
        parent->color_ = Black;
        uncle->color_ = Black;

        node = gparent;
        parent = node->parent_;
      } else {
        if (parent->left_ == node) {
          rightRotate(root, parent);
          std::swap(parent, node);
        }
        leftRotate(root, gparent);
        parent->color_ = Black;
        gparent->color_ = Red;
        break;
      }
    }
  }
  root->color_ = Black;
  root_->parent_ = header_;
}

template <class Key>
void s21::set<Key>::RBTree::Destroy() {
  Destroy(root_);
}

template <class Key>
void s21::set<Key>::RBTree::Destroy(s21::set<Key>::RBTree::RBTreeNode*& node) {
  if (node == nullptr) return;
  Destroy(node->left_);
  Destroy(node->right_);
  delete node;
  node = nullptr;
}

template <class Key>
void s21::set<Key>::RBTree::Remove(Key key) {
  s21::set<Key>::RBTree::RBTreeNode* deletenode = Search(root_, key);
  if (deletenode != nullptr) Remove(root_, deletenode);
}
template <class Key>
void s21::set<Key>::RBTree::Remove(s21::set<Key>::RBTree::RBTreeNode*& root,
                                   s21::set<Key>::RBTree::RBTreeNode* node) {
  s21::set<Key>::RBTree::RBTreeNode *child, *parent;
  RBTreeColor color;
  root_->parent_ = nullptr;
  if (node->left_ != nullptr && node->right_ != nullptr) {
    s21::set<Key>::RBTree::RBTreeNode* replace = node;
    replace = node->right_;
    while (replace->left_ != nullptr) {
      replace = replace->left_;
    }

    if (node->parent_ != nullptr) {
      if (node->parent_->left_ == node)
        node->parent_->left_ = replace;
      else
        node->parent_->right_ = replace;
    }

    else
      root = replace;
    child = replace->right_;
    parent = replace->parent_;
    color = replace->color_;

    if (parent == node)
      parent = replace;
    else {
      if (child != nullptr) child->parent_ = parent;
      parent->left_ = child;

      replace->right_ = node->right_;
      node->right_->parent_ = replace;
    }
    replace->parent_ = node->parent_;
    replace->color_ = node->color_;
    replace->left_ = node->left_;
    node->left_->parent_ = replace;
    if (color == Black) RemoveFixUp(root, child, parent);

    delete node;
    root_->parent_ = header_;
    return;
  }

  if (node->left_ != nullptr)
    child = node->left_;
  else
    child = node->right_;

  parent = node->parent_;
  color = node->color_;
  if (child) {
    child->parent_ = parent;
  }

  if (parent) {
    if (node == parent->left_)
      parent->left_ = child;
    else
      parent->right_ = child;
  }

  else
    root_ = child;

  if (color == Black) {
    RemoveFixUp(root, child, parent);
  }
  delete node;
  root_->parent_ = header_;
}
template <class Key>
void s21::set<Key>::RBTree::RemoveFixUp(
    s21::set<Key>::RBTree::RBTreeNode*& root,
    s21::set<Key>::RBTree::RBTreeNode* node,
    s21::set<Key>::RBTree::RBTreeNode* parent) {
  s21::set<Key>::RBTree::RBTreeNode* othernode;
  while (((!node) || node->color_ == Black) && node != root_) {
    if (parent->left_ == node) {
      othernode = parent->right_;
      if (othernode->color_ == Red) {
        othernode->color_ = Black;
        parent->color_ = Red;
        leftRotate(root, parent);
        othernode = parent->right_;
      } else {
        if (!(othernode->right_) || othernode->right_->color_ == Black) {
          othernode->left_->color_ = Black;
          othernode->color_ = Red;
          rightRotate(root, othernode);
          othernode = parent->right_;
        }
        othernode->color_ = parent->color_;
        parent->color_ = Black;
        othernode->right_->color_ = Black;
        leftRotate(root, parent);
        node = root;
        break;
      }
    } else {
      othernode = parent->left_;
      if (othernode->color_ == Red) {
        othernode->color_ = Black;
        parent->color_ = Red;
        rightRotate(root, parent);
        othernode = parent->left_;
      }
      if ((!othernode->left_ || othernode->left_->color_ == Black) &&
          (!othernode->right_ || othernode->right_->color_ == Black)) {
        othernode->color_ = Red;
        node = parent;
        parent = node->parent_;
      } else {
        if (!(othernode->left_) || othernode->left_->color_ == Black) {
          othernode->right_->color_ = Black;
          othernode->color_ = Red;
          leftRotate(root, othernode);
          othernode = parent->left_;
        }
        othernode->color_ = parent->color_;
        parent->color_ = Black;
        othernode->left_->color_ = Black;
        rightRotate(root, parent);
        node = root;
        break;
      }
    }
  }
  if (node) node->color_ = Black;
}

template <class Key>
typename s21::set<Key>::RBTree::RBTreeNode* s21::set<Key>::RBTree::Search(
    Key key) {
  return Search(root_, key);
}
template <class Key>
typename s21::set<Key>::RBTree::RBTreeNode* s21::set<Key>::RBTree::Search(
    s21::set<Key>::RBTree::RBTreeNode* node, Key key) const {
  if (node == nullptr || node->key_ == key)
    return node;
  else if (key > node->key_)
    return Search(node->right_, key);
  else
    return Search(node->left_, key);
}

template <class Key>
typename s21::set<Key>::RBTree::RBTreeNode* s21::set<Key>::RBTree::Min() {
  return MinimalNode(root_);
}

template <class Key>
typename s21::set<Key>::RBTree::RBTreeNode* s21::set<Key>::RBTree::MinimalNode(
    s21::set<Key>::RBTree::RBTreeNode* subTreeRoot) {
  s21::set<Key>::RBTree::RBTreeNode* x = subTreeRoot;
  while (x != nullptr && x->left_ != nullptr) {
    x = x->left_;
  }
  return x;
}

template <class Key>
typename s21::set<Key>::RBTree::RBTreeNode* s21::set<Key>::RBTree::Max() {
  return MaximalNode(root_);
}

template <class Key>
typename s21::set<Key>::RBTree::RBTreeNode* s21::set<Key>::RBTree::MaximalNode(
    s21::set<Key>::RBTree::RBTreeNode* subTreeRoot) {
  s21::set<Key>::RBTree::RBTreeNode* x = subTreeRoot;
  while (x != nullptr && x->right_ != nullptr) {
    x = x->right_;
  }
  return x;
}

// RBTREE ITERATOR

template <class Key>
typename s21::set<Key>::RBTree::iterator&
s21::set<Key>::RBTree::iterator::operator=(const iterator& it) {
  node_ = it.node_;
  return *this;
}

template <class Key>
bool s21::set<Key>::RBTree::iterator::operator==(const iterator& it) {
  return (node_ == it.node_);
}

template <class Key>
bool s21::set<Key>::RBTree::iterator::operator!=(const iterator& it) {
  return !(*this == it);
}

template <class Key>
typename s21::set<Key>::RBTree::iterator&
s21::set<Key>::RBTree::iterator::operator++() {
  if (node_->right_ != nullptr) {  // у node есть правый сын
    RBTreeNode* x = node_->right_;
    while (x && x->left_) x = x->left_;
    node_ = x;
  } else if (node_->parent_ &&
             node_ == node_->parent_->left_) {  // node -- левый сын
    node_ = node_->parent_;
  } else {
    RBTreeNode* x = node_->parent_;
    while (x->parent_ && x == x->parent_->right_) {  // пока x -- правый сын
      x = x->parent_;  //     идем вверх по дереву
    }
    // утв: x -- левый сын своего отца
    node_ = x->parent_;
  }
  return *this;
}

template <class Key>
typename s21::set<Key>::RBTree::iterator&
s21::set<Key>::RBTree::iterator::operator--() {
  if (node_->left_ != nullptr) {
    RBTreeNode* x = node_->left_;
    while (x && x->right_) x = x->right_;
    node_ = x;
  } else if (node_->parent_ && node_ == node_->parent_->right_) {
    node_ = node_->parent_;
  } else {
    RBTreeNode* x = node_->parent_;
    while (x->parent_ && x == x->parent_->left_) {
      x = x->parent_;
    }
    node_ = x->parent_;
  }
  return *this;
}

#endif
