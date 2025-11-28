#pragma once

#include <cstddef>
#include <string>
#include <vector>

template <typename T> class Heap {
public:
  Heap();
  void Insert(const T &val);
  const T &Top() const;
  void Pop();

  std::size_t Size() const;
  std::string ToString() const;
  const std::vector<T> &Array() const;

private:
  void heapifyUp(size_t node);
  void heapifyDown(size_t node);
  std::size_t leftNode(size_t parent) const;
  std::size_t rightNode(size_t parent) const;
  std::size_t parentNode(size_t child) const;

  std::vector<T> _arr;
};
