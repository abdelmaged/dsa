#include "linked_list.h"
#include "hash_node_open.h"

#include <sstream>

template <typename T> const T &Node<T>::Value() const { return _val; }

template <typename T> LinkedList<T>::~LinkedList() {
  Node<T> *curr = _head;
  Node<T> *next;

  while (curr) {
    next = curr->_next;
    delete curr;
    curr = next;
  }
}

template <typename T> std::string LinkedList<T>::ToString() const {
  std::ostringstream oss;

  Node<T> *curr = _head;
  while (curr) {
    // oss << curr->_prev << ", ";
    // oss << curr << ", ";
    // oss << curr->_next << ", ";
    oss << curr->_val;
    curr = curr->_next;
    if (curr) {
      oss << ", ";
    }
  }
  return oss.str();
}

template <typename T> void LinkedList<T>::PushBack(const T &val) {
  Node<T> *node = new Node<T>(val);

  if (!_head) {
    _head = _tail = node;
  } else {
    node->_prev = _tail;
    _tail->_next = node;
    _tail = node;
  }
  ++_size;
}

template <typename T> void LinkedList<T>::Delete(Node<T> *node) {

  if (node->_prev) {
    node->_prev->_next = node->_next;
  } else {
    _head = node->_next;
  }

  if (node->_next) {
    node->_next->_prev = node->_prev;
  } else {
    _tail = node->_prev;
  }

  node->_next = node->_prev = nullptr;
  --_size;
  delete node;
}

template <typename T> Node<T> *LinkedList<T>::Search(const T &val) const {
  auto curr = _head;
  while (curr) {
    if (curr->_val == val) {
      return curr;
    }
    curr = curr->_next;
  }
  return nullptr;
}

template class Node<int>;
template class LinkedList<int>;

template class Node<HashNodeOpen<int, int>>;
template class LinkedList<HashNodeOpen<int, int>>;
