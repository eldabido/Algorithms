#include <iostream>
#include <vector>
#include <string>

std::string s[101]; // Хранение плитки.
std::vector<std::vector<int> > graph; // Список смежности графа.
std::vector<int> mt; // Паросочетания.
std::vector<int> used; // Посещенные вершины.
std::vector<int> par; // Предки.

// DFS-алгоритм.
int dfs(int v) {
  if (used[v]) {
    return 0;
  }
  used[v] = 1;
  for (int i = 0; i < graph[v].size(); ++i) {
    int to = graph[v][i];
    if (mt[to] == -1 || dfs(mt[to])) {
      mt[to] = v;
      par[v] = to;
      return 1;
    }
  }
  return 0;
}

// Алгоритм Куна.
void path(int n, int m) {
  mt.assign(n * m, -1);
  par.assign(n * m, -1);
  for (int run = 1; run; ) {
    run = 0;
    used.assign(n * m, 0);
    for (int i = 0; i < n; ++i){
      for (int j = 0; j < m; ++j) {
        if ((i + j) % 2) {
          continue;
        }
        if ((par[i * m + j] == -1) && dfs(i * m + j)) {
          run = 1;
        }
      }
    }
  }
}

int main() {
  // Ввод.
  int n;
  int m;
  int a;
  int b;
  std::cin >> n >> m >> a >> b;
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
  }

  // Строим граф из свободных клеток.
  graph.resize(n * m);
  int empt = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == '.') {
        continue; // Если занята, то пропускаем.
      }
      ++empt;
      if ((i + j) % 2) {
        continue;
      }
      int u = i * m + j; // Номер вершины клетки.
      // Добавляем ребра в граф для соседних свободных клеток.
      if ((j > 0) && (s[i][j - 1] == '*'))
        graph[u].push_back(u - 1);
      if ((j < m - 1) && (s[i][j + 1] == '*'))
        graph[u].push_back(u + 1);
      if ((i > 0) && (s[i - 1][j] == '*'))
        graph[u].push_back(u - m);
      if ((i < n - 1) && (s[i + 1][j] == '*'))
        graph[u].push_back(u + m);
    }
  }
  // Простой случай.
  if (2 * b <= a) {
    std::cout << empt * b;
    return 0;
  }
  path(n, m);
  int c = 0;
  for (int i = 0; i < n * m; ++i) {
    if (mt[i] != -1)
      ++c;
  }
  int res = c * a + (empt - 2 * c) * b;
  std::cout << res;
}
