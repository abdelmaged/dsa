#pragma once

#include <string>
#include <cstddef>

template <typename T>
struct Node {
  T _val;
  Node<T>* _prev{nullptr};
  Node<T>* _next{nullptr};

  Node() = default;
  explicit Node(const T& v) : _val(v), _prev(nullptr), _next(nullptr) {}

  const T& Value() const;
};

template <typename T>
class LinkedList {
public:
  LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}
  ~LinkedList();

  std::string ToString() const;

  void PushBack(const T& val);

  void Delete(Node<T> *node);

  Node<T> *Search(const T& val) const;

protected:
  Node<T>* _head{nullptr};
  Node<T>* _tail{nullptr};
  std::size_t _size{0};
};
