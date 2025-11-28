#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

#include "hash_node_open.h"
#include "linked_list.h"

template <typename K, typename V> class HashTableOpen {
public:
  using HashFnT = std::function<size_t(const K &)>;

  HashTableOpen(int size, HashFnT h_fn);
  std::string ToString() const;
  bool Insert(const K &key, const V &val);
  bool Delete(const K &key);
  const V *Search(const K &key) const;

private:
  size_t hashIdx(const K &key) const;
  Node<HashNodeOpen<K, V>> *findNode(const K &key, size_t h_idx) const;

  std::vector<LinkedList<HashNodeOpen<K, V>>> _table;
  int _size;
  HashFnT _hash_fn;
};
