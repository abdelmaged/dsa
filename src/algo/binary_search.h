#pragma once

#include <vector>

class BinarySearch {
public:
  int FindGreater(const std::vector<int> &nums, int target) const;
  int FindGreaterEqual(const std::vector<int> &nums, int target) const;
  int FindExact(const std::vector<int> &nums, int target) const;
  int FindSmallerEqual(const std::vector<int> &nums, int target) const;
  int FindSmaller(const std::vector<int> &nums, int target) const;
};
