#include "bubble_sort.h"

#include <vector>

#include "printer.h"

void BubbleSort::Sort(std::vector<int>& vec) {
  PrintVector(vec, "Before Sort");
  bool swapped = true;
  for (size_t i = 0; i < vec.size() && swapped; ++i) {
    swapped = false;
    for (size_t j = 1; j < vec.size(); ++j) {
      if (vec[j] < vec[j - 1]) {
        std::swap(vec[j], vec[j - 1]);
        swapped = true;
      }
    }
  }
  PrintVector(vec, "After  Sort");
}
