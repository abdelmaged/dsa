#pragma once

#include <vector>

class MergeSort {
public:
  void Sort(std::vector<int> &vec);
  void SortIterative(std::vector<int> &vec);

private:
  void Merge(std::vector<int> &vec, size_t low, size_t mid, size_t high);
  void MergeSortImpl(std::vector<int> &vec, size_t low, size_t high);
};
