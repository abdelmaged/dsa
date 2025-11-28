#pragma once

#include <ostream>

template <typename K, typename V> class HashNodeClosed {
public:
  enum class HashNodeState { kEmpty, kOccupied, kDeleted };

  HashNodeClosed() : _state(HashNodeState::kEmpty) {}
  HashNodeClosed(const K &key) : _key(key), _state(HashNodeState::kEmpty) {}
  HashNodeClosed(const K &key, const V &val)
      : _key(key), _val(val), _state(HashNodeState::kOccupied) {}

  bool operator==(const HashNodeClosed<K, V> &other) const;

  template <typename TK, typename TV>
  friend std::ostream &operator<<(std::ostream &os,
                                  const HashNodeClosed<TK, TV> &hnode);

  K _key{};
  V _val{};
  HashNodeState _state{HashNodeState::kEmpty};
};
