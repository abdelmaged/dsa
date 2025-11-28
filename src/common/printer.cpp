#include <iostream>
#include <vector>

void PrintVector(const std::vector<int> &vec, const char *title) {
  std::cout << title << ":";
  for (auto &val : vec) {
    std::cout << " " << val;
  }
  std::cout << std::endl;
}

void PrintRange(const std::vector<int> &vec, size_t low, size_t high,
                const char *title) {
  std::cout << title << ":";
  for (size_t i = low; i <= high; ++i) {
    std::cout << " " << vec[i];
  }
  std::cout << std::endl;
}
