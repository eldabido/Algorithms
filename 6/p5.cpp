#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  // Алгоритм Флойда-Уоршелла. Инициализация.
  const long long maxx = LLONG_MAX;
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, maxx));
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }
  // Считываем дугию
  for (int i = 0; i < m; ++i) {
      int u;
      int v;
      int w;
      std::cin >> u >> v >> w;
      if (dist[u][v] > w) {
          dist[u][v] = w;
      }
  }

  // Сам алгоритм.
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] < maxx && dist[k][j] < maxx) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }

  // Вывод.
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        if (dist[i][j] == maxx) {
          std::cout << i << " " << j << " -1\n";
        } else {
          std::cout << i << " " << j << " " << dist[i][j] << "\n";
        }
      }
    }
  }
}
