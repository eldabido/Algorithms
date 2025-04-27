#include <iostream>
#include <vector>
#include <algorithm>

class Edge {
public:
  int u;
  int v;
  int weight;
  bool operator<(Edge const& other) {
    return weight < other.weight;
  }
};

int find(std::vector<int>& parent, int v) {
  if (v == parent[v])
    return v;
  parent[v] = find(parent, parent[v]);
  return parent[v];
}

void union_sets(std::vector<int>& parent, std::vector<int>& rank, int a, int b) {
    a = find(parent, a);
    b = find(parent, b);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            ++rank[a];
    }
}

int main() {
  // Воспользуемся алгоритмом Краскала.
  // Инициализация.
  int n, m;
  std::cin >> n >> m;
  std::vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
  }
  // Сортируем по весу.
  std::sort(edges.begin(), edges.end());

  // DSU.
  std::vector<int> parent;
  std::vector<int> rank;

  parent.resize(n + 1);
  rank.resize(n + 1);
  for (int i = 1; i <= n; ++i) {
    parent[i] = i;
    rank[i] = 0;
  }

  // Находим минимальный остов.
  std::vector<Edge> mst_edges;
  int mst = 0;
  for (auto edge : edges) {
    if (find(parent, edge.u) != find(parent, edge.v)) {
      mst += edge.weight;
      mst_edges.push_back(edge);
      union_sets(parent, rank, edge.u, edge.v);
    }
  }
  // Ищем второй.
  int second_mst = INT_MAX;
  for (int i = 0; i < mst_edges.size(); ++i) {
    for (int j = 1; j <= n; ++j) {
      parent[j] = j;
      rank[j] = 0;
    }
    int cur_cost = 0;
    int edge_cnt = 0;
    for (auto edge : edges) {
      if (edge.u == mst_edges[i].u && edge.v == mst_edges[i].v
          && edge.weight == mst_edges[i].weight)
        continue;
      if (find(parent, edge.u) != find(parent, edge.v)) {
        cur_cost += edge.weight;
        union_sets(parent, rank, edge.u, edge.v);
        ++edge_cnt;
      }
    }
    if (edge_cnt == n - 1)
      second_mst = std::min(second_mst, cur_cost);
  }
  std::cout << mst << " " << second_mst << "\n";
}
