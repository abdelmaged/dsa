#include "hash_table_open.h"

#include <sstream>

#include "linked_list.h"

template <typename K, typename V>
HashTableOpen<K, V>::HashTableOpen(int size, HashFnT h_fn)
    : _size(size), _hash_fn(h_fn) {
  _table.resize(_size);
}

template <typename K, typename V>
std::string HashTableOpen<K, V>::ToString() const {
  std::ostringstream oss;
  for (const auto &bucket : _table) {
    oss << "{";
    oss << bucket.ToString();
    oss << "} ";
  }

  return oss.str();
}

template <typename K, typename V>
bool HashTableOpen<K, V>::Insert(const K &key, const V &val) {
  size_t h_idx = hashIdx(key);

  if (findNode(key, h_idx)) {
    return false;
  }

  auto hnode = HashNodeOpen<K, V>(key, val);
  _table[h_idx].PushBack(hnode);

  return true;
}

template <typename K, typename V>
bool HashTableOpen<K, V>::Delete(const K &key) {
  size_t h_idx = hashIdx(key);

  Node<HashNodeOpen<K, V>> *node = findNode(key, h_idx);
  if (!node) {
    return false;
  }

  _table[h_idx].Delete(node);
  return true;
}

template <typename K, typename V>
const V *HashTableOpen<K, V>::Search(const K &key) const {
  size_t h_idx = hashIdx(key);

  auto node = findNode(key, h_idx);
  return node ? &(node->Value()._val) : nullptr;
}

template <typename K, typename V>
size_t HashTableOpen<K, V>::hashIdx(const K &key) const {
  size_t h = _hash_fn(key);
  return h % _size;
}

template <typename K, typename V>
Node<HashNodeOpen<K, V>> *HashTableOpen<K, V>::findNode(const K &key,
                                                    size_t h_idx) const {
  const auto &bucket = _table[h_idx];
  HashNodeOpen<K, V> hnode = HashNodeOpen<K, V>(key);
  return bucket.Search(hnode);
}

template class HashTableOpen<int, int>;