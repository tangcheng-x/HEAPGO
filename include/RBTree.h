#ifndef RBTREE_H_
#define RBTREE_H_

#include "Utils.h"

#include <iostream>

enum COLOR {
  RED, BLACK
};

template <typename Key, typename Value>
struct Node {
  Node* left_;
  Node* right_;
  Node* parent_;
  COLOR color_;
  Key key_;
  Value value_;

  Node()
  : left_(NULL), right_(NULL), parent_(NULL) {}
};  // struct Node


#define CHECK_NODE_NOT_NIL(node) \
  CHECK(node != nil_node_)

template <typename Key, typename Value>
class RBTree {
 private:
  Node<Key, Value>* root_;
  Node<Key, Value>* nil_node_;
 public:
  RBTree();

  // Left Rotation
  void LeftRotate(Node<Key, Value>* node);
  // Right Rotation
  void RightRotate(Node<Key, Value>* node);

  // Insert Node
  bool Insert(Key key, Value value);

  // Delete Node
  bool Delete(const Key& key);

  // Search Node by key
  Node<Key, Value>* Search(const Key& key);

  // Display The RBTree by InOrder
  void InOrderPrint(Node<Key, Value>* node);

  void InOrderPrint() { InOrderPrint(root_); }
 private:

  void InsertFixUp(Node<Key, Value>* insert_node);
  void DeleteFixUp(Node<Key, Value>* delete_node);

  Node<Key, Value>* GetSuccessor(Node<Key, Value>* node);

  DISALLOW_COPY_AND_ASSIGN(RBTree);
};  // class RBTree

template <typename Key, typename Value>
RBTree<Key, Value>::RBTree() {
  nil_node_ = new Node<Key, Value>();
  root_ = nil_node_;
  nil_node_->parent_ = root_;
  nil_node_->left_ = root_;
  nil_node_->right_ = root_;
  nil_node_->color_ = BLACK;
}


template <typename Key, typename Value>
void RBTree<Key, Value>::LeftRotate(Node<Key, Value>* node) {
  CHECK_NODE_NOT_NIL(node);
  CHECK_NODE_NOT_NIL(node->right_);
  Node<Key, Value>* right_child = node->right_;
  right_child->parent_ = node->parent_;
  if (right_child->left_ != nil_node_) {
    right_child->left_->parent_ = node;
  }
  node->right_ = right_child->left_;
  if (node->parent_ == nil_node_) {
    root_ = right_child;
    nil_node_->left_ = root_;
    nil_node_->right_ = root_;
  }
  else if (node == node->parent_->left_)
    node->parent_->left_ = right_child;
  else
    node->parent_->right_ = right_child;

  right_child->left_ = node;
  node->parent_ = right_child;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::RightRotate(Node<Key, Value>* node) {
  CHECK_NODE_NOT_NIL(node);
  CHECK_NODE_NOT_NIL(node->left_);
  Node<Key, Value>* left_child = node->left_;
  left_child->parent_ = node->parent_;
  if (left_child->right_ != nil_node_) {
    left_child->right_->parent_ = node;
  }
  node->left_ = left_child->right_;
  if (node->parent_ == nil_node_) {
    root_ = left_child;
    nil_node_->left_ = root_;
    nil_node_->right_ = root_;
  }
  else {
    if (node == node->parent_->left_)
      node->parent_->left_ = left_child;
    else
      node->parent_->right_ = left_child;
  }
  left_child->right_ = node;
  node->parent_ = left_child;
}

template <typename Key, typename Value>
bool RBTree<Key, Value>::Insert(Key key, Value value) {
  Node<Key, Value>* p_node = nil_node_;
  Node<Key, Value>* cur = root_;

  while (cur != nil_node_) {
    p_node = cur;
    if (key < cur->key_)
      cur = cur->left_;
    else if (key > cur->key_)
      cur = cur->right_;
    else {
      return false;
    }
  }

  Node<Key, Value>* new_node = new Node<Key, Value>();
  new_node->key_ = key;
  new_node->value_ = value;
  new_node->color_ = RED;
  new_node->left_ = nil_node_;
  new_node->right_ = nil_node_;
  
  if (p_node == nil_node_) {
    root_ = new_node;
    root_->parent_ = nil_node_;
    nil_node_->left_ = root_;
    nil_node_->right_ = root_;
    nil_node_->parent_ = root_;
  } else {
    if (key < p_node->key_) {
      p_node->left_ = new_node;
    } else {
      p_node->right_ = new_node;
    }
    new_node->parent_ = p_node;
  }
  InsertFixUp(new_node);
  return true;
}

template <class Key, class Value>
void RBTree<Key, Value>::InsertFixUp(Node<Key, Value>* node) {
  while (node->parent_->color_ == RED) {
    if (node->parent_ == node->parent_->parent_->left_) {
      Node<Key, Value>* uncle = node->parent_->parent_->right_;
      if (uncle->color_ == RED) {
        node->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        node = node->parent_->parent_;
      } else if (uncle->color_ == BLACK) {
        if (node == node->parent_->right_) {
          node = node->parent_;
          LeftRotate(node);
        } else {
          node->parent_->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          RightRotate(node->parent_->parent_);
        }
      }
    } else {
      Node<Key, Value>* uncle = node->parent_->parent_->left_;
      if (uncle->color_ == RED) {
        node->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        node = node->parent_->parent_;
      } else if (uncle->color_ == BLACK) {
        if (node == node->parent_->left_) {
          node = node->parent_;
          RightRotate(node);
        } else {
          node->parent_->color_ = BLACK;
          node->parent_->parent_->color_ = RED;
          LeftRotate(node->parent_->parent_);
        }
      }
    }
  }
  root_->color_ = BLACK;
}


template <typename Key, typename Value>
void RBTree<Key, Value>::InOrderPrint(Node<Key, Value>* node) {
  if (node == nil_node_) {
    return;
  }
  else {
    InOrderPrint(node->left_);
    std::cout << node->key_ << ": " << node->value_ << std::endl;
    InOrderPrint(node->right_);
  }
}


template <typename Key, typename Value>
Node<Key, Value>* RBTree<Key, Value>::Search(const Key& key) {
  Node<Key, Value>* s_node = root_;
  while (s_node != nil_node_) {
    if (key < s_node->key_) {
      s_node = s_node->left_;
    } else if (key > s_node->key_) {
      s_node = s_node->right_;
    } else {
      return s_node;
    }
  }
  return s_node;
}

template <typename Key, typename Value>
Node<Key, Value>* RBTree<Key, Value>::GetSuccessor(Node<Key, Value>* node) {
  if (node == nil_node_)
    return nil_node_;
  Node<Key, Value>* successor = node->left_;
  while (successor != nil_node_) {
    if (successor->right_ != nil_node_)
      successor = successor->right_;
    else
      break;
  }
  
  if (successor == nil_node_) {
    Node<Key, Value>* p_node = node->parent_;
    successor = node;
    while (p_node != nil_node_ && successor == p_node->right_) {
      successor = p_node;
      p_node = p_node->parent_;
    }
    successor = p_node;
  }

  return successor;
}

template <typename Key, typename Value>
bool RBTree<Key, Value>::Delete(const Key& key) {
  Node<Key, Value>* cur = Search(key);
  if (cur == nil_node_)
    return false;
  if (cur->left_ != nil_node_ && cur->right_ != nil_node_) {
    Node<Key, Value>* successor = GetSuccessor(cur);
    cur->value_ = successor->value_;
    cur->key_ = successor->key_;
    cur = successor;
  }

  Node<Key, Value>* cur_successor;
  if (cur->right_ != nil_node_)
    cur_successor = cur->right_;
  else
    cur_successor = cur->left_;
  cur_successor->parent_ = cur->parent_;
  
  // If delete the root node
  if (cur->parent_ == nil_node_) {
    root_ = cur_successor;
    nil_node_->parent_ = root_;
    nil_node_->left_ = root_;
    nil_node_->right_ = root_;
  } else if (cur == cur->parent_->right_) {
    cur->parent_->right_ = cur_successor;
  } else {
    cur->parent_->left_ = cur_successor;
  }

  if (cur->color_ == BLACK &&
      !(cur_successor == nil_node_ &&
        cur_successor->parent_ == nil_node_)) {
    DeleteFixUp(cur_successor);
  }
  delete cur;
  return true;
}


template <typename Key, typename Value>
void RBTree<Key, Value>::DeleteFixUp(Node<Key, Value>* node) {
  while (node != root_ && node->color_ == BLACK) {
    if (node == node->parent_->left_) {
      Node<Key, Value>* b_node = node->parent_->right_;
      if (b_node->color_ == RED) {                     // CASE 1
        b_node->color_ = BLACK;
        node->parent_->color_ = RED;
        LeftRotate(node->parent_);
      } else {
        if (b_node->left_->color_ == BLACK &&          // CASE 2
            b_node->right_->color_ == BLACK) {
          b_node->color_ = RED;
          node = b_node->parent_;
        } else if (b_node->right_->color_ == BLACK) {  // CASE 3
          b_node->color_ = RED;
          b_node->left_->color_ = BLACK;
          RightRotate(b_node);
        } else if (b_node->right_->color_ == RED) {    // CASE 4
          b_node->color_ = b_node->parent_->color_;
          b_node->right_->color_ = BLACK;
          b_node->parent_->color_ = BLACK;
          LeftRotate(b_node->parent_);
          node = root_;
        }
      }
    } else {
      Node<Key, Value>* b_node = node->parent_->left_;
      if (b_node->color_ == RED) {                      // CASE 1
        b_node->color_ = BLACK;
        node->parent_->color_ = RED;
        RightRotate(node->parent_);
      } else {
        if (b_node->left_->color_ == BLACK &&           // CASE 2
            b_node->right_->color_ == BLACK) {
          b_node->color_ = RED;
          node = b_node->parent_;
        } else if (b_node->left_->color_ == BLACK) {   // CASE 3
          b_node->color_ = RED;
          b_node->right_->color_ = BLACK;
          LeftRotate(b_node);
        } else if (b_node->left_->color_ == RED) {
          b_node->color_ = node->parent_->color_;
          b_node->right_->color_ = BLACK;
          b_node->left_->color_ = BLACK;
          RightRotate(b_node->parent_);
          node = root_;
        }
      }
    }
  }

  nil_node_->parent_ = root_;
  node->color_ = BLACK;
}

#endif  //RBTREE_H_
