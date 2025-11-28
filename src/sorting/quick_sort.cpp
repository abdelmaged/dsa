#include "quick_sort.h"

#include <utility>
#include <vector>

#include "printer.h"

void QuickSort::Sort(std::vector<int> &vec) {
  PrintVector(vec, "Before Sort");
  QuickSortImpl(vec, 0, vec.size() - 1);
  PrintVector(vec, "After  Sort");
}

size_t QuickSort::PartitionLow(std::vector<int> &vec, size_t low, size_t high) {
  size_t split_idx = high;
  size_t pivot_idx = low;
  int pivot = vec[pivot_idx];

  for (size_t i = high; i != -1; --i) {
    if (vec[i] > pivot) {
      std::swap(vec[i], vec[split_idx]);
      --split_idx;
    }
  }
  std::swap(vec[pivot_idx], vec[split_idx]);
  return split_idx;
}

size_t QuickSort::PartitionHigh(std::vector<int> &vec, size_t low,
                                size_t high) {
  size_t pivot_idx = high;
  int pivot = vec[pivot_idx];

  size_t split_idx = low;
  for (size_t i = low; i <= high; ++i) {
    if (vec[i] < pivot) {
      std::swap(vec[i], vec[split_idx]);
      ++split_idx;
    }
  }
  std::swap(vec[pivot_idx], vec[split_idx]);
  return split_idx;
}

size_t QuickSort::PartitionMid(std::vector<int> &vec, size_t low, size_t high) {
  size_t pivot_idx = low + (high - low) / 2;

  std::swap(vec[pivot_idx], vec[high]);
  return PartitionHigh(vec, low, high);
}

size_t QuickSort::Partition(std::vector<int> &vec, size_t low, size_t high) {
  size_t split_idx;

  PrintRange(vec, low, high, "Before Partition");
  switch (_pivot_strategy) {
  case PivotStrategy::kLow:
    split_idx = PartitionLow(vec, low, high);
  case PivotStrategy::kHigh:
    split_idx = PartitionHigh(vec, low, high);
  case PivotStrategy::kMid:
    split_idx = PartitionMid(vec, low, high);
  }
  PrintRange(vec, low, high, "After  Partition");

  return split_idx;
}

void QuickSort::QuickSortImpl(std::vector<int> &vec, size_t low, size_t high) {
  if (low >= high) {
    return;
  }

  size_t split_loc = Partition(vec, low, high);
  if (split_loc) {
    QuickSortImpl(vec, low, split_loc - 1);
  }
  QuickSortImpl(vec, split_loc + 1, high);
}

// int main(int argc, char **argv) {
//   std::vector<std::vector<int>> tests = {
//       {10, 5, 20, 30, 15, 100, 90, 8},
//       {8, 7, 1, 2, 6, 9, 10, 2, 11},
//       {5, 5, 5, 5, 5, 5, 5, 5, 5},
//   };

//   QuickSort qs(QuickSort::PivotStrategy::kMid);

//   for (auto &t : tests) {
//     qs.sort(t);
//   }

//   return 0;
// }
