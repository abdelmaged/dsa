#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "avl.h"
#include "hash_table_closed.h"
#include "hash_table_open.h"
#include "heap.h"
#include "linked_list.h"
#include "matrix.h"
#include "segment_tree.h"
#include "union_find.h"

TEST(DataStructureTest, LinkedList) {
  LinkedList<int> ll;

  ll.PushBack(10);
  ll.PushBack(20);
  ll.PushBack(30);
  ll.PushBack(40);

  EXPECT_STREQ(ll.ToString().c_str(), "10, 20, 30, 40");

  ll.Delete(ll.Search(20));
  EXPECT_STREQ(ll.ToString().c_str(), "10, 30, 40");

  ll.Delete(ll.Search(10));
  EXPECT_STREQ(ll.ToString().c_str(), "30, 40");

  ll.Delete(ll.Search(40));
  EXPECT_STREQ(ll.ToString().c_str(), "30");

  ll.Delete(ll.Search(30));
  EXPECT_STREQ(ll.ToString().c_str(), "");
}

TEST(DataStructureTest, HashTableOpen) {
  HashTableOpen<int, int> hto(10, [](const int &key) -> size_t { return key; });

  hto.Insert(10, 100);
  hto.Insert(20, 200);
  hto.Insert(31, 3100);
  hto.Insert(32, 3200);

  EXPECT_STREQ(hto.ToString().c_str(),
               "{{10, 100}, {20, 200}} " // #0
               "{{31, 3100}} "           // #1
               "{{32, 3200}} "           // #2
               "{} "                     // #3
               "{} "                     // #4
               "{} "                     // #5
               "{} "                     // #6
               "{} "                     // #7
               "{} "                     // #8
               "{} "                     // #9
  );

  hto.Delete(20);
  EXPECT_STREQ(hto.ToString().c_str(),
               "{{10, 100}} "  // #0
               "{{31, 3100}} " // #1
               "{{32, 3200}} " // #2
               "{} "           // #3
               "{} "           // #4
               "{} "           // #5
               "{} "           // #6
               "{} "           // #7
               "{} "           // #8
               "{} "           // #9
  );

  hto.Delete(32);
  EXPECT_STREQ(hto.ToString().c_str(),
               "{{10, 100}} "  // #0
               "{{31, 3100}} " // #1
               "{} "           // #2
               "{} "           // #3
               "{} "           // #4
               "{} "           // #5
               "{} "           // #6
               "{} "           // #7
               "{} "           // #8
               "{} "           // #9
  );

  EXPECT_EQ(*hto.Search(31), 3100);
  EXPECT_EQ(hto.Search(32), nullptr);
}

TEST(DataStructureTest, HashTableClosed) {
  HashTableClosed<int, int> htc(10,
                                [](const int &key) -> size_t { return key; });

  htc.Insert(10, 100);
  htc.Insert(20, 200);
  htc.Insert(31, 3100);
  htc.Insert(32, 3200);

  EXPECT_STREQ(htc.ToString().c_str(),
               "{10, 100} "  // #0
               "{20, 200} "  // #1
               "{31, 3100} " // #2
               "{32, 3200} " // #3
               "{E} "        // #4
               "{E} "        // #5
               "{E} "        // #6
               "{E} "        // #7
               "{E} "        // #8
               "{E} "        // #9
  );

  htc.Delete(20);
  EXPECT_STREQ(htc.ToString().c_str(),
               "{10, 100} "  // #0
               "{D} "        // #1
               "{31, 3100} " // #2
               "{32, 3200} " // #3
               "{E} "        // #4
               "{E} "        // #5
               "{E} "        // #6
               "{E} "        // #7
               "{E} "        // #8
               "{E} "        // #9
  );

  htc.Delete(32);
  EXPECT_STREQ(htc.ToString().c_str(),
               "{10, 100} "  // #0
               "{D} "        // #1
               "{31, 3100} " // #2
               "{D} "        // #3
               "{E} "        // #4
               "{E} "        // #5
               "{E} "        // #6
               "{E} "        // #7
               "{E} "        // #8
               "{E} "        // #9
  );

  EXPECT_EQ(*htc.Search(31), 3100);
  EXPECT_EQ(htc.Search(32), nullptr);

  htc.Insert(131, 13100);
  EXPECT_STREQ(htc.ToString().c_str(),
               "{10, 100} "    // #0
               "{131, 13100} " // #1
               "{31, 3100} "   // #2
               "{D} "          // #3
               "{E} "          // #4
               "{E} "          // #5
               "{E} "          // #6
               "{E} "          // #7
               "{E} "          // #8
               "{E} "          // #9
  );
}

TEST(DataStructureTest, UnionFind) {
  UnionFind uf(6);

  EXPECT_STREQ(uf.ToString().c_str(),
               "(0, 0, 0) (1, 1, 0) (2, 2, 0) (3, 3, 0) (4, 4, 0) (5, 5, 0) ");

  uf.UnionSet(1, 2);
  uf.UnionSet(3, 4);
  uf.UnionSet(4, 5);
  uf.UnionSet(2, 4);
  EXPECT_STREQ(uf.ToString().c_str(),
               "(0, 0, 0) (1, 2, 0) (2, 4, 1) (3, 4, 0) (4, 4, 2) (5, 4, 0) ");
}

TEST(DataStructureTest, DiagnoalMatrix) {
  DiagnoalMatrix dmx(5);

  for (int i = 0; i < 10; ++i) {
    dmx.Set(i, i, i + 2);
  }
  dmx.Set(2, 4, 100);
  dmx.Set(5, 3, 100);

  EXPECT_EQ(dmx.Get(3, 3), 5);
  EXPECT_EQ(dmx.Get(2, 4), 0);
  EXPECT_EQ(dmx.Get(5, 3), 0);
  EXPECT_EQ(dmx.Get(6, 6), 0);
  EXPECT_EQ(dmx.Get(4, 4), 6);
}

TEST(DataStructureTest, LowerTriangularMatrix) {
  LowerTriangularMatrix ltmx(5);

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j <= 10; ++j) {
      ltmx.Set(i, j, i + 2 + j * 10);
    }
  }

  EXPECT_EQ(ltmx.Get(0, 0), 2);
  EXPECT_EQ(ltmx.Get(0, 1), 0);
  EXPECT_EQ(ltmx.Get(1, 0), 3);
  EXPECT_EQ(ltmx.Get(1, 1), 13);
  EXPECT_EQ(ltmx.Get(1, 2), 0);
  EXPECT_EQ(ltmx.Get(2, 0), 4);
  EXPECT_EQ(ltmx.Get(2, 1), 14);
  EXPECT_EQ(ltmx.Get(2, 2), 24);
  EXPECT_EQ(ltmx.Get(2, 3), 0);
  EXPECT_EQ(ltmx.Get(3, 0), 5);
  EXPECT_EQ(ltmx.Get(3, 1), 15);
  EXPECT_EQ(ltmx.Get(3, 2), 25);
  EXPECT_EQ(ltmx.Get(3, 3), 35);
  EXPECT_EQ(ltmx.Get(4, 4), 46);
  EXPECT_EQ(ltmx.Get(6, 7), 0);
}

TEST(DataStructureTest, UpperTriangularMatrix) {
  UpperTriangularMatrix utmx(5);

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j <= 10; ++j) {
      utmx.Set(i, j, i + 2 + j * 10);
    }
  }

  EXPECT_EQ(utmx.Get(0, 0), 2);
  EXPECT_EQ(utmx.Get(0, 1), 12);
  EXPECT_EQ(utmx.Get(0, 2), 22);
  EXPECT_EQ(utmx.Get(0, 3), 32);
  EXPECT_EQ(utmx.Get(0, 4), 42);
  EXPECT_EQ(utmx.Get(0, 5), 0);
  EXPECT_EQ(utmx.Get(1, 0), 0);
  EXPECT_EQ(utmx.Get(1, 1), 13);
  EXPECT_EQ(utmx.Get(1, 2), 23);
  EXPECT_EQ(utmx.Get(1, 3), 33);
  EXPECT_EQ(utmx.Get(2, 3), 34);
  EXPECT_EQ(utmx.Get(2, 3), 34);
  EXPECT_EQ(utmx.Get(4, 4), 46);
}

TEST(DataStructureTest, SymmetricMatrix) {
  SymmetricMatrix smx(5);

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j <= 10; ++j) {
      smx.Set(i, j, i + 2 + j * 10);
    }
  }

  EXPECT_EQ(smx.Get(0, 0), 2);
  EXPECT_EQ(smx.Get(1, 0), 3);
  EXPECT_EQ(smx.Get(0, 1), 3);
  EXPECT_EQ(smx.Get(1, 1), 13);
  EXPECT_EQ(smx.Get(1, 2), 14);
  EXPECT_EQ(smx.Get(2, 1), 14);
  EXPECT_EQ(smx.Get(4, 4), 46);
  EXPECT_EQ(smx.Get(8, 7), 0);
}

TEST(DataStructureTest, ToeplitzMatrix) {
  ToeplitzMatrix tmx(5);

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j <= 10; ++j) {
      tmx.Set(i, j, i + 2 + j * 10);
    }
  }

  EXPECT_EQ(tmx.Get(0, 0), 46);
  EXPECT_EQ(tmx.Get(2, 2), 46);
  EXPECT_EQ(tmx.Get(0, 1), 45);
  EXPECT_EQ(tmx.Get(3, 4), 45);
  EXPECT_EQ(tmx.Get(4, 0), 6);
  EXPECT_EQ(tmx.Get(4, 3), 36);
  EXPECT_EQ(tmx.Get(1, 0), 36);
  EXPECT_EQ(tmx.Get(2, 0), 26);
}

TEST(DataStructureTest, HankelMatrix) {
  HankelMatrix hmx(5);

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j <= 10; ++j) {
      hmx.Set(i, j, i + 2 + j * 10);
    }
  }

  EXPECT_EQ(hmx.Get(0, 0), 2);
  EXPECT_EQ(hmx.Get(4, 4), 46);
  EXPECT_EQ(hmx.Get(0, 1), 3);
  EXPECT_EQ(hmx.Get(1, 0), 3);
  EXPECT_EQ(hmx.Get(4, 3), 36);
  EXPECT_EQ(hmx.Get(3, 4), 36);
}

TEST(DataStructureTest, MatrixTraversal) {
  MatrixTraversal mtrav;

  using VectorVectorInt = std::vector<std::vector<int>>;

  EXPECT_EQ(mtrav.DiagonalRising({
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
            }),
            (VectorVectorInt{
                {7},
                {8, 4},
                {9, 5, 1},
                {6, 2},
                {3},
            }));

  EXPECT_EQ(mtrav.DiagonalFalling({
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
            }),
            (VectorVectorInt{
                {7},
                {4, 8},
                {1, 5, 9},
                {2, 6},
                {3},
            }));

  EXPECT_EQ(mtrav.AntiDiagonalRising({
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
            }),
            (VectorVectorInt{
                {1},
                {4, 2},
                {7, 5, 3},
                {8, 6},
                {9},
            }));

  EXPECT_EQ(mtrav.AntiDiagonalFalling({
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
            }),
            (VectorVectorInt{
                {1},
                {2, 4},
                {3, 5, 7},
                {6, 8},
                {9},
            }));
}

TEST(DataStructureTest, AVL) {
  AVLTree<int> tree(10);

  for (int i = 0; i < 10; i++) {
    tree.Insert(i);
  }

  EXPECT_EQ(tree.Search(11), false);
  EXPECT_EQ(tree.Search(9), true);

  EXPECT_STREQ(tree.ToString().c_str(),
               "(3) "                       // L0
               "(1, 7) "                    // L1
               "(0, 2, 5, 9) "              // L2
               "(N, N, N, N, 4, 6, 8, 10) " // L4
               "(N, N, N, N, N, N, N, N) "  // L5
  );

  tree.Delete(5);
  EXPECT_STREQ(tree.ToString().c_str(),
               "(3) "                       // L0
               "(1, 7) "                    // L1
               "(0, 2, 4, 9) "              // L2
               "(N, N, N, N, N, 6, 8, 10) " // L3
               "(N, N, N, N, N, N) "        // L4
  );

  tree.Delete(3);
  EXPECT_STREQ(tree.ToString().c_str(),
               "(2) "                 // L0
               "(1, 7) "              // L1
               "(0, N, 4, 9) "        // L2
               "(N, N, N, 6, 8, 10) " // L3
               "(N, N, N, N, N, N) "  // L4
  );

  tree.Delete(10);
  EXPECT_STREQ(tree.ToString().c_str(),
               "(2) "                // L0
               "(1, 7) "             // L1
               "(0, N, 4, 9) "       // L2
               "(N, N, N, 6, 8, N) " // L3
               "(N, N, N, N) "       // L4
  );

  tree.Delete(8);
  EXPECT_STREQ(tree.ToString().c_str(),
               "(2) "                // L0
               "(1, 7) "             // L1
               "(0, N, 4, 9) "       // L2
               "(N, N, N, 6, N, N) " // L3
               "(N, N) "             // L4
  );

  tree.Delete(9);
  EXPECT_STREQ(tree.ToString().c_str(),
               "(2) "                // L0
               "(1, 6) "             // L1
               "(0, N, 4, 7) "       // L2
               "(N, N, N, N, N, N) " // L3
  );

  EXPECT_EQ(tree.Search(4), true);
  EXPECT_EQ(tree.Search(9), false);
}

TEST(DataStructureTest, Heap) {
  Heap<int> h;

  EXPECT_THROW(h.Top(), std::out_of_range);

  for (int i = 10; i >= 0; --i) {
    h.Insert(i);
  }

  EXPECT_EQ(h.Size(), 11);
  EXPECT_STREQ(h.ToString().c_str(), "(0) "                       // L0
                                     "(1, 5) "                    // L1
                                     "(4, 2, 9, 6) "              // L2
                                     "(10, 7, 8, 3, N, N, N, N) " // L3
                                     "(N, N, N, N, N, N, N, N) "  // L4
  );
  EXPECT_EQ(h.Top(), 0);
  h.Pop();
  EXPECT_EQ(h.Top(), 1);
  h.Pop();
  EXPECT_EQ(h.Top(), 2);
  EXPECT_EQ(h.Size(), 9);

  // Heap<int> h2;
  // h2.Insert(1);
  // EXPECT_EQ(h2.Array(), std::vector<int>({1}));
  // h2.Insert(6);
  // EXPECT_EQ(h2.Array(), std::vector<int>({1, 6}));
  // h2.Insert(2);
  // EXPECT_EQ(h2.Array(), std::vector<int>({1, 2, 6}));
}

TEST(DataStructureTest, SegmentTree) {
  auto query = [](SegmentTree *stree, std::vector<int> &data) {
    int sum = 0;
    for (int i = 0; i < data.size(); ++i) {
      for (int j = i; j < data.size(); ++j) {
        sum += data[j];
        EXPECT_EQ(stree->RangeQuery(i, j), sum)
            << "  Range: " << i << ", " << j;
      }
      sum = 0;
    }
  };

  auto do_test = [&query](SegmentTree *stree, std::vector<int> &data) {
    query(stree, data);
    for (int i = 0; i < data.size(); ++i) {
      stree->Update(i, data[i] * 10);
      data[i] *= 10;
      query(stree, data);
    }

    stree->UpdateRange(1, 3, 100);
    data[1] = 100;
    data[2] = 100;
    data[3] = 100;
    query(stree, data);

    stree->UpdateRange(0, 0, 200);
    data[0] = 200;
    query(stree, data);
  };

  auto sum_fn = [](int x, int y) { return x + y; };

  std::vector<int> data({1, 2, 3, 4, 5});
  SegmentTree stree(data, sum_fn);
  do_test(&stree, data);

  std::vector<int> data2({1, 2, 3, 4, 5, 6});
  SegmentTree stree2(data2, sum_fn);
  do_test(&stree2, data2);

  std::vector<int> data3({1, 2, 3, 4, 5, 6, 7});
  SegmentTree stree3(data3, sum_fn);
  do_test(&stree3, data3);

  std::vector<int> data4({1, 2, 3, 4, 5, 6, 7, 8});
  SegmentTree stree4(data4, sum_fn);
  do_test(&stree4, data4);

  std::vector<int> data_lazy({1, 2, 3, 4, 5});
  SegmentTreeLazy stree_lazy(data_lazy, sum_fn);
  do_test(&stree_lazy, data_lazy);

  std::vector<int> data_cnt(10, 1);
  SegmentTree stree_cnt(data_cnt, sum_fn);
  EXPECT_EQ(stree_cnt.FindKth(1), 0);
  EXPECT_EQ(stree_cnt.FindKth(8), 7);
  stree_cnt.Update(0, 0);
  EXPECT_EQ(stree_cnt.FindKth(1), 1);
  EXPECT_EQ(stree_cnt.FindKth(8), 8);
}
