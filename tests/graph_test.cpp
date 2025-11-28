#include <gtest/gtest.h>
#include <vector>

#include "graph.h"

TEST(GraphTest, TopologicalSort) {
  Graph g(8);

  g.DirectedEdge(0, 1, 1);
  g.DirectedEdge(0, 2, 1);
  g.DirectedEdge(1, 2, 1);
  g.DirectedEdge(2, 3, 1);
  g.DirectedEdge(2, 5, 1);
  g.DirectedEdge(3, 4, 1);
  g.DirectedEdge(7, 6, 1);

  std::vector<int> topo;
  g.TopologicalSortDFS(topo);
  EXPECT_EQ(topo, std::vector<int>({7, 6, 0, 1, 2, 5, 3, 4}));

  std::vector<int> topo2;
  g.TopologicalSortKahn(topo2);
  EXPECT_EQ(topo, std::vector<int>({7, 6, 0, 1, 2, 5, 3, 4}));
}

TEST(GraphTest, ArticulationPoints) {
  Graph g(6);

  g.UndirectedEdge(0, 1, 1);
  g.UndirectedEdge(1, 2, 1);
  g.UndirectedEdge(3, 4, 1);
  g.UndirectedEdge(4, 5, 1);
  g.UndirectedEdge(1, 4, 1);

  std::vector<int> ap;
  g.ArticulationPoints(ap);
  EXPECT_EQ(ap, std::vector<int>({1, 4}));

  Graph g2(6);
  g2.UndirectedEdge(1, 0, 1);
  g2.UndirectedEdge(1, 2, 1);
  g2.UndirectedEdge(1, 5, 1);
  g2.UndirectedEdge(1, 4, 1);
  g2.UndirectedEdge(1, 3, 1);
  g2.UndirectedEdge(4, 5, 1);

  std::vector<int> ap2;
  g2.ArticulationPoints(ap2);
  EXPECT_EQ(ap2, std::vector<int>({1}));
}

TEST(GraphTest, SingleSourceShortestPathDijkstra) {
  Graph g(5);

  g.DirectedEdge(0, 1, 2);
  g.DirectedEdge(0, 2, 6);
  g.DirectedEdge(1, 3, 3);
  g.DirectedEdge(1, 4, 6);
  g.DirectedEdge(2, 4, 1);
  g.DirectedEdge(3, 4, 5);

  std::vector<int> dist;
  std::vector<int> path;
  g.SingleSourceShortestPathDijkstra(0, dist, path);
  EXPECT_EQ(dist, std::vector<int>({0, 2, 6, 5, 7}));
  EXPECT_EQ(path, std::vector<int>({0, 0, 0, 1, 2}));
}

TEST(GraphTest, SingleSourceShortestPathBellmanFord) {
  Graph g(7);

  g.DirectedEdge(0, 1, 6);
  g.DirectedEdge(0, 2, 5);
  g.DirectedEdge(0, 3, 5);
  g.DirectedEdge(1, 4, -1);
  g.DirectedEdge(2, 1, -2);
  g.DirectedEdge(3, 2, -2);
  g.DirectedEdge(3, 5, -1);
  g.DirectedEdge(4, 6, 3);
  g.DirectedEdge(5, 6, 3);

  std::vector<int> dist;
  std::vector<int> path;
  g.SingleSourceShortestPathBellmanFord(0, dist, path);
  EXPECT_EQ(dist, std::vector<int>({0, 1, 3, 5, 0, 4, 3}));
  EXPECT_EQ(path, std::vector<int>({0, 2, 3, 0, 1, 3, 4}));

  Graph g2(4);

  g2.DirectedEdge(0, 1, 4);
  g2.DirectedEdge(0, 3, 5);
  g2.DirectedEdge(2, 1, -10);
  g2.DirectedEdge(3, 2, 3);

  g2.SingleSourceShortestPathBellmanFord(0, dist, path);
  EXPECT_EQ(dist, std::vector<int>({0, -2, 8, 5}));
  EXPECT_EQ(path, std::vector<int>({0, 2, 3, 0}));
}

TEST(GraphTest, AllPairsShortestPathFloydWarshal) {
  Graph g(4);

  g.DirectedEdge(0, 1, 3);
  g.DirectedEdge(0, 3, 7);
  g.DirectedEdge(1, 0, 8);
  g.DirectedEdge(1, 2, 2);
  g.DirectedEdge(2, 0, 5);
  g.DirectedEdge(2, 3, 1);
  g.DirectedEdge(3, 0, 2);

  std::vector<std::vector<int>> dist;
  std::vector<std::vector<int>> path;
  g.AllPairsShortestPathFloydWarshal(dist, path);
  EXPECT_EQ(dist, std::vector<std::vector<int>>({
                      {0, 3, 5, 6}, // Source 0
                      {5, 0, 2, 3}, // Source 1
                      {3, 6, 0, 1}, // Source 2
                      {2, 5, 7, 0}, // Source 3
                  }));
  EXPECT_EQ(path, std::vector<std::vector<int>>({
                      {0, 0, 1, 2}, // Source 0
                      {3, 1, 1, 2}, // Source 1
                      {3, 0, 2, 2}, // Source 2
                      {3, 0, 1, 3}, // Source 3
                  }));
}

TEST(GraphTest, MST) {
  Graph g(5);

  g.UndirectedEdge(0, 1, 4);
  g.UndirectedEdge(0, 4, 6);
  g.UndirectedEdge(0, 2, 4);
  g.UndirectedEdge(0, 3, 6);
  g.UndirectedEdge(1, 2, 2);
  g.UndirectedEdge(2, 3, 8);
  g.UndirectedEdge(3, 4, 9);

  std::vector<Edge> edges;
  EXPECT_EQ(g.MSTPrim(edges), 18);
  EXPECT_EQ(edges,
            std::vector<Edge>({{0, 1, 4}, {1, 2, 2}, {0, 4, 6}, {0, 3, 6}}));

  EXPECT_EQ(g.MSTKruskal(edges), 18);
  EXPECT_EQ(edges,
            std::vector<Edge>({{1, 2, 2}, {0, 1, 4}, {0, 4, 6}, {0, 3, 6}}));
}

TEST(GraphTest, SingleSourceSingleTarget) {
  Graph g(15);

  g.UndirectedEdge(0, 4, 1);
  g.UndirectedEdge(1, 4, 1);
  g.UndirectedEdge(2, 5, 1);
  g.UndirectedEdge(3, 5, 1);
  g.UndirectedEdge(4, 6, 1);
  g.UndirectedEdge(5, 6, 1);
  g.UndirectedEdge(6, 7, 1);
  g.UndirectedEdge(7, 8, 1);
  g.UndirectedEdge(8, 9, 1);
  g.UndirectedEdge(8, 10, 1);
  g.UndirectedEdge(9, 11, 1);
  g.UndirectedEdge(9, 12, 1);
  g.UndirectedEdge(10, 13, 1);
  g.UndirectedEdge(10, 14, 1);

  int dist = -1;
  std::vector<int> path;
  g.SingleSourceSingleTargetShortestPathBidirectionalBFS(0, 14, dist, path);
  EXPECT_EQ(dist, 6);
  EXPECT_EQ(path, std::vector<int>({0, 4, 6, 7, 8, 10, 14}));
}

TEST(GraphTest, StronglyConnectedComponents) {
  Graph g(8);

  g.DirectedEdge(0, 1, 1);
  g.DirectedEdge(1, 3, 1);
  g.DirectedEdge(2, 1, 1);
  g.DirectedEdge(3, 2, 1);
  g.DirectedEdge(3, 4, 1);
  g.DirectedEdge(4, 5, 1);
  g.DirectedEdge(5, 7, 1);
  g.DirectedEdge(7, 6, 1);
  g.DirectedEdge(6, 4, 1);

  std::vector<std::vector<int>> scc;
  g.StronglyConnectedComponentsKosaraju(scc);
  EXPECT_EQ(scc, std::vector<std::vector<int>>({
                     {0},          // SCC #1
                     {3, 2, 1},    // SCC #2
                     {5, 7, 6, 4}, // SCC #3
                 }));

  g.StronglyConnectedComponentsTarjan(scc);
  EXPECT_EQ(scc, std::vector<std::vector<int>>({
                     {6, 7, 5, 4}, // SCC #1
                     {2, 3, 1},    // SCC #2
                     {0},          // SCC #3
                 }));
}

TEST(GraphTest, MaxFlow) {
  Graph g(4);

  g.DirectedEdge(0, 1, 8);
  g.DirectedEdge(0, 2, 8);
  g.DirectedEdge(1, 3, 8);
  g.DirectedEdge(2, 3, 8);
  g.DirectedEdge(1, 2, 1);
  EXPECT_EQ(g.MaxFlowFordFulkerson(0, 3), 16);
  EXPECT_EQ(g.MaxFlowFordDinic(0, 3), 16);

  Graph g2(7);

  g2.DirectedEdge(0, 1, 3);
  g2.DirectedEdge(0, 3, 3);
  g2.DirectedEdge(1, 2, 4);
  g2.DirectedEdge(2, 0, 3);
  g2.DirectedEdge(2, 3, 1);
  g2.DirectedEdge(2, 4, 2);
  g2.DirectedEdge(3, 4, 2);
  g2.DirectedEdge(3, 5, 6);
  g2.DirectedEdge(4, 1, 1);
  g2.DirectedEdge(4, 6, 1);
  g2.DirectedEdge(5, 6, 9);
  EXPECT_EQ(g2.MaxFlowFordFulkerson(0, 6), 5);
  EXPECT_EQ(g2.MaxFlowFordDinic(0, 6), 5);
}