#include "hash_node_open.h"

template <typename K, typename V>
HashNodeOpen<K, V>::HashNodeOpen(const K &key) : _key(key) {}

template <typename K, typename V>
HashNodeOpen<K, V>::HashNodeOpen(const K &key, const V &val) : _key(key), _val(val) {}

template <typename K, typename V>
bool HashNodeOpen<K, V>::operator==(const HashNodeOpen<K, V> &other) const {
  return _key == other._key;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const HashNodeOpen<K, V> &hnode) {
  os << "{" << hnode._key << ", " << hnode._val << "}";
  return os;
}

template class HashNodeOpen<int, int>;

template std::ostream &
operator<< <int, int>(std::ostream &os, const HashNodeOpen<int, int> &hnode);