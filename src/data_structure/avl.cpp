#include "avl.h"

#include <algorithm>
#include <queue>
#include <sstream>
#include <string>

template <typename T>
AVLNode<T>::AVLNode(T val)
    : _left(nullptr), _right(nullptr), _value(val), _height(1) {}

template <typename T> AVLTree<T>::AVLTree(T val) {
  _root = new AVLNode<T>(val);
}

template <typename T> std::string AVLTree<T>::ToString() const {
  std::ostringstream oss;
  std::queue<AVLNode<T> *> q;

  q.push(_root);
  while (!q.empty()) {
    oss << "(";
    int n = (int)q.size();
    while (n--) {
      auto curr = q.front();
      q.pop();
      if (curr) {
        q.push(curr->_left);
        q.push(curr->_right);
        oss << curr->_value;
      } else {
        oss << "N";
      }
      if (n) {
        oss << ", ";
      }
    }
    oss << ") ";
  }

  return oss.str();
}

template <typename T> bool AVLTree<T>::Search(const T &val) {
  AVLNode<T> *curr = _root;
  while (curr) {
    if (val == curr->_value) {
      return true;
    }
    if (val < curr->_value) {
      curr = curr->_left;
    } else {
      curr = curr->_right;
    }
  }
  return false;
}

template <typename T> void AVLTree<T>::Insert(const T &val) {
  _root = insertParent(_root, val);
}

template <typename T>
AVLNode<T> *AVLTree<T>::insertParent(AVLNode<T> *parent, const T &val) {
  if (!parent) {
    return new AVLNode<T>(val);
  }

  if (val < parent->_value) {
    parent->_left = insertParent(parent->_left, val);
  } else if (val > parent->_value) {
    parent->_right = insertParent(parent->_right, val);
  } else {
    // equal keys
    return parent;
  }

  return updateParent(parent);
}

template <typename T> void AVLTree<T>::Delete(const T &val) {
  _root = deleteParent(_root, val);
}

template <typename T>
AVLNode<T> *AVLTree<T>::deleteParent(AVLNode<T> *parent, const T &val) {
  if (!parent) {
    return nullptr;
  }

  if (val < parent->_value) {
    parent->_left = deleteParent(parent->_left, val);
  } else if (val > parent->_value) {
    parent->_right = deleteParent(parent->_right, val);
  } else {
    if (parent->_left && parent->_right) {
      AVLNode<T> *pred = nodePredecessor(parent);
      parent->_value = pred->_value;
      parent->_left = deleteParent(parent->_left, pred->_value);
    } else {
      AVLNode<T> *pred_succ = parent->_left ? parent->_left : parent->_right;
      delete parent;
      return  pred_succ;
    }
  }

  return updateParent(parent);
}

template <typename T>
AVLNode<T>* AVLTree<T>::updateParent(AVLNode<T> *parent) {
  adjustHeight(parent);

  int balance = nodeBalance(parent);

  if (balance > 1) {
    if (nodeBalance(parent->_left) >= 0) {
      // LL
      return rotateRight(parent);
    } else {
      // LR
      parent->_left = rotateLeft(parent->_left);
      return rotateRight(parent);
    }
  } else if (balance < -1) {
    if (nodeBalance(parent->_right) <= 0) {
      // RR
      return rotateLeft(parent);
    } else {
      // RL
      parent->_right = rotateRight(parent->_right);
      return rotateLeft(parent);

    }
  }

  return parent;
}

template <typename T> AVLNode<T> *AVLTree<T>::rotateLeft(AVLNode<T> *x) {
  AVLNode<T> *y = x->_right;
  AVLNode<T> *l = y->_left;

  x->_right = l;
  y->_left = x;

  adjustHeight(x);
  adjustHeight(y);

  return y;
}

template <typename T> AVLNode<T> *AVLTree<T>::rotateRight(AVLNode<T> *x) {
  AVLNode<T> *y = x->_left;
  AVLNode<T> *r = y->_right;

  x->_left = r;
  y->_right = x;

  adjustHeight(x);
  adjustHeight(y);

  return y;
}

template <typename T> int AVLTree<T>::nodeHeight(AVLNode<T> *node) {
  if (!node) {
    return 0;
  }
  return node->_height;
}

template <typename T> int AVLTree<T>::nodeBalance(AVLNode<T> *node) {
  if (!node) {
    return 0;
  }
  return nodeHeight(node->_left) - nodeHeight(node->_right);
}

template <typename T> void AVLTree<T>::adjustHeight(AVLNode<T> *node) {
  int l_h = nodeHeight(node->_left);
  int r_h = nodeHeight(node->_right);

  node->_height = std::max(l_h, r_h) + 1;
}

template <typename T>
AVLNode<T>* AVLTree<T>::nodePredecessor(AVLNode<T> *node) {
  AVLNode<T> *curr = node->_left;
  while (curr && curr->_right) {
    curr = curr->_right;
  }
  return curr;
}

template <typename T>
AVLNode<T>* AVLTree<T>::nodeSuccessor(AVLNode<T> *node) {
  AVLNode<T> *curr = node->_right;
  while (curr && curr->_left) {
    curr = curr->_left;
  }
  return curr;
}

template class AVLNode<int>;
template class AVLTree<int>;
