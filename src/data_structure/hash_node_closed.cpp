#include "hash_node_closed.h"

template <typename K, typename V>
bool HashNodeClosed<K, V>::operator==(const HashNodeClosed<K, V> &other) const {
  if (other._state != HashNodeState::kOccupied) {
    return false;
  }
  return _key == other._key;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const HashNodeClosed<K, V> &hnode) {
  switch (hnode._state) {
  case HashNodeClosed<K, V>::HashNodeState::kEmpty:
    os << "{E}";
    break;
  case HashNodeClosed<K, V>::HashNodeState::kOccupied:
    os << "{" << hnode._key << ", " << hnode._val << "}";
    break;
  case HashNodeClosed<K, V>::HashNodeState::kDeleted:
    os << "{D}";
    break;
  }
  return os;
}

template class HashNodeClosed<int, int>;

template std::ostream &
operator<< <int, int>(std::ostream &os, const HashNodeClosed<int, int> &hnode);