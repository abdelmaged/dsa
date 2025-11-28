#include "segment_tree.h"

SegmentTree::SegmentTree(const std::vector<int> &in_nums,
                         std::function<int(int, int)> oper)
    : n((int)in_nums.size()), nums(in_nums), operation(oper) {
  // 4n approximation for:
  // leaf nodes = n
  // internal nodes = n - 1
  // total nodes = 2n - 1
  // Min.Height Formula: h = log2(n + 1) - 1
  // Replace n with 2n - 1
  // then min.h = log2(2n) - 1 
  //            = log2(n) + log2(2) - 1 
  //            = log2(n) + 1 - 1 
  //            = log2(n) 
  //            = ceil(log2(n))
  // Max.Nodes Formula: 2^(h + 1) - 1
  // Replace h with ceil(log2(n))
  // then max.n = 2^(ceil(log2(n)) + 1) - 1 
  //            = 2^(log2(n) + 2) - 1 
  //            = 2^(2) * 2^(log2(n)) - 1 
  //            = 4 * n - 1
  stree.assign(4 * n, 0);
  build(0, 0, n - 1);
  // TODO efficient build using two for loops instead of recursion
}

void SegmentTree::Update(int idx, int val) { update(0, 0, n - 1, idx, val); }

void SegmentTree::UpdateRange(int left, int right, int val) {
  updateRange(0, 0, n - 1, left, right, val);
}

int SegmentTree::RangeQuery(int left, int right) {
  return range(0, 0, n - 1, left, right);
}

int SegmentTree::FindKth(int k) const {
  return findKth(0, 0, n - 1, k);
}

void SegmentTree::build(int parent, int left, int right) {
  if (left == right) {
    stree[parent] = nums[left];
    return;
  }

  int mid = midRange(left, right);
  int l_child = leftChild(parent);
  int r_child = rightChild(parent);
  build(l_child, left, mid);
  build(r_child, mid + 1, right);
  stree[parent] = operation(stree[l_child], stree[r_child]);
}

int SegmentTree::range(int parent, int t_left, int t_right, int u_left,
                       int u_right) {
  // Is Tree Node fully inside User Range ?
  if (overlapTotal(t_left, t_right, u_left, u_right)) {
    return stree[parent];
  }

  int t_mid = midRange(t_left, t_right);
  int l_child = leftChild(parent);
  int r_child = rightChild(parent);

  bool l_overlap = overlap(t_left, t_mid, u_left, u_right);
  bool r_overlap = overlap(t_mid + 1, t_right, u_left, u_right);

  if (l_overlap && r_overlap) {
    return operation(range(l_child, t_left, t_mid, u_left, u_right),
                     range(r_child, t_mid + 1, t_right, u_left, u_right));
  }

  if (l_overlap) {
    return range(l_child, t_left, t_mid, u_left, u_right);
  }

  // r_intersect
  return range(r_child, t_mid + 1, t_right, u_left, u_right);
}

void SegmentTree::update(int parent, int t_left, int t_right, int u_idx,
                         int u_val) {
  if (t_left == t_right) {
    stree[parent] = u_val;
    return;
  }

  int t_mid = midRange(t_left, t_right);
  int l_child = leftChild(parent);
  int r_child = rightChild(parent);
  if (t_mid < u_idx) {
    update(r_child, t_mid + 1, t_right, u_idx, u_val);
  } else {
    update(l_child, t_left, t_mid, u_idx, u_val);
  }
  stree[parent] = operation(stree[l_child], stree[r_child]);
}

void SegmentTree::updateRange(int parent, int t_left, int t_right, int u_left,
                              int u_right, int u_val) {
  if (!overlap(t_left, t_right, u_left, u_right)) {
    return;
  }

  if (t_left == t_right) {
    stree[parent] = u_val;
    return;
  }

  int t_mid = midRange(t_left, t_right);
  int l_child = leftChild(parent);
  int r_child = rightChild(parent);

  updateRange(l_child, t_left, t_mid, u_left, u_right, u_val);
  updateRange(r_child, t_mid + 1, t_right, u_left, u_right, u_val);

  stree[parent] = operation(stree[l_child], stree[r_child]);
}

int SegmentTree::findKth(int parent, int t_left, int t_right, int k) const {
  if (t_left == t_right) {
    return t_left;
  }

  int t_mid = midRange(t_left, t_right);
  int l_child = leftChild(parent);
  if (k <= stree[l_child]) {
    return findKth(l_child, t_left, t_mid, k);
  }

  int r_child = rightChild(parent);
  return findKth(r_child, t_mid + 1, t_right, k - stree[l_child]);
}

int SegmentTree::midRange(int left, int right) const {
  return left + (right - left) / 2;
}

int SegmentTree::leftChild(int parent) const { return parent * 2 + 1; }

int SegmentTree::rightChild(int parent) const { return parent * 2 + 2; }

bool SegmentTree::overlap(int l1, int r1, int l2, int r2) const {
  return !(r1 < l2 || l1 > r2);
}

bool SegmentTree::overlapTotal(int l_narrow, int r_narrow, int l_wide,
                               int r_wide) const {
  return l_wide <= l_narrow && r_narrow <= r_wide;
}

SegmentTreeLazy::SegmentTreeLazy(const std::vector<int> &in_nums,
                                 std::function<int(int, int)> oper)
    : SegmentTree(in_nums, oper) {
  is_lazy.assign(stree.size(), 0);
  lazy_val.assign(stree.size(), 0);
}

void SegmentTreeLazy::UpdateRange(int left, int right, int val) {
  updateRange(0, 0, n - 1, left, right, val);
}

int SegmentTreeLazy::RangeQuery(int left, int right) {
  return range(0, 0, n - 1, left, right);
}

void SegmentTreeLazy::propagate(int parent, int t_left, int t_right) {
  if (!is_lazy[parent]) {
    return;
  }
  is_lazy[parent] = 0;
  stree[parent] = lazy_val[parent];

  if (t_left == t_right) {
    return;
  }

  int l_child = leftChild(parent);
  int r_child = rightChild(parent);

  is_lazy[l_child] = 1;
  is_lazy[r_child] = 1;

  lazy_val[l_child] = lazy_val[parent];
  lazy_val[r_child] = lazy_val[parent];
}

void SegmentTreeLazy::updateRange(int parent, int t_left, int t_right,
                                  int u_left, int u_right, int u_val) {
  propagate(parent, t_left, t_right);
  if (!overlap(t_left, t_right, u_left, u_right)) {
    return;
  }

  if (overlapTotal(t_left, t_right, u_left, u_right)) {
    lazy_val[parent] = u_val;
    is_lazy[parent] = 1;
    propagate(parent, t_left, t_right);
    return;
  }

  int t_mid = midRange(t_left, t_right);
  int l_child = leftChild(parent);
  int r_child = rightChild(parent);
  updateRange(l_child, t_left, t_mid, u_left, u_right, u_val);
  updateRange(r_child, t_mid + 1, t_right, u_left, u_right, u_val);
  int l_val = is_lazy[l_child] ? lazy_val[l_child] : stree[l_child];
  int r_val = is_lazy[r_child] ? lazy_val[r_child] : stree[r_child];
  stree[parent] = operation(l_val, r_val);
}

int SegmentTreeLazy::range(int parent, int t_left, int t_right, int u_left,
                           int u_right) {
  propagate(parent, t_left, t_right);
  if (overlapTotal(t_left, t_right, u_left, u_right)) {
    return stree[parent];
  }

  int t_mid = midRange(t_left, t_right);
  int l_child = leftChild(parent);
  int r_child = rightChild(parent);

  bool l_overlap = overlap(t_left, t_mid, u_left, u_right);
  bool r_overlap = overlap(t_mid + 1, t_right, u_left, u_right);

  if (l_overlap && r_overlap) {
    return operation(range(l_child, t_left, t_mid, u_left, u_right),
                     range(r_child, t_mid + 1, t_right, u_left, u_right));
  }

  if (l_overlap) {
    return range(l_child, t_left, t_mid, u_left, u_right);
  }

  // r_overlap
  return range(r_child, t_mid + 1, t_right, u_left, u_right);
}
