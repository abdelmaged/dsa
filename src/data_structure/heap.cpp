#include "heap.h"

#include <stdexcept>
#include <utility>
#include <vector>
#include <queue>
#include <sstream>

template <typename T> Heap<T>::Heap() {}

template <typename T> void Heap<T>::Insert(const T &val) {
  _arr.push_back(val);
  heapifyUp(_arr.size() - 1);
}

template <typename T> const T &Heap<T>::Top() const {
  if (_arr.empty()) {
    throw std::out_of_range("Heap is empty!");
  }
  return _arr[0];
}

template <typename T> void Heap<T>::Pop() {
  if (_arr.empty()) {
    throw std::out_of_range("Heap is empty!");
  }

  std::swap(_arr[0], _arr[_arr.size() - 1]);
  _arr.pop_back();
  heapifyDown(0);
}

template <typename T> void Heap<T>::heapifyUp(size_t node) {
  size_t parent;

  while (node != 0) {
    parent = parentNode(node);
    if (_arr[node] >= _arr[parent]) {
      break;
    }
    std::swap(_arr[node], _arr[parent]);
    node = parent;
  }
}

template <typename T> void Heap<T>::heapifyDown(size_t node) {
  size_t left;
  size_t right;
  size_t len = _arr.size();
  size_t next;

  while (true) {
    next = node;
    left = leftNode(node);
    right = rightNode(node);
    if (left < len && _arr[left] < _arr[next]) {
      next = left;
    }
    if (right < len && _arr[right] < _arr[next]) {
      next = right;
    }
    if (next == node) {
      break;
    }
    std::swap(_arr[node], _arr[next]);
    node = next;
  }
}

template <typename T> size_t Heap<T>::leftNode(size_t parent) const {
  return parent * 2 + 1;
}

template <typename T> size_t Heap<T>::rightNode(size_t parent) const {
  return parent * 2 + 2;
}

template <typename T> size_t Heap<T>::parentNode(size_t child) const {
  return (child - 1) / 2;
}

template <typename T> size_t Heap<T>::Size() const {
  return _arr.size();
}

template <typename T> std::string Heap<T>::ToString() const {
  std::ostringstream oss;
  std::queue<size_t> q;
  size_t len = _arr.size();

  q.push(0);
  while (!q.empty()) {
    oss << "(";
    int n = (int)q.size();
    while (n--) {
      auto curr = q.front();
      q.pop();
      if (curr < len) {
        q.push(leftNode(curr));
        q.push(rightNode(curr));
        oss << _arr[curr];
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
template <typename T>
const std::vector<T>& Heap<T>::Array() const {
  return _arr;
}

template class Heap<int>;