#include "merge_sort.h"

#include <vector>

#include "printer.h"

void MergeSort::Merge(std::vector<int> &vec, size_t low, size_t mid, size_t high) {
  PrintRange(vec, low, high, "Before Merge");
  size_t len = high - low + 1;
  std::vector<int> temp(len);

  size_t i = low;
  size_t j = mid + 1;
  size_t k = 0;

  while (i <= mid && j <= high) {
    if (vec[i] <= vec[j]) {
      temp[k++] = vec[i++];
    } else {
      temp[k++] = vec[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = vec[i++];
  }

  while (j <= high) {
    temp[k++] = vec[j++];
  }

  for (i = low, j = 0; i <= high; ++i, ++j) {
    vec[i] = temp[j];
  }
  PrintRange(vec, low, high, "After  Merge");
}

void MergeSort::MergeSortImpl(std::vector<int> &vec, size_t low, size_t high) {
  if (low == high) {
    return;
  }
  size_t mid = low + (high - low) / 2;
  MergeSortImpl(vec, low, mid);
  MergeSortImpl(vec, mid + 1, high);
  Merge(vec, low, mid, high);
}

void MergeSort::Sort(std::vector<int> &vec) {
  if (vec.empty()) {
    return;
  }
  PrintVector(vec, "Before Sort");
  MergeSortImpl(vec, 0, vec.size() - 1);
  PrintVector(vec, "After  Sort");
};

void MergeSort::SortIterative(std::vector<int> &vec) {
  if (vec.empty()) {
    return;
  }

  PrintVector(vec, "Before Sort");
  // 1, 2, 4, ... , n/2
  for (size_t subarray_size = 1; subarray_size < vec.size(); subarray_size *= 2) {
    size_t low = 0;
    while (low + subarray_size < vec.size()) {
      size_t mid  = low + subarray_size - 1;
      size_t high = std::min(low + 2*subarray_size - 1, vec.size() - 1);
      Merge(vec, low, mid, high);
      low += 2 * subarray_size;
    }
  }
  PrintVector(vec, "After  Sort");
};
