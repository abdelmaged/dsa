#include "union_find.h"

#include <sstream>
#include <unordered_map>
#include <vector>

UnionFind::UnionFind(int n) {
  parent_.assign(n, 0);
  rank_.assign(n, 0);
  for (int i = 0; i < n; ++i) {
    parent_[i] = i;
  }
}

int UnionFind::FindSet(int i) {
  while (parent_[i] != i) {
    i = parent_[i] = parent_[parent_[i]];
  }
  return i;
}

void UnionFind::UnionSet(int i, int j) {
  i = FindSet(i);
  j = FindSet(j);

  if (i == j) {
    return;
  }

  auto merge = [&](int parent, int child) -> void {
    parent_[child] = parent;
    if (rank_[parent] == rank_[child]) {
      ++rank_[parent];
    }
  };

  if (rank_[i] > rank_[j]) {
    merge(i, j);
  } else {
    merge(j, i);
  }
}

std::string UnionFind::ToString() const {
  std::ostringstream oss;
  for (int i = 0; i < parent_.size(); ++i) {
    oss << "(";
    oss << i << ", " << parent_[i] << ", " << rank_[i];
    oss << ") ";
  }

  return oss.str();
}

std::unordered_map<int, std::vector<int>> UnionFind::MergedSets() {
  std::unordered_map<int, std::vector<int>> groups;
  for (int i = 0; i < parent_.size(); ++i) {
    int root = FindSet(i);
    groups[root].push_back(i);
  }
  return groups;
}