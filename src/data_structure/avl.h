#pragma once

#include <cstddef>
#include <string>

template <typename T> class AVLNode {
public:
  AVLNode(T val);
  AVLNode<T> *_left;
  AVLNode<T> *_right;
  T _value;
  int _height;
};

template <typename T> class AVLTree {
public:
  explicit AVLTree(T val);

  std::string ToString() const;
  bool Search(const T &val);
  void Insert(const T &val);
  void Delete(const T &val);

private:
  AVLNode<T> *_root{nullptr};

  // Internal helpers
  AVLNode<T> *insertParent(AVLNode<T> *parent, const T &val);
  AVLNode<T> *deleteParent(AVLNode<T> *parent, const T &val);
  AVLNode<T> *updateParent(AVLNode<T> *parent);
  AVLNode<T> *rotateLeft(AVLNode<T> *x);
  AVLNode<T> *rotateRight(AVLNode<T> *x);
  int nodeHeight(AVLNode<T> *node);
  int nodeBalance(AVLNode<T> *node);
  void adjustHeight(AVLNode<T> *node);
  AVLNode<T> *nodePredecessor(AVLNode<T> *node);
  AVLNode<T> *nodeSuccessor(AVLNode<T> *node);
};
