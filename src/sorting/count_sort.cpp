#include "count_sort.h"

#include <algorithm>
#include <vector>

#include "printer.h"

void CountSort::Sort(std::vector<int> &vec) {
  if (vec.empty()) {
    return;
  }
  PrintVector(vec, "Before Sort");
  int mx_val = vec[0];
  for (auto& val : vec) {
    mx_val = std::max(mx_val, val);
  }

  std::vector<int> counting(mx_val + 1, 0);
  for (auto& val : vec) {
    ++counting[val];
  }

  for(size_t i = 1; i <= mx_val; ++i) {
    counting[i] += counting[i - 1];
  }

  std::vector<int> temp(vec.size());
  for (size_t i = vec.size() - 1; i != -1; --i) {
    temp[counting[vec[i]]-- - 1] = vec[i];
  }

  for (size_t i = vec.size() - 1; i != -1; --i) {
    vec[i] = temp[i];
  }
  PrintVector(vec, "After  Sort");
}

void CountSort::SortBasic(std::vector<int> &vec) {
  PrintVector(vec, "Before Sort");
  auto mx_it = std::max_element(vec.begin(), vec.end());
  std::vector<int> counting(*mx_it + 1, 0);
  for (auto& val : vec) {
    ++counting[val];
  }
  size_t k = 0;
  for (int i = 0; i < counting.size(); ++i) {
    while(counting[i]--) {
      vec[k++] = i;
    }
  }
  PrintVector(vec, "After  Sort");
}