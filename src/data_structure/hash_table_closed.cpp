#include "hash_table_closed.h"

#include "hash_node_closed.h"
#include <sstream>
#include <stdexcept>

template <typename K, typename V>
HashTableClosed<K, V>::HashTableClosed(size_t capacity, HashFnT h_fn)
    : _capacity(capacity), _size(0), _hash_fn(h_fn) {
  _table.resize(capacity);
}

template <typename K, typename V>
bool HashTableClosed<K, V>::Insert(const K &key, const V &val) {
  if (_size == _capacity) {
    throw std::length_error("Max capacity reached");
  }

  size_t h_idx = hashIdx(key);

  HashNodeClosed<K, V> *node = findActiveNode(key, h_idx);

  if (node) {
    return false;
  }

  ++_size;
  node = findInActiveNode(key, h_idx);
  node->_key = key;
  node->_val = val;
  node->_state = HashNodeClosed<K, V>::HashNodeState::kOccupied;

  return true;
}

template <typename K, typename V>
bool HashTableClosed<K, V>::Delete(const K &key) {
  size_t h_idx = hashIdx(key);

  HashNodeClosed<K, V> *node = findActiveNode(key, h_idx);

  if (!node) {
    return false;
  }

  --_size;
  node->_state = HashNodeClosed<K, V>::HashNodeState::kDeleted;

  return true;
}

template <typename K, typename V>
const V *HashTableClosed<K, V>::Search(const K &key) {
  size_t h_idx = hashIdx(key);

  HashNodeClosed<K, V> *node = findActiveNode(key, h_idx);

  if (!node) {
    return nullptr;
  }
  return &node->_val;
}

template <typename K, typename V>
std::string HashTableClosed<K, V>::ToString() const {
  std::ostringstream oss;
  for (auto &node : _table) {
    oss << node << " ";
  }
  return oss.str();
}

template <typename K, typename V>
size_t HashTableClosed<K, V>::hashIdx(const K &key) const {
  size_t h = _hash_fn(key);
  return h % _capacity;
}

template <typename K, typename V>
HashNodeClosed<K, V> *HashTableClosed<K, V>::findActiveNode(const K &key,
                                                            size_t h_idx) {
  HashNodeClosed<K, V> *node = &_table[h_idx];

  while (true) {
    switch (node->_state) {
    case HashNodeClosed<K, V>::HashNodeState::kEmpty:
      // not found
      return nullptr;
    case HashNodeClosed<K, V>::HashNodeState::kOccupied:
      if (node->_key == key) {
        // found
        return node;
      }
      // probe
      break;
    case HashNodeClosed<K, V>::HashNodeState::kDeleted:
      // probe
      break;
    }
    h_idx = probe(h_idx);
    node = &_table[h_idx];
  }

  return nullptr;
}

template <typename K, typename V>
HashNodeClosed<K, V> *HashTableClosed<K, V>::findInActiveNode(const K &key,
                                                              size_t h_idx) {
  HashNodeClosed<K, V> *node = &_table[h_idx];

  while (true) {
    switch (node->_state) {
    case HashNodeClosed<K, V>::HashNodeState::kEmpty:
      return node;
    case HashNodeClosed<K, V>::HashNodeState::kOccupied:
      // probe
      break;
    case HashNodeClosed<K, V>::HashNodeState::kDeleted:
      return node;
    }
    h_idx = probe(h_idx);
    node = &_table[h_idx];
  }

  return nullptr;
}
template <typename K, typename V>
size_t HashTableClosed<K, V>::probe(size_t h_idx) const {
  ++h_idx;
  return h_idx % _capacity;
}

template class HashTableClosed<int, int>;