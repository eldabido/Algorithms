#include <iostream>
#include <vector>

bool dfs(const std::vector<std::vector<int>>& graph_adj, std::vector<bool>& visited, std::vector<int>& matches, std::vector<int>& matches_2, int u) {
  if (visited[u])
    return false;
  visited[u] = true;
  for (int v : graph_adj[u]) {
    if (matches[v] == -1 || dfs(graph_adj, visited, matches, matches_2, matches[v])) {
      matches[v] = u;
      matches_2[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  // Считываем данные.
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph_adj(n + 1); // список смежности.
  std::vector<bool> visited(n + 1); // для посещённых вершин.
  std::vector<int> matches(m + 1, -1); // Для мэтчей, то есть пар.
  std::vector<int> matches_2(n + 1, -1); // Для вывода.

  for (int i = 1; i <= n; ++i) {
    int v;
    while (std::cin >> v && v != 0) {
        graph_adj[i].push_back(v);
    }
  }
  // Поиск алгоритмом Куна.
  int matching = 0;
  for (int u = 1; u <= n; ++u) {
    visited.assign(n + 1, false);
    if (dfs(graph_adj, visited, matches, matches_2, u)) {
        ++matching;
    }
  }
  // Вывод.
  std::cout << matching << "\n";
  for (int u = 1; u <= n; ++u) {
    if (matches_2[u] != -1) {
        std::cout << u << " " << matches_2[u] << "\n";
    }
  }
}
