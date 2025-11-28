#include <gtest/gtest.h>

#include "binary_search.h"

TEST(AlgoTest, BinarySearch) {
  std::vector<int> nums{0, 2, 4, 6, 8, 10};

  BinarySearch bs;

  EXPECT_EQ(bs.FindExact(nums, 0), 0);
  EXPECT_EQ(bs.FindExact(nums, 2), 1);
  EXPECT_EQ(bs.FindExact(nums, 4), 2);
  EXPECT_EQ(bs.FindExact(nums, 6), 3);
  EXPECT_EQ(bs.FindExact(nums, 8), 4);
  EXPECT_EQ(bs.FindExact(nums, 10), 5);
  EXPECT_EQ(bs.FindExact(nums, -1), -1);
  EXPECT_EQ(bs.FindExact(nums, 1), -1);
  EXPECT_EQ(bs.FindExact(nums, 3), -1);
  EXPECT_EQ(bs.FindExact(nums, 5), -1);
  EXPECT_EQ(bs.FindExact(nums, 7), -1);
  EXPECT_EQ(bs.FindExact(nums, 9), -1);
  EXPECT_EQ(bs.FindExact(nums, 11), -1);

  EXPECT_EQ(bs.FindGreaterEqual(nums, 0), 0);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 2), 1);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 4), 2);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 6), 3);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 8), 4);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 10), 5);
  EXPECT_EQ(bs.FindGreaterEqual(nums, -1), 0);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 1), 1);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 3), 2);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 5), 3);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 7), 4);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 9), 5);
  EXPECT_EQ(bs.FindGreaterEqual(nums, 11), -1);

  EXPECT_EQ(bs.FindGreater(nums, 0), 1);
  EXPECT_EQ(bs.FindGreater(nums, 2), 2);
  EXPECT_EQ(bs.FindGreater(nums, 4), 3);
  EXPECT_EQ(bs.FindGreater(nums, 6), 4);
  EXPECT_EQ(bs.FindGreater(nums, 8), 5);
  EXPECT_EQ(bs.FindGreater(nums, 10), -1);
  EXPECT_EQ(bs.FindGreater(nums, -1), 0);
  EXPECT_EQ(bs.FindGreater(nums, 1), 1);
  EXPECT_EQ(bs.FindGreater(nums, 3), 2);
  EXPECT_EQ(bs.FindGreater(nums, 5), 3);
  EXPECT_EQ(bs.FindGreater(nums, 7), 4);
  EXPECT_EQ(bs.FindGreater(nums, 9), 5);
  EXPECT_EQ(bs.FindGreater(nums, 11), -1);

  EXPECT_EQ(bs.FindSmallerEqual(nums, 0), 0);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 2), 1);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 4), 2);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 6), 3);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 8), 4);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 10), 5);
  EXPECT_EQ(bs.FindSmallerEqual(nums, -1), -1);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 1), 0);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 3), 1);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 5), 2);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 7), 3);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 9), 4);
  EXPECT_EQ(bs.FindSmallerEqual(nums, 11), 5);

  EXPECT_EQ(bs.FindSmaller(nums, 0), -1);
  EXPECT_EQ(bs.FindSmaller(nums, 2), 0);
  EXPECT_EQ(bs.FindSmaller(nums, 4), 1);
  EXPECT_EQ(bs.FindSmaller(nums, 6), 2);
  EXPECT_EQ(bs.FindSmaller(nums, 8), 3);
  EXPECT_EQ(bs.FindSmaller(nums, 10), 4);
  EXPECT_EQ(bs.FindSmaller(nums, -1), -1);
  EXPECT_EQ(bs.FindSmaller(nums, 1), 0);
  EXPECT_EQ(bs.FindSmaller(nums, 3), 1);
  EXPECT_EQ(bs.FindSmaller(nums, 5), 2);
  EXPECT_EQ(bs.FindSmaller(nums, 7), 3);
  EXPECT_EQ(bs.FindSmaller(nums, 9), 4);
  EXPECT_EQ(bs.FindSmaller(nums, 11), 5);


  std::vector<int> nums2{1, 2, 3, 3, 4, 5};
  EXPECT_EQ(bs.FindGreater(nums2, 3), 4);
  EXPECT_EQ(bs.FindGreaterEqual(nums2, 3), 2);
  EXPECT_EQ(bs.FindExact(nums2, 3), 2);
  EXPECT_EQ(bs.FindSmallerEqual(nums2, 3), 3);
  EXPECT_EQ(bs.FindSmaller(nums2, 3), 1);
}
