#ifndef S21_BINARY_TREE_H
#define S21_BINARY_TREE_H

#include <string>

namespace s21 {

template <typename Key, typename T>
class S21RBTree;

template <typename Key, typename T>
class S21RBTreeNode {
 public:
  S21RBTreeNode();
  S21RBTreeNode(Key key, T value);
  S21RBTreeNode(const S21RBTreeNode<Key, T>& other);
  ~S21RBTreeNode();

 public:
  T& GetValue() noexcept;
  void SetValue(T value) noexcept;

 private:
  friend class S21RBTree<Key, T>;

 private:
  S21RBTreeNode<Key, T>* Grandparent() noexcept;
  S21RBTreeNode<Key, T>* Sibling() noexcept;
  S21RBTreeNode<Key, T>* Uncle() noexcept;

 private:
  S21RBTreeNode* parent_;
  S21RBTreeNode* left_;
  S21RBTreeNode* right_;
  bool isRed_;
  Key key_;
  T value_;
};

template <typename Key, typename T>
class S21RBTree {
 public:
  class Iterator;
  using value_type = std::pair<Key, T>;
  using key_type = Key;
  using mapped_type = T;
  using iterator = typename S21RBTree<Key, T>::Iterator;

 public:
  S21RBTree();
  S21RBTree(Key key, T value);
  ~S21RBTree();
  S21RBTreeNode<Key, T>* Insert(Key key, T value);

  void PrintTree();

  S21RBTreeNode<Key, T>* Find(Key key) noexcept;
  S21RBTreeNode<Key, T>* Find(S21RBTreeNode<Key, T>* node, Key key) noexcept;

  void Delete(Key key);
  void Delete(Iterator pos);
  void RemoveTreeInPostOrder(S21RBTreeNode<Key, T>* node);
  void RemoveTreeInPostOrder();

  Iterator Begin();
  Iterator End();

  bool Empty() noexcept;

 private:
  void RotateLeft(S21RBTreeNode<Key, T>* node) noexcept;
  void RotateRight(S21RBTreeNode<Key, T>* node) noexcept;
  void PrintTree(const std::string& prefix, const S21RBTreeNode<Key, T>* node,
                 bool isLeft);
  S21RBTreeNode<Key, T>* Insert(S21RBTreeNode<Key, T>* node, Key key, T value);
  // Balance functions for insertion
  void InsertType1(S21RBTreeNode<Key, T>* node) noexcept;
  void InsertType2(S21RBTreeNode<Key, T>* node) noexcept;
  void InsertType3(S21RBTreeNode<Key, T>* node) noexcept;
  void InsertType4(S21RBTreeNode<Key, T>* node) noexcept;
  void InsertType5(S21RBTreeNode<Key, T>* node) noexcept;

  void Delete(S21RBTreeNode<Key, T>* node);
  // Balance functions for deletion
  void DeleteType0(S21RBTreeNode<Key, T>* node);
  void DeleteType1(S21RBTreeNode<Key, T>* node) noexcept;
  void DeleteType2(S21RBTreeNode<Key, T>* node) noexcept;
  void DeleteType3(S21RBTreeNode<Key, T>* node) noexcept;
  void DeleteType4(S21RBTreeNode<Key, T>* node) noexcept;
  void DeleteType5(S21RBTreeNode<Key, T>* node) noexcept;
  void DeleteType6(S21RBTreeNode<Key, T>* node) noexcept;

  void ReplaceNode(S21RBTreeNode<Key, T>* node,
                   S21RBTreeNode<Key, T>* child) noexcept;

  S21RBTreeNode<Key, T>* FindSubstitution(
      S21RBTreeNode<Key, T>* startNode) noexcept;
  S21RBTreeNode<Key, T>* FindMin(S21RBTreeNode<Key, T>* startNode) noexcept;
  S21RBTreeNode<Key, T>* FindMax() noexcept;
  S21RBTreeNode<Key, T>* FindMax(S21RBTreeNode<Key, T>* startNode) noexcept;

 private:
  S21RBTreeNode<Key, T>* root_;
};

template <typename Key, typename T>
class S21RBTree<Key, T>::Iterator {
 public:
  Iterator() : node_(nullptr), parentClass_(nullptr) {}
  Iterator(S21RBTree<Key, T>* parent, S21RBTreeNode<Key, T>* node)
      : node_(node), parentClass_(parent) {}
  Iterator(S21RBTreeNode<Key, T>* node) : node_(node), parentClass_() {}

 public:
  bool operator==(const Iterator& other);
  bool operator!=(const Iterator& other);

  Iterator& operator++();
  Iterator& operator++(int);
  Iterator& operator--();
  Iterator& operator--(int);
  value_type operator*();

  S21RBTreeNode<Key, T>* GetPtr();

 private:
  S21RBTreeNode<Key, T>* node_;
  S21RBTree* parentClass_;
};

template <typename Key, typename T>
typename S21RBTree<Key, T>::Iterator& S21RBTree<Key, T>::Iterator::operator++(
    int) {
  ++(*this);
  return *this;
}

template <typename Key, typename T>
typename S21RBTree<Key, T>::Iterator& S21RBTree<Key, T>::Iterator::operator--(
    int) {
  --(*this);
  return *this;
}

template <typename Key, typename T>
typename S21RBTree<Key, T>::Iterator S21RBTree<Key, T>::Begin() {
  Iterator it(this, FindMin(root_));
  return it;
}

template <typename Key, typename T>
typename S21RBTree<Key, T>::Iterator S21RBTree<Key, T>::End() {
  Iterator it(this, nullptr);
  return it;
}

template <typename Key, typename T>
bool S21RBTree<Key, T>::Iterator::operator==(const Iterator& other) {
  if ((node_ == nullptr) ^ (other.node_ == nullptr)) return false;

  if ((node_ == nullptr) && (other.node_ == nullptr)) return true;

  if (node_->key_ != other.node_->key_) return false;

  if (node_->value_ != other.node_->value_) return false;

  return true;
}

template <typename Key, typename T>
typename S21RBTree<Key, T>::Iterator&
S21RBTree<Key, T>::Iterator::operator--() {
  if (node_ == nullptr) {
    node_ = parentClass_->FindMax(parentClass_->root_);
  } else if (node_->left_ != nullptr) {
    S21RBTreeNode<Key, T>* prevNode = node_->left_;
    while (prevNode != nullptr && prevNode->right_ != nullptr)
      prevNode = prevNode->right_;
    node_ = prevNode;
  } else if (node_->parent_ != nullptr && node_ == node_->parent_->right_) {
    node_ = node_->parent_;
  } else if (node_->parent_ != nullptr && node_ == node_->parent_->left_) {
    S21RBTreeNode<Key, T>* prevNode = node_->parent_;
    while (prevNode->parent_ != nullptr &&
           prevNode == prevNode->parent_->left_) {
      prevNode = prevNode->parent_;
    }
    node_ = prevNode->parent_;
  } else if (node_->parent_ == nullptr) {
    node_ = nullptr;
  }
  return *this;
}

template <typename Key, typename T>
typename S21RBTree<Key, T>::Iterator&
S21RBTree<Key, T>::Iterator::operator++() {
  if (node_->right_ != nullptr) {
    S21RBTreeNode<Key, T>* nextNode = node_->right_;
    while (nextNode->left_ != nullptr) nextNode = nextNode->left_;
    node_ = nextNode;
  } else if (node_->parent_ != nullptr && node_ == node_->parent_->left_) {
    node_ = node_->parent_;
  } else if (node_->parent_ != nullptr && node_ == node_->parent_->right_) {
    S21RBTreeNode<Key, T>* nextNode = node_->parent_;
    while (nextNode->parent_ != nullptr &&
           nextNode == nextNode->parent_->right_)
      nextNode = nextNode->parent_;

    node_ = nextNode->parent_;
  } else if (node_->parent_ == nullptr) {
    node_ = nullptr;
  }

  return *this;
}

template <typename Key, typename T>
bool S21RBTree<Key, T>::Iterator::operator!=(const Iterator& other) {
  return ((*this) == other) ? false : true;
}

template <typename Key, typename T>
typename S21RBTree<Key, T>::value_type
S21RBTree<Key, T>::Iterator::operator*() {
  return std::pair<Key, T>(node_->key_, node_->value_);
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::Iterator::GetPtr() {
  return node_;
}

/**
 * Methods definition of the Tree Node class.
 */

template <typename Key, typename T>
S21RBTreeNode<Key, T>::S21RBTreeNode()
    : parent_(nullptr), left_(nullptr), right_(nullptr), isRed_(true) {}

template <typename Key, typename T>
S21RBTreeNode<Key, T>::S21RBTreeNode(Key key, T value)
    : parent_(nullptr),
      left_(nullptr),
      right_(nullptr),
      isRed_(true),
      key_(key),
      value_(value) {}

template <typename Key, typename T>
S21RBTreeNode<Key, T>::S21RBTreeNode(const S21RBTreeNode<Key, T>& other)
    : left_(other.left_),
      right_(other.right_),
      parent_(other.isRed_),
      value_(other.value_),
      key_(other.key_) {}

template <typename Key, typename T>
S21RBTreeNode<Key, T>::~S21RBTreeNode() {}

template <typename Key, typename T>
T& S21RBTreeNode<Key, T>::GetValue() noexcept {
  return value_;
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTreeNode<Key, T>::Grandparent() noexcept {
  if (parent_ != nullptr) {
    return parent_->parent_;
  } else {
    return nullptr;
  }
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTreeNode<Key, T>::Uncle() noexcept {
  S21RBTreeNode* gp = Grandparent();

  if (gp == nullptr) {
    return nullptr;
  }

  if (parent_ == gp->left_) {
    return gp->right_ == nullptr ? nullptr : gp->right_;
  } else {
    return gp->left_ == nullptr ? nullptr : gp->left_;
  }
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTreeNode<Key, T>::Sibling() noexcept {
  S21RBTreeNode<Key, T>* sibling = nullptr;

  if (parent_ != nullptr && this == parent_->left_) {
    sibling = parent_->right_;
  } else if (parent_ != nullptr) {
    sibling = parent_->left_;
  }

  return sibling;
}

template <typename Key, typename T>
void S21RBTreeNode<Key, T>::SetValue(T value) noexcept {
  value_ = value;
}

/**
 * Definition of the tree methods=
 */

template <typename Key, typename T>
S21RBTree<Key, T>::S21RBTree() : root_(nullptr) {}

template <typename Key, typename T>
S21RBTree<Key, T>::S21RBTree(Key key, T value) {
  root_ = new S21RBTreeNode<Key, T>(key, value);
}

template <typename Key, typename T>
S21RBTree<Key, T>::~S21RBTree() {
  RemoveTreeInPostOrder(root_);
}

template <typename Key, typename T>
bool S21RBTree<Key, T>::Empty() noexcept {
  return root_ == nullptr ? true : false;
}
template <typename Key, typename T>
void S21RBTree<Key, T>::Delete(Key key) {
  S21RBTreeNode<Key, T>* node = Find(key);
  if (node != nullptr) Delete(node);
}

template <typename Key, typename T>
void S21RBTree<Key, T>::Delete(Iterator pos) {
  Delete(pos.GetPtr());
}

template <typename Key, typename T>
void S21RBTree<Key, T>::ReplaceNode(S21RBTreeNode<Key, T>* node,
                                    S21RBTreeNode<Key, T>* child) noexcept {
  if (child != nullptr) {
    child->parent_ = node->parent_;
    if (node->parent_ == nullptr) root_ = child;
  }
  if (node->parent_ != nullptr) {
    if (node->parent_->left_ == node) {
      node->parent_->left_ = child;
    } else {
      node->parent_->right_ = child;
    }
  }
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::FindMin(
    S21RBTreeNode<Key, T>* startNode) noexcept {
  S21RBTreeNode<Key, T>* minNode = nullptr;
  if (startNode != nullptr) {
    if (startNode->left_ == nullptr) {
      minNode = startNode;
    } else {
      minNode = FindMin(startNode->left_);
    }
  }

  return minNode;
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::FindMax(
    S21RBTreeNode<Key, T>* startNode) noexcept {
  S21RBTreeNode<Key, T>* maxNode = nullptr;
  if (startNode != nullptr) {
    if (startNode->right_ == nullptr) {
      maxNode = startNode;
    } else {
      maxNode = FindMax(startNode->right_);
    }
  }
  return maxNode;
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::FindMax() noexcept {
  return FindMax(root_);
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::FindSubstitution(
    S21RBTreeNode<Key, T>* startNode) noexcept {
  S21RBTreeNode<Key, T>* maxLeftSideNode = nullptr;

  if (startNode != nullptr) {
    maxLeftSideNode = FindMax(startNode->left_);
  }

  return maxLeftSideNode;
}

// TODO: Реализовать Удаление элементов
template <typename Key, typename T>
void S21RBTree<Key, T>::Delete(S21RBTreeNode<Key, T>* node) {
  // delete node;
  if (node->left_ != nullptr && node->right_ != nullptr) {
    S21RBTreeNode<Key, T>* leftSideMax = FindSubstitution(node);
    node->value_ = leftSideMax->value_;
    DeleteType0(leftSideMax);
  } else {
    DeleteType0(node);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::DeleteType0(S21RBTreeNode<Key, T>* node) {
  S21RBTreeNode<Key, T>* child =
      node->right_ == nullptr ? node->left_ : node->right_;

  if (node->left_ == nullptr && node->right_ == nullptr &&
      node->parent_ == nullptr) {
    root_ = nullptr;
  } else if (child == nullptr && node->isRed_ == true) {
    if (node->parent_->left_ == node) {
      node->parent_->left_ = nullptr;
    } else {
      node->parent_->right_ = nullptr;
    }
  } else if (child == nullptr) {
    DeleteType1(node);
    if (node->parent_->left_ == node) {
      node->parent_->left_ = nullptr;
    } else {
      node->parent_->right_ = nullptr;
    }
  } else {
    ReplaceNode(node, child);
    if (node->isRed_ == false) {
      if (child != nullptr && child->isRed_ == true) {
        child->isRed_ = false;
      } else {
        DeleteType1(child);
      }
    }
  }
  delete node;
}

template <typename Key, typename T>
void S21RBTree<Key, T>::DeleteType1(S21RBTreeNode<Key, T>* node) noexcept {
  if (node->parent_ != nullptr) {
    DeleteType2(node);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::DeleteType2(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* sibling = node->Sibling();

  if (sibling != nullptr && sibling->isRed_ == true) {
    node->parent_->isRed_ = true;
    sibling->isRed_ = false;

    if (node == node->parent_->left_) {
      RotateLeft(node->parent_);
    } else {
      RotateRight(node->parent_);
    }
  }

  DeleteType3(node);
}

template <typename Key, typename T>
void S21RBTree<Key, T>::DeleteType3(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* sibling = node->Sibling();

  // Родитель, брат, и дети брата - черные;
  bool condition =
      node->parent_->isRed_ == false && sibling->isRed_ == false &&
      (sibling->left_ == nullptr || sibling->left_->isRed_ == false) &&
      (sibling->right_ == nullptr || sibling->right_->isRed_ == false);

  if (condition == true) {
    sibling->isRed_ = true;
    DeleteType1(node->parent_);
  } else {
    DeleteType4(node);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::DeleteType4(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* sibling = node->Sibling();

  // Брат, и дети брата - черные, но родитель - красный;
  bool condition =
      node->parent_->isRed_ == true && sibling->isRed_ == false &&
      (sibling->left_ == nullptr || sibling->left_->isRed_ == false) &&
      (sibling->right_ == nullptr || sibling->right_->isRed_ == false);

  if (condition) {
    sibling->isRed_ = true;
    node->parent_->isRed_ = false;
  } else {
    DeleteType5(node);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::DeleteType5(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* sibling = node->Sibling();
  if (sibling->isRed_ == false) {
    // Нода является левым потомком, правый брат - черный, а левый - красный;
    bool conditionLeft =
        (node == node->parent_->left_) &&
        (sibling->right_ == nullptr || sibling->right_->isRed_ == false) &&
        (sibling->left_ != nullptr && sibling->left_->isRed_ == true);
    bool conditionRight =
        (node == node->parent_->right_) &&
        (sibling->left_ == nullptr || sibling->left_->isRed_ == false) &&
        (sibling->right_ != nullptr || sibling->right_->isRed_ == true);

    if (conditionLeft == true) {
      sibling->isRed_ = true;
      sibling->left_->isRed_ = false;
      RotateRight(sibling);
    } else if (conditionRight == true) {
      sibling->isRed_ = true;
      sibling->right_->isRed_ = false;
      RotateLeft(sibling);
    }
  }
  DeleteType6(node);
}

template <typename Key, typename T>
void S21RBTree<Key, T>::DeleteType6(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* sibling = node->Sibling();

  sibling->isRed_ = node->parent_->isRed_;
  node->parent_->isRed_ = false;

  if (node == node->parent_->left_) {
    sibling->right_->isRed_ = false;
    RotateLeft(node->parent_);
  } else {
    sibling->left_->isRed_ = false;
    RotateRight(node->parent_);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::InsertType5(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* gp = node->Grandparent();

  node->parent_->isRed_ = false;
  if (gp != nullptr) {
    gp->isRed_ = true;
    if (node == node->parent_->left_ && node->parent_ == gp->left_) {
      RotateRight(gp);
    } else {
      RotateLeft(gp);
    }
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::InsertType4(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* gp = node->Grandparent();

  if ((node == node->parent_->right_) && (gp != nullptr) &&
      (node->parent_ == gp->left_)) {
    RotateLeft(node->parent_);
    node = node->left_;
  } else if ((node == node->parent_->left_) && (gp != nullptr) &&
             (node->parent_ == gp->right_)) {
    RotateRight(node->parent_);
    node = node->right_;
  }

  InsertType5(node);
}

template <typename Key, typename T>
void S21RBTree<Key, T>::InsertType3(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* uncle = node->Uncle();

  if ((uncle != nullptr) && (uncle->isRed_ == true)) {
    node->parent_->isRed_ = false;
    uncle->isRed_ = false;
    S21RBTreeNode<Key, T>* gp = node->Grandparent();
    gp->isRed_ = true;
    InsertType1(gp);
  } else {
    InsertType4(node);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::InsertType2(S21RBTreeNode<Key, T>* node) noexcept {
  if (node->parent_->isRed_ == false) {
    return;
  } else {
    InsertType3(node);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::InsertType1(S21RBTreeNode<Key, T>* node) noexcept {
  if (node && node->parent_ == nullptr) {
    node->isRed_ = false;
  } else {
    InsertType2(node);
  }
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::Insert(Key key, T value) {
  S21RBTreeNode<Key, T>* node = nullptr;
  if (root_ == nullptr) {
    root_ = new S21RBTreeNode<Key, T>(key, value);
    node = root_;
  } else {
    node = Insert(root_, key, value);
    InsertType1(node);
  }

  return node;
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::Insert(S21RBTreeNode<Key, T>* node,
                                                 Key key, T value) {
  S21RBTreeNode<Key, T>* newNode = nullptr;
  if (key < node->key_) {
    if (node->left_ == nullptr) {
      newNode = new S21RBTreeNode<Key, T>(key, value);
      newNode->parent_ = node;
      node->left_ = newNode;
    } else {
      newNode = Insert(node->left_, key, value);
    }

  } else {
    if (node->right_ == nullptr) {
      newNode = new S21RBTreeNode<Key, T>(key, value);
      newNode->parent_ = node;
      node->right_ = newNode;
    } else {
      newNode = Insert(node->right_, key, value);
    }
  }
  return newNode;
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::Find(Key key) noexcept {
  if (root_ != nullptr && key == root_->key_) {
    return root_;
  } else {
    S21RBTreeNode<Key, T>* node = Find(root_, key);
    return node;
  }
}

template <typename Key, typename T>
S21RBTreeNode<Key, T>* S21RBTree<Key, T>::Find(S21RBTreeNode<Key, T>* node,
                                               Key key) noexcept {
  S21RBTreeNode<Key, T>* rNode = nullptr;
  if (node != nullptr) {
    if (key == node->key_) {
      rNode = node;
    } else if (key < node->key_) {
      rNode = Find(node->left_, key);
    } else {
      rNode = Find(node->right_, key);
    }
  }

  return rNode;
}

template <typename Key, typename T>
void S21RBTree<Key, T>::RemoveTreeInPostOrder(S21RBTreeNode<Key, T>* node) {
  if (node == nullptr) return;

  RemoveTreeInPostOrder(node->left_);

  RemoveTreeInPostOrder(node->right_);

  delete node;
}

template <typename Key, typename T>
void S21RBTree<Key, T>::RemoveTreeInPostOrder() {
  RemoveTreeInPostOrder(root_);
  root_ = nullptr;
}

template <typename Key, typename T>
void S21RBTree<Key, T>::PrintTree() {
  if (root_ != nullptr) {
    PrintTree("", root_, false);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::PrintTree(const std::string& prefix,
                                  const S21RBTreeNode<Key, T>* node,
                                  bool isLeft) {
  if (node != nullptr) {
    std::cout << prefix;

    std::cout << (isLeft ? "├──" : "└──");

    std::cout << (node->isRed_ ? "\033[1;31m" : "") << node->value_
              << (isLeft ? "l" : "r") << (node->isRed_ ? "\033[0m" : "")
              << std::endl;

    PrintTree(prefix + (isLeft ? "│   " : "    "), node->left_, true);
    PrintTree(prefix + (isLeft ? "│   " : "    "), node->right_, false);
  }
}

template <typename Key, typename T>
void S21RBTree<Key, T>::RotateLeft(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* rNode = node->right_;

  rNode->parent_ = node->parent_;
  if (rNode->parent_ == nullptr) root_ = rNode;

  if (node->parent_ != nullptr) {
    if (node->parent_->left_ == node) {
      node->parent_->left_ = rNode;
    } else {
      node->parent_->right_ = rNode;
    }
  }

  node->right_ = rNode->left_;

  if (rNode->left_ != nullptr) {
    rNode->left_->parent_ = node;
  }

  node->parent_ = rNode;
  rNode->left_ = node;
}

template <typename Key, typename T>
void S21RBTree<Key, T>::RotateRight(S21RBTreeNode<Key, T>* node) noexcept {
  S21RBTreeNode<Key, T>* rNode = node->left_;

  rNode->parent_ = node->parent_;
  if (rNode->parent_ == nullptr) root_ = rNode;

  if (node->parent_ != nullptr) {
    if (node->parent_->left_ == node) {
      node->parent_->left_ = rNode;
    } else {
      node->parent_->right_ = rNode;
    }
  }

  node->left_ = rNode->right_;

  if (rNode->right_ != nullptr) {
    rNode->right_->parent_ = node;
  }

  node->parent_ = rNode;
  rNode->right_ = node;
}

}  // namespace s21

#endif  // S21_BINARY_TREE_H