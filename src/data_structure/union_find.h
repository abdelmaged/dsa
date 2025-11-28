#pragma once

#include <unordered_map>
#include <vector>

class UnionFind {
public:
  UnionFind(int n);
  int FindSet(int i);
  void UnionSet(int i, int j);
  std::unordered_map<int, std::vector<int>> MergedSets();

  std::string ToString() const;

private:
  std::vector<int> parent_;
  std::vector<int> rank_;
};