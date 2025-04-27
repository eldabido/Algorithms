#include <iostream>
#include <string>
#include <vector>

class DSU {
public:
  std::vector<int> parent;
  std::vector<int> rank;

  DSU(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
      parent[i] = i;
    }
  }

  int find(int v) {
    if (parent[v] != v) {
      parent[v] = find(parent[v]);
    }
    return parent[v];
  }

  void union_(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
      if (rank[u] < rank[v]) {
        std::swap(u, v);
      }
      parent[v] = u;
      rank[u] += rank[v];
    }
  }

  bool connect(int u, int v) {
    return find(u) == find(v);
  }
};

int main() {
  // Инициализация.
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  std::vector<std::pair<int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> edges[i].first >> edges[i].second;
  }
  // Считываем операции.
  std::vector<std::pair<std::string, std::pair<int, int>>> operations(k);
  std::string comm;
  int u;
  int v;
  for (int i = 0; i < k; ++i) {
    std::cin >> comm >> u >> v;
    operations[i] = {comm, {u, v}};
  }

  DSU dsu(n);
  // Считываем в обратном порядке. При cut делаем union, а при ask проверяем, есть ли путь.
  std::vector<std::string> result;
  for (int i = k - 1; i >= 0; --i) {
    comm = operations[i].first;
    u = operations[i].second.first;
    v = operations[i].second.second;

    if (comm == "cut") {
      dsu.union_(u, v);
    } else if (comm == "ask") {
      if (dsu.connect(u, v)) {
        result.push_back("YES");
      } else {
        result.push_back("NO");
      }
    }
  }

  // Вывод.
  for (int i = result.size() - 1; i >= 0; --i) {
      std::cout << result[i] << '\n';
  }
}
