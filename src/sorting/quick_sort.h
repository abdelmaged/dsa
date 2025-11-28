#pragma once

#include <cstddef>
#include <vector>

class QuickSort {
public:
  enum class PivotStrategy { kLow, kHigh, kMid };

  QuickSort(PivotStrategy pivot_strategy = PivotStrategy::kMid)
      : _pivot_strategy(pivot_strategy) {}

  void Sort(std::vector<int> &vec);

private:
  size_t PartitionLow(std::vector<int> &vec, size_t low, size_t high);
  size_t PartitionHigh(std::vector<int> &vec, size_t low, size_t high);
  size_t PartitionMid(std::vector<int> &vec, size_t low, size_t high);
  size_t Partition(std::vector<int> &vec, size_t low, size_t high);
  void QuickSortImpl(std::vector<int> &vec, size_t low, size_t high);

  PivotStrategy _pivot_strategy{PivotStrategy::kMid};
};
