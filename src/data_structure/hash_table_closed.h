#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

#include "hash_node_closed.h"

// Header for purpose: declarations for HashTableClosed template class

template <typename K, typename V>
class HashTableClosed {
 public:
  using HashFnT = std::function<size_t(const K &)>;

  HashTableClosed(size_t capacity, HashFnT h_fn);

  bool Insert(const K &key, const V &val);
  bool Delete(const K &key);
  const V *Search(const K &key) const;
  const V *Search(const K &key);

  std::string ToString() const;

 private:
  size_t hashIdx(const K &key) const;

  // find active (occupied) node containing the key; returns nullptr otherwise
  // name variants used across different implementations
  HashNodeClosed<K, V> *findActiveNode(const K &key, size_t h_idx);
  const HashNodeClosed<K, V> *findActiveNode(const K &key, size_t h_idx) const;
  HashNodeClosed<K, V> *findNode(const K &key, size_t h_idx);
  const HashNodeClosed<K, V> *findNode(const K &key, size_t h_idx) const;

  // find an empty or deleted slot suitable for inserting key
  HashNodeClosed<K, V> *findInActiveNode(const K &key, size_t h_idx);
  const HashNodeClosed<K, V> *findInActiveNode(const K &key, size_t h_idx) const;

  size_t probe(size_t h_idx) const;

  std::vector<HashNodeClosed<K, V>> _table;
  size_t _capacity;
  size_t _size;
  HashFnT _hash_fn;
};
