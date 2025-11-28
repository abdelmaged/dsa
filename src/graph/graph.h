#include <ostream>

struct Edge {
  int u, v, w;

  Edge(int src, int tgt, int w);
  bool operator<(const Edge &other) const;
  bool operator>(const Edge &other) const;
  bool operator==(const Edge &other) const;

  friend std::ostream &operator<<(std::ostream &os, const Edge &edge);
};

class Graph {
public:
  Graph(int vertices);

  void DirectedEdge(int from, int to, int weight);
  void UndirectedEdge(int from, int to, int weight);

  bool CycleCheckUndirected() const;
  bool CycleCheckDirected() const;

  void TopologicalSortDFS(std::vector<int> &topo_order);
  void TopologicalSortKahn(std::vector<int> &topo_order);

  void ArticulationPoints(std::vector<int> &points);

  void SingleSourceShortestPathBFS(int src, std::vector<int> &dist,
                                   std::vector<int> &path);
  void SingleSourceShortestPathDijkstra(int src, std::vector<int> &dist,
                                        std::vector<int> &path);
  void SingleSourceShortestPathBellmanFord(int src, std::vector<int> &dist,
                                           std::vector<int> &path);
  void SingleSourceSingleTargetShortestPathBidirectionalBFS(
      int src, int tgt, int &dist, std::vector<int> &path);

  void AllPairsShortestPathFloydWarshal(std::vector<std::vector<int>> &dist,
                                        std::vector<std::vector<int>> &path);

  int MSTPrim(std::vector<Edge> &edges);
  int MSTKruskal(std::vector<Edge> &edges);

  void StronglyConnectedComponentsKosaraju(std::vector<std::vector<int>> &scc);
  void StronglyConnectedComponentsTarjan(std::vector<std::vector<int>> &scc);

  int MaxFlowFordFulkerson(int src, int sink);
  int MaxFlowFordDinic(int src, int sink);

private:
  int _n_vertices;
  std::vector<std::vector<Edge>> _adj_list;
  std::vector<std::vector<std::pair<int, int>>> adj_;
  std::vector<Edge> _edge_list;
};
