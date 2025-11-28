#pragma once

#include <ostream>

template <typename K, typename V>
class HashNodeOpen {
 public:
  HashNodeOpen() = default;
  explicit HashNodeOpen(const K &key);
  HashNodeOpen(const K &key, const V &val);

  bool operator==(const HashNodeOpen<K, V> &other) const;

  template <typename TK, typename TV>
  friend std::ostream &operator<<(std::ostream &os, const HashNodeOpen<TK, TV> &hnode);

  K _key{};
  V _val{};
};

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const HashNodeOpen<K, V> &hnode);
