#include "binary_search.h"

int BinarySearch::FindGreater(const std::vector<int> &nums, int target) const {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (nums[mid] <= target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return left < nums.size() ? left : -1;
}

int BinarySearch::FindGreaterEqual(const std::vector<int> &nums,
                                   int target) const {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return left < nums.size() ? left : -1;
}

int BinarySearch::FindExact(const std::vector<int> &nums, int target) const {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (nums[mid] == target) {
      return mid;
    }

    if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}

int BinarySearch::FindSmallerEqual(const std::vector<int> &nums,
                                   int target) const {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (nums[mid] <= target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return left > 0 ? left - 1 : -1;
}

int BinarySearch::FindSmaller(const std::vector<int> &nums, int target) const {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return left > 0 ? left - 1 : -1;
}
