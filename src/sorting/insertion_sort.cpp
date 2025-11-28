#include "insertion_sort.h"

#include <vector>

#include "printer.h"

void InsertionSort::Sort(std::vector<int>& vec) {
  PrintVector(vec, "Before Sort");
  for (size_t i = 0; i < vec.size(); ++i) {
    size_t mn_k = i;
    size_t mn_val = vec[i];
    for (size_t j = i + 1; j < vec.size(); ++j) {
      if (vec[j] < mn_val) {
        mn_val = vec[j];
        mn_k = j;
      }
    }
    std::swap(vec[i], vec[mn_k]);
  }
  PrintVector(vec, "After  Sort");
}
