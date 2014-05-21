#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include "Utils.h"
#include <iostream>
template <typename Key, typename Value>
struct Node {
  Key key_;
  Value value_;
  
  Node* left_;
  Node* right_;

  Node(Key key, Value value)
    : key_(key), value_(value),
      left_(NULL), right_(NULL) {}
  Node()
    : left_(NULL), right_(NULL) {}

  ~Node() {
    if (left_)
      delete left_;
    if (right_)
      delete right_;
  }
};  // struct node

template <typename Key, typename Value>
class BinarySearchTree {
 public:
  typedef Node<Key, Value> node;
 private:
  node* root_;
 public:
  BinarySearchTree()
    : root_(NULL) {
  }

  bool Insert(Key key, Value value);
  bool Delete(const Key& key);

  node* Search(const Key& key);
  bool IsEmpty() const {
    return root_ == NULL;
  }

  void InorderTravel();

 private:
  bool Insert(node* new_node);
  bool Delete(node* del_node);
  void InorderTravel(node* travel_node);

  node* GetMinNodeFromSubtree(node* sub_tree);
  node* GetParent(node* child);
};  // class BinarySearchTree

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Insert(Key key, Value value) {
  Node<Key, Value>* new_node = new Node<Key, Value>(key, value);
  return Insert(new_node);
}


template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Insert(Node<Key, Value>* new_node) {
  Node<Key, Value>* cur = root_;
  Node<Key, Value>* parent = NULL;
  Key k = new_node->key_;

  while (cur != NULL) {
    parent = cur;
    if (k < cur->key_)
      cur = cur->left_;
    else if (k > cur->key_)
      cur = cur->right_;
    else {
      LOG_OUT("Insert error:" 
          "the key has already in thsi binary tree. loc:%s:%d",
          __FILE__, __LINE__);
      return false;
    }
  }

  if (parent == NULL)
    root_ = new_node;
  else if (k < parent->key_)
    parent->left_ = new_node;
  else
    parent->right_ = new_node;
  return true;
}


template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Delete(const Key& key) {
  Node<Key, Value>* del_node = Search(key);
  if (del_node == NULL)
    return false;
  return Delete(del_node);
}


template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Delete(Node<Key, Value>* del_node) {
  Node<Key, Value>* parent = GetParent(del_node);
  Node<Key, Value>* cur = del_node;
  if (del_node->left_ == NULL)
    del_node = del_node->right_;
  else if (del_node->right_ == NULL)
    del_node = del_node->left_;
  else {
    Node<Key, Value>* successor = GetMinNodeFromSubtree(del_node->right_);
    del_node->key_ = successor->key_;
    del_node->value_ = successor->value_;
    if (GetParent(successor) != del_node)
      GetParent(successor)->left_ = successor->right_;
    else
      del_node->left_ = successor->right_;
    delete successor;
    return true;
  }

  if (parent == NULL)
    root_ = del_node;
  else {
    if (parent->left_ == cur)
      parent->left_ = del_node;
    else
      parent->right_ = del_node;
  }

  cur = NULL;

  return true;
}


template <typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::Search(const Key& key) {
  if (IsEmpty())
    return NULL;
  Node<Key, Value>* cur = root_;
  while (cur != NULL && cur->key_ != key) {
    if (key < cur->key_)
      cur = cur->left_;
    else
      cur = cur->right_;
  }
  
  return cur;
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::InorderTravel(Node<Key, Value>* t_node) {
  Node<Key, Value>* cur = t_node;
  if (cur != NULL) {
    InorderTravel(cur->left_);
    std::cout << cur->key_ << "-->" << cur->value_ << std::endl;
    InorderTravel(cur->right_);
  }
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::InorderTravel() {
  InorderTravel(root_);
}

template <typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::GetMinNodeFromSubtree(Node<Key, Value>* subtree) {
  Node<Key, Value>* cur = subtree;
  Node<Key, Value>* ret = NULL;
  while (cur != NULL) {
    ret = cur;
    cur = cur->left_;
  }

  return ret;
}


template <typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::GetParent(Node<Key, Value>* child_node) {
  Node<Key, Value>* parent = NULL;
  Node<Key, Value>* cur = root_;
  while (cur != NULL) {
    if (cur == child_node)
      return parent;
    parent = cur;
    if (child_node->key_ < cur->key_)
      cur = cur->left_;
    else
      cur = cur->right_;
  }

  return NULL;
}

#endif  // BINARY_SEARCH_TREE_H_
