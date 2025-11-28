#pragma once

// Header for SegmentTree (non-lazy and lazy variants)

#include <cstddef>
#include <functional>
#include <vector>

class SegmentTree {
public:
  SegmentTree(const std::vector<int> &in_nums,
              std::function<int(int, int)> oper);
  void Update(int idx, int val);
  void UpdateRange(int left, int right, int val);
  int RangeQuery(int left, int right);
  int FindKth(int k) const;

protected:
  int n{0};
  std::vector<int> nums;
  std::vector<int> stree;
  std::function<int(int, int)> operation;

  void build(int parent, int left, int right);
  int range(int parent, int t_left, int t_right, int u_left, int u_right);
  void update(int parent, int t_left, int t_right, int u_idx, int u_val);
  void updateRange(int parent, int t_left, int t_right, int u_left, int u_right,
                   int u_val);
  int findKth(int parent, int t_left, int t_right, int k) const;
  int midRange(int left, int right) const;
  int leftChild(int parent) const;
  int rightChild(int parent) const;
  bool overlap(int l1, int r1, int l2, int r2) const;
  bool overlapTotal(int l_narrow, int r_narrow, int l_wide, int r_wide) const;
};

class SegmentTreeLazy : public SegmentTree {
public:
  SegmentTreeLazy(const std::vector<int> &in_nums,
                  std::function<int(int, int)> oper);
  void UpdateRange(int left, int right, int val);
  int RangeQuery(int left, int right);

protected:
  std::vector<int> is_lazy;
  std::vector<int> lazy_val;

  void propagate(int parent, int t_left, int t_right);
  void updateRange(int parent, int t_left, int t_right, int u_left, int u_right,
                   int u_val);
  int range(int parent, int t_left, int t_right, int u_left, int u_right);
};
