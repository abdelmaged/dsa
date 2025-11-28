#include "graph.h"
#include "union_find.h"

#include <algorithm>
#include <fcntl.h>
#include <functional>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

#define INF 0x7fffffff

Edge::Edge(int src, int tgt, int w) : u(src), v(tgt), w(w) {}

bool Edge::operator<(const Edge &other) const { return w < other.w; }

bool Edge::operator>(const Edge &other) const { return w > other.w; }

bool Edge::operator==(const Edge &other) const {
  return u == other.u && v == other.v && w == other.w;
}

std::ostream &operator<<(std::ostream &os, const Edge &edge) {
  os << "{" << edge.u << ", " << edge.v << ", " << edge.w << "}";
  return os;
}

Graph::Graph(int vertices) : _n_vertices((vertices)) {
  _adj_list.resize(vertices);
  adj_.resize(vertices);
}

void Graph::DirectedEdge(int from, int to, int weight) {
  if (from < 0 || to < 0 || from >= _adj_list.size() ||
      to >= _adj_list.size()) {
    throw std::out_of_range("`from` vertix or `to` vertix out of range");
  }
  _adj_list[from].push_back(Edge(from, to, weight));
  adj_[from].emplace_back(to, weight);
}

bool Graph::CycleCheckUndirected() const {
  std::vector<int> vis(_n_vertices, 0);

  std::function<bool(int, int)> dfs = [&](int u, int parent) {
    vis[u] = true;

    for (const auto &[v, w] : adj_[u]) {
      if (vis[v] && v != parent) {
        return true;
      }
      if (dfs(v, u)) {
        return true;
      }
    }
    return false;
  };

  for (int u = 0; u < _n_vertices; ++u) {
    if (vis[u]) {
      continue;
    }
    if (dfs(u, -1)) {
      return true;
    }
  }
  return false;
}

bool Graph::CycleCheckDirected() const {
  // TODO
  return false;
}

void Graph::UndirectedEdge(int from, int to, int weight) {
  DirectedEdge(from, to, weight);
  DirectedEdge(to, from, weight);
  _edge_list.push_back(Edge(from, to, weight));
}

void Graph::TopologicalSortDFS(std::vector<int> &topo_order) {
  std::vector<bool> visited(_n_vertices, false);
  topo_order.clear();

  std::function<void(int u)> dfs;
  dfs = [&](int u) {
    visited[u] = true;
    for (auto &[v, w] : adj_[u]) {
      if (!visited[v]) {
        dfs(v);
      }
    }
    topo_order.push_back(u);
  };

  for (int u = 0; u < _n_vertices; ++u) {
    if (!visited[u]) {
      dfs(u);
    }
  }
  std::reverse(topo_order.begin(), topo_order.end());
}

void Graph::TopologicalSortKahn(std::vector<int> &topo_order) {
  std::vector<int> in_deg(_n_vertices, 0);
  std::queue<int> q;

  topo_order.clear();

  for (int u = 0; u < _n_vertices; ++u) {
    for (auto &edge : _adj_list[u]) {
      ++in_deg[edge.v];
    }
  }

  for (int u = 0; u < _n_vertices; ++u) {
    if (!in_deg[u]) {
      q.push(u);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo_order.push_back(u);
    for (auto &edge : _adj_list[u]) {
      --in_deg[edge.v];
      if (!in_deg[edge.v]) {
        q.push(edge.v);
      }
    }
  }
}

void Graph::ArticulationPoints(std::vector<int> &points) {
  int time_id = 0;
  std::vector<int> visit_time(_n_vertices, -1);
  std::vector<int> low_link(_n_vertices, -1);
  std::vector<int> parent(_n_vertices, -1);

  std::function<void(int)> dfs = [&](int u) {
    visit_time[u] = time_id;
    low_link[u] = time_id;
    ++time_id;
    bool is_ap = false;
    int child_cnt = 0;

    for (auto &edge : _adj_list[u]) {
      if (visit_time[edge.v] != -1) {
        if (edge.v != parent[u]) { // Is Back Edge (not bidirectional) ?
          low_link[u] = std::min(low_link[u], low_link[edge.v]);
        }
        continue;
      }

      ++child_cnt;
      parent[edge.v] = u;
      dfs(edge.v);
      low_link[u] = std::min(low_link[u], low_link[edge.v]);

      if (is_ap) {
        continue;
      }

      if ((parent[u] == -1 && child_cnt > 1) || // 1. Root Case
          (parent[u] != -1 &&
           visit_time[u] <= low_link[edge.v])) { // 2. Non-Root Case
        printf("%d, visited_time=%d, low_link[%d]=%d\n", u, visit_time[u],
               edge.v, low_link[edge.v]);
        points.push_back(u);
        is_ap = true;
      }
    }
  };

  for (int u = 0; u < _n_vertices; ++u) {
    if (visit_time[u] == -1) {
      dfs(u);
    }
  }
}

void Graph::SingleSourceShortestPathBFS(int src, std::vector<int> &dist,
                                        std::vector<int> &path) {
  dist.assign(_n_vertices, INF);
  path.assign(_n_vertices, INF);
  dist[src] = 0;

  std::queue<int> q;
  q.push(src);

  // Just do BFS and calc. distance
  // O(V + E)
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (const auto &[v, w] : adj_[u]) {
      if (dist[v] != INF) {
        continue;
      }
      dist[v] = dist[u] + 1;
      q.push(v);
      path[v] = u;
    }
  }
}

void Graph::SingleSourceShortestPathDijkstra(int src, std::vector<int> &dist,
                                             std::vector<int> &path) {
  dist.assign(_n_vertices, INF);
  path.assign(_n_vertices, INF);
  dist[src] = 0;
  path[src] = src;

  using DistPair = std::pair<int, int>; // <dist, node>
  std::priority_queue<DistPair, std::vector<DistPair>, std::greater<DistPair>>
      pq;
  pq.emplace(0, src);

  // GREEDY: Just choose Min. edge and relax distance
  // O((V + E)logV)
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (dist[u] < d) {
      continue;
    }

    for (const auto &[v, w] : adj_[u]) {
      if (dist[v] < d + w) {
        continue;
      }
      dist[v] = d + w;
      pq.emplace(dist[v], v);
      path[v] = u;
    }
  }
}

void Graph::SingleSourceShortestPathBellmanFord(int src, std::vector<int> &dist,
                                                std::vector<int> &path) {
  dist.assign(_n_vertices, INF);
  path.assign(_n_vertices, INF);
  dist[src] = 0;
  path[src] = src;
  // DP: Just RELAX each edge V-1 times
  // O(VE)
  for (int i = 0; i < _n_vertices - 1; ++i) {
    for (int u = 0; u < _n_vertices; ++u) {
      if (dist[u] == INF) {
        continue;
      }
      for (const auto &[v, w] : adj_[u]) {
        if (dist[v] < dist[u] + w) {
          continue;
        }
        dist[v] = dist[u] + w;
        path[v] = u;
      }
    }
  }

  // Moore optimiation => Use Queue for changed dist
}

void Graph::AllPairsShortestPathFloydWarshal(
    std::vector<std::vector<int>> &dist, std::vector<std::vector<int>> &path) {
  dist.assign(_n_vertices, std::vector<int>(_n_vertices, INF));
  path.assign(_n_vertices, std::vector<int>(_n_vertices, INF));

  for (int i = 0; i < _n_vertices; ++i) {
    dist[i][i] = 0;
    path[i][i] = i;
    for (auto &edge : _adj_list[i]) {
      dist[i][edge.v] = edge.w;
      path[i][edge.v] = i;
    }
  }

  for (int k = 0; k < _n_vertices; ++k) {
    for (int u = 0; u < _n_vertices; ++u) {
      for (int v = 0; v < _n_vertices; ++v) {
        if (dist[u][k] == INF || dist[k][v] == INF) {
          continue;
        }
        if (dist[u][v] <= dist[u][k] + dist[k][v]) {
          continue;
        }
        dist[u][v] = dist[u][k] + dist[k][v];
        path[u][v] = path[k][v];
      }
    }
  }
}

void Graph::SingleSourceSingleTargetShortestPathBidirectionalBFS(
    int src, int tgt, int &dist, std::vector<int> &path) {
  std::vector<int> s_dist(_n_vertices, INF);
  std::vector<int> t_dist(_n_vertices, INF);

  std::vector<int> s_path(_n_vertices, -1);
  std::vector<int> t_path(_n_vertices, -1);

  std::queue<int> s_q;
  std::queue<int> t_q;

  s_q.push(src);
  t_q.push(tgt);

  s_dist[src] = 0;
  t_dist[tgt] = 0;

  auto expand = [&](std::queue<int> &q, std::vector<int> &dist,
                    std::vector<int> &path, const std::vector<int> &dist_back) {
    auto u = q.front();
    q.pop();

    for (auto &[v, w] : adj_[u]) {
      if (dist[v] != INF) {
        continue;
      }
      q.push(v);
      dist[v] = dist[u] + 1;
      path[v] = u;
      if (dist_back[v] != INF) {
        return v;
      }
    }

    return -1;
  };

  int meeting_point = -1;
  while (!s_q.empty() && !t_q.empty()) {
    meeting_point = expand(s_q, s_dist, s_path, t_dist);
    if (meeting_point != -1) {
      break;
    }

    meeting_point = expand(t_q, t_dist, t_path, s_dist);
    if (meeting_point != -1) {
      break;
    }
  }

  if (meeting_point == -1) {
    dist = INF;
    return;
  }

  dist = s_dist[meeting_point] + t_dist[meeting_point];
  int i = meeting_point;
  while (i != src) {
    i = s_path[i];
    path.push_back(i);
  }
  reverse(path.begin(), path.end());
  path.push_back(meeting_point);
  i = meeting_point;
  while (i != tgt) {
    i = t_path[i];
    path.push_back(i);
  }
}

int Graph::MSTPrim(std::vector<Edge> &edges) {
  int mst = 0;

  edges.clear();
  edges.reserve(_n_vertices - 1);
  std::vector<int> visited(_n_vertices, 0);

  // Just start from any node, and choose Min. Edges from there
  // O(E log E) = O(E log V)
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
  for (const auto &edge : _adj_list[0]) {
    pq.push(edge);
  }
  visited[0] = 1;

  while (!pq.empty()) {
    auto edge = pq.top();
    pq.pop();
    if (visited[edge.v]) {
      continue;
    }

    visited[edge.v] = 1;
    mst += edge.w;
    edges.push_back(edge);

    for (const auto &edge : _adj_list[edge.v]) {
      if (visited[edge.v]) {
        continue;
      }
      pq.push(edge);
    }
  }

  return mst;
}

int Graph::MSTKruskal(std::vector<Edge> &edges) {
  int mst = 0;
  UnionFind uf(_n_vertices);

  edges.clear();
  edges.reserve(_n_vertices - 1);
  // Just choose Min. edges as long as there is no cycle
  // O(E log E) = O(E log V)
  std::sort(_edge_list.begin(), _edge_list.end());
  for (auto &edge : _edge_list) {
    if (uf.FindSet(edge.u) == uf.FindSet(edge.v)) {
      continue;
    }
    uf.UnionSet(edge.u, edge.v);
    edges.push_back(edge);
    mst += edge.w;
  }

  return mst;
}

void Graph::StronglyConnectedComponentsKosaraju(
    std::vector<std::vector<int>> &scc) {
  std::vector<bool> visited(_n_vertices, false);
  std::vector<int> order;

  scc.clear();
  std::function<void(const std::vector<std::vector<Edge>> &, int,
                     std::vector<int> &)>
      dfs = [&](const std::vector<std::vector<Edge>> &adj_list, int u,
                std::vector<int> &out_order) {
        visited[u] = true;
        for (auto &edge : adj_list[u]) {
          if (visited[edge.v]) {
            continue;
          }
          dfs(adj_list, edge.v, out_order);
        }
        out_order.push_back(u);
      };

  // 1st DFS
  for (int u = 0; u < _n_vertices; ++u) {
    if (visited[u]) {
      continue;
    }
    dfs(_adj_list, u, order);
  }

  std::vector<std::vector<Edge>> adj_list_rev;
  adj_list_rev.assign(_n_vertices, std::vector<Edge>());
  // Reverse
  for (int u = 0; u < _n_vertices; ++u) {
    for (auto &edge : _adj_list[u]) {
      adj_list_rev[edge.v].push_back(Edge(edge.v, u, edge.w));
    }
  }

  // 2nd DFS
  visited.assign(_n_vertices, false);
  while (!order.empty()) {
    int u = order.back();
    order.pop_back();

    if (visited[u]) {
      continue;
    }

    scc.push_back({});
    auto &comp = scc.back();
    dfs(adj_list_rev, u, comp);
  }
}

void Graph::StronglyConnectedComponentsTarjan(
    std::vector<std::vector<int>> &scc) {
  std::stack<int> stck;
  std::vector<bool> on_stck(_n_vertices, false);
  std::vector<int> id(_n_vertices, -1);
  std::vector<int> low_link(_n_vertices, -1);
  int last_id = 0;

  scc.clear();
  std::function<void(int u)> dfs;
  dfs = [&](int u) {
    stck.push(u);
    on_stck[u] = true;
    id[u] = last_id;
    low_link[u] = last_id;
    ++last_id;

    for (auto &edge : _adj_list[u]) {
      if (id[edge.v] == -1) {
        dfs(edge.v);
      }
      if (on_stck[edge.v]) {
        low_link[u] = std::min(low_link[u], low_link[edge.v]);
      }
    }

    if (id[u] == low_link[u]) {
      // Root of SCC
      scc.push_back({});
      int k = -1;
      while (k != u) {
        k = stck.top();
        stck.pop();
        on_stck[k] = false;
        scc.back().push_back(k);
      }
    }
  };

  for (int u = 0; u < _n_vertices; ++u) {
    if (id[u] == -1) {
      dfs(u);
    }
  }
}

int Graph::MaxFlowFordFulkerson(int src, int sink) {
  int mf = 0;
  std::vector<int> parent;

  // Init. Forward & Reverse Edges
  std::vector<std::vector<Edge>> mf_adj_mat(
      _n_vertices, std::vector<Edge>(_n_vertices, Edge(-1, -1, 0)));
  for (int u = 0; u < _n_vertices; ++u) {
    for (auto &edge : _adj_list[u]) {
      mf_adj_mat[u][edge.v] = edge;
      mf_adj_mat[edge.v][u] = Edge(edge.v, u, 0);
    }
  }

  std::function<bool(int u)> bfs = [&](int u) {
    std::queue<int> q;
    q.push(u);
    parent.assign(_n_vertices, -1);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto &edge : mf_adj_mat[u]) {
        if (edge.w <= 0) {
          // no capacity
          continue;
        }
        if (parent[edge.v] != -1 || edge.v == src) {
          // visited
          continue;
        }
        q.push(edge.v);
        parent[edge.v] = u;
        if (edge.v == sink) {
          return true;
        }
      }
    }
    return false;
  };

  while (bfs(src)) {
    // Find Bottle neck
    int v = sink;
    int u = parent[v];
    int bottle_neck = mf_adj_mat[u][v].w;

    v = u;
    while (parent[v] != -1) {
      u = parent[v];
      bottle_neck = std::min(bottle_neck, mf_adj_mat[u][v].w);
      v = u;
    }

    // Update flow capacity
    v = sink;
    while (parent[v] != -1) {
      u = parent[v];
      printf("(%d, %d) <- ", u, v);
      mf_adj_mat[u][v].w -= bottle_neck;
      mf_adj_mat[v][u].w += bottle_neck;
      v = u;
    }
    mf += bottle_neck;
    printf("\nbottle_neck = %d\n", bottle_neck);
  }

  return mf;
}

int Graph::MaxFlowFordDinic(int src, int sink) {
  int mf = 0;
  std::vector<std::vector<Edge>> mf_adj_mat(
      _n_vertices, std::vector<Edge>(_n_vertices, Edge(-1, -1, 0)));
  std::vector<int> level;

  for (int u = 0; u < _n_vertices; ++u) {
    for (auto &edge : _adj_list[u]) {
      mf_adj_mat[u][edge.v] = edge;
      mf_adj_mat[edge.v][u] = Edge(edge.v, u, 0);
    }
  }

  auto bfs = [&]() {
    std::queue<int> q;
    q.push(src);
    level.assign(_n_vertices, -1);
    level[src] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &edge : mf_adj_mat[u]) {
        if (edge.w <= 0) {
          // no cap.
          continue;
        }
        if (level[edge.v] != -1) {
          // visited
          continue;
        }
        level[edge.v] = level[u] + 1;
        q.push(edge.v);
        if (edge.v == sink) {
          return true;
        }
      }
    }
    return false;
  };

  std::vector<int> last_valid_edge_idx;
  std::function<int(int, int)> dfs = [&](int u, int flow) -> int {
    if (u == sink) {
      return flow;
    }
    // By referecene to update last_valid_edge_idx[u]
    for (int &v = last_valid_edge_idx[u]; v < _n_vertices; ++v) {
      auto &edge = mf_adj_mat[u][v];

      if (edge.w == 0) {
        // no cap
        continue;
      }
      if (level[edge.v] != level[u] + 1) {
        // not progressing
        continue;
      }
      int bottle_neck = dfs(edge.v, std::min(flow, edge.w));
      if (bottle_neck > 0) {
        // Found path
        // Update capacity
        mf_adj_mat[u][edge.v].w -= bottle_neck;
        mf_adj_mat[edge.v][u].w += bottle_neck;
        return bottle_neck;
      }
    }
    return 0;
  };

  while (bfs()) {
    last_valid_edge_idx.assign(_n_vertices, 0);
    while (1) {
      int bottle_neck = dfs(src, INF);
      if (bottle_neck) {
        mf += bottle_neck;
      } else {
        break;
      }
    }
  }

  return mf;
}
