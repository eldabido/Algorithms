#include <iostream>
#include <vector>
#include <algorithm>

// Тут две версии dfs для удобства.
void dfs1(std::vector<std::vector<int>>& adj, std::vector<int>& order, std::vector<bool>& visited, int v) {
  visited[v] = true;
  for (int u : adj[v]) {
    if (!visited[u]) {
      dfs1(adj, order, visited, u);
    }
  }
  order.push_back(v);
}

void dfs2(std::vector<std::vector<int>>& adj_rev, std::vector<int>& component, std::vector<bool>& visited, int v, int k) {
  visited[v] = true;
  component[v] = k;
  for (int u : adj_rev[v]) {
    if (!visited[u]) {
      dfs2(adj_rev, component, visited, u, k);
    }
  }
}

int main() {
  // Пользуемся алгоритмом Косарайю.
  std::vector<std::vector<int>> adj; // Исходный граф.
  std::vector<std::vector<int>> adj_rev; // Reversed граф.
  std::vector<bool> visited; // Посещенные вершины.
  std::vector<int> order; // Порядок обхода.
  std::vector<int> component; // Компоненты.

  // Инициализация.
  int n, m;
  std::cin >> n >> m;
  adj.resize(n);
  adj_rev.resize(n);
  int a, b;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    --a;
    --b;
    adj[a].push_back(b);
    adj_rev[b].push_back(a);
  }

  // Начинаем первый обход для порядка вершин.
  visited.assign(n, false);
    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        dfs1(adj, order, visited, i);
      }
    }
    std::reverse(order.begin(), order.end());
    visited.assign(n, false);
    component.assign(n, -1);
    int k = 0;
    // На втором обходе обходим в порядке order и находим КСС.
    for (auto vert : order) {
      if (!visited[vert]) {
        dfs2(adj_rev, component, visited, vert, k);
        k++;
      }
    }

    // Вывод.
    std::cout << k << "\n";
    for (auto i : component) {
      std::cout << i + 1 << " ";
    }
    std::cout << "\n";
}
