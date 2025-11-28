#include <gtest/gtest.h>

#include "quick_sort.h"
#include "merge_sort.h"
#include "count_sort.h"
#include "insertion_sort.h"
#include "selection_sort.h"
#include "bubble_sort.h"

class SortTest : public testing::Test {
protected:
  std::vector<std::vector<int>> _tests = {
      {3, 1, 2, 1, 3},
      {10, 20, 15, 5, 25},
      {5, 2, 9, 3, 7},
      {10, 1, 2, 20, 5, 3, 4},
      {7, 3, 5, 1, 9, 2, 4},
      {10, 5, 20, 30, 15, 100, 90, 8},
      {8, 7, 1, 2, 6, 9, 10, 2, 11},
      {5, 5, 5, 5, 5, 5, 5, 5, 5},
      {10, 5, 8, 3, 7, 9, 4, 1, 6, 2, 11},
  };

  std::vector<std::vector<int>> _refs = {
      {1, 1, 2, 3, 3},
      {5, 10, 15, 20, 25},
      {2, 3, 5, 7, 9},
      {1, 2, 3, 4, 5, 10, 20},
      {1, 2, 3, 4, 5, 7, 9},
      {5, 8, 10, 15, 20, 30, 90, 100},
      {1, 2, 2, 6, 7, 8, 9, 10, 11},
      {5, 5, 5, 5, 5, 5, 5, 5, 5},
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
  };
};

TEST_F(SortTest, QuickSort) {
  std::vector<QuickSort::PivotStrategy> strategies = {
      QuickSort::PivotStrategy::kLow, QuickSort::PivotStrategy::kHigh,
      QuickSort::PivotStrategy::kMid};

  for (auto &strategy : strategies) {
    QuickSort qs(strategy);

    auto tests = _tests;
    for (size_t i = 0; i < tests.size(); ++i) {
      qs.Sort(tests[i]);
      EXPECT_EQ(tests[i], _refs[i]) << "Strategy: " << (int)strategy;
    }
  }
}

TEST_F(SortTest, MergeSort) {
  MergeSort ms;

  auto tests = _tests;
  for (size_t i = 0; i < tests.size(); ++i) {
    ms.Sort(tests[i]);
    EXPECT_EQ(tests[i], _refs[i]) << "Recursive";
  }

  tests = _tests;
  for (size_t i = 0; i < tests.size(); ++i) {
    ms.SortIterative(tests[i]);
    EXPECT_EQ(tests[i], _refs[i]) << "Iterative";
  }
}

TEST_F(SortTest, CountSort) {
  CountSort cs;

  auto tests = _tests;
  for (size_t i = 0; i < tests.size(); ++i) {
    cs.Sort(tests[i]);
    EXPECT_EQ(tests[i], _refs[i]);
  }

  tests = _tests;
  for (size_t i = 0; i < tests.size(); ++i) {
    cs.SortBasic(tests[i]);
    EXPECT_EQ(tests[i], _refs[i]);
  }
}

TEST_F(SortTest, InsertionSort) {
  InsertionSort is;

  auto tests = _tests;
  for (size_t i = 0; i < tests.size(); ++i) {
    is.Sort(tests[i]);
    EXPECT_EQ(tests[i], _refs[i]);
  }
}

TEST_F(SortTest, SelectionSort) {
  SelectionSort ss;

  auto tests = _tests;
  for (size_t i = 0; i < tests.size(); ++i) {
    ss.Sort(tests[i]);
    EXPECT_EQ(tests[i], _refs[i]);
  }
}

TEST_F(SortTest, BubbleSort) {
  BubbleSort bs;

  auto tests = _tests;
  for (size_t i = 0; i < tests.size(); ++i) {
    bs.Sort(tests[i]);
    EXPECT_EQ(tests[i], _refs[i]);
  }
}