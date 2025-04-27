#include <iostream>
#include <vector>

struct Edge {
    int u;
    int v;
    int w;
};

void BellmanFord(std::vector<Edge>& edges, std::vector<long long>& dist, int n, int m) {
  dist[0] = 0;
  // Релаксация.
  for (int i = 1; i < n; ++i) {
    for (auto edge : edges) {
      if (dist[edge.u] != LLONG_MAX && dist[edge.u] + edge.w < dist[edge.v]) {
        dist[edge.v] = dist[edge.u] + edge.w;
      }
    }
  }

  // Проверка на наличие отрицательных циклов.
  for (int i = 1; i < n; ++i) {
    for (auto edge : edges) {
      if ((dist[edge.u] != LLONG_MAX && dist[edge.u] + edge.w < dist[edge.v])) {
        dist[edge.v] = LLONG_MIN;
      }
    }
  }

  // Пометить все вершины, участвующие в отрицательном цикле.
  for (int i = 1; i < n; ++i) {
    for (const auto& edge : edges) {
      if (dist[edge.u] == LLONG_MIN && dist[edge.v] != LLONG_MIN) {
        dist[edge.v] = LLONG_MIN;
      }
    }
  }
}

int main() {
  // Алгоритм Беллмана-Форда. Инициализация.
  int n, m;
  std::cin >> n >> m;
  std::vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
  }
  // Расстояния.
  std::vector<long long> dist(n, LLONG_MAX);
  // Запускаем алгоритм.
  BellmanFord(edges, dist, n, m);
  // Вывод.
  for (int i = 1; i < n; ++i) {
    if (dist[i] == LLONG_MIN) {
      std::cout << "-inf\n";
    } else {
      std::cout << dist[i] << "\n";
    }
  }
}
