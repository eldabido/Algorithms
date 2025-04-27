#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// Структура "Ребро".
struct Edge {
  int vend; // Вершина, в которую ведёт ребро.
  int cap; // Пропускная способность.
  int flow; // Поток.
  int rev; // Индекс обратного ребра.
};

class Dinic {
public:
  // Список смежности.
  std::vector<std::vector<Edge>> graph;
  // Уровни вершин.
  int numVertices;
  std::vector<int> level, ptr;
  Dinic(int n) : numVertices(n), level(n), ptr(n), graph(n) {}

  // Добавление ребра.
  void add_edge(int from, int vend, int capacity) {
    graph[from].push_back({vend, capacity, 0, (int)graph[vend].size()});
    graph[vend].push_back({from, 0, 0, (int)graph[from].size() - 1});
  }

  // BFS и DFS для Диница.
  bool bfs(int source, int sink) {
    std::fill(level.begin(), level.end(), -1);
    level[source] = 0;
    std::queue<int> q;
    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &e : graph[u]) {
        if (e.cap > e.flow && level[e.vend] == -1) {
          level[e.vend] = level[u] + 1;
          q.push(e.vend);
        }
      }
    }
    return level[sink] != -1;
  }

  int dfs(int u, int sink, int flow) {
    if (u == sink) {
      return flow;
    }
    for (int &i = ptr[u]; i < graph[u].size(); ++i) {
      auto &e = graph[u][i];
      if (e.cap > e.flow && level[e.vend] == level[u] + 1) {
        int pushed = dfs(e.vend, sink, std::min(flow, e.cap - e.flow));
        if (pushed > 0) {
          e.flow += pushed;
          graph[e.vend][e.rev].flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }
  // Сам поиск.
  int flow(int source, int sink) {
    int flow = 0;
    while (bfs(source, sink)) {
      std::fill(ptr.begin(), ptr.end(), 0);
      while (int pushed = dfs(source, sink, 100001)) {
        flow += pushed;
      }
    }
    return flow;
  }
};

int main() {
  // Ввод.
  int n;
  int m;
  int a;
  int h;
  std::cin >> n >> m >> a >> h;
  Dinic dinic(n + 2);
  int source = 0;
  int sink = n + 1;
  dinic.add_edge(source, a, 2);
  dinic.add_edge(h, sink, 2);
  int x;
  int y;
  for (int i = 0; i < m; ++i) {
    std::cin >> x >> y;
    dinic.add_edge(x, y, 1);
  }

  // Находим поток.
  int floww = dinic.flow(source, sink);
  // Если меньше двух, то нет двух путей.
  if (floww < 2) {
    std::cout << "NO\n";
    return 0;
  }
  // Иначе они есть. И находим их.
  std::cout << "YES\n";

  std::vector<int> path1;
  std::vector<int> path2;
  int u = a;
  while (u != h) {
    path1.push_back(u);
    for (auto &e : dinic.graph[u]) {
      if (e.flow > 0) {
        --e.flow;
        u = e.vend;
        break;
      }
    }
  }
  path1.push_back(h);

  u = a;
  while (u != h) {
    path2.push_back(u);
    for (auto &e : dinic.graph[u]) {
      if (e.flow > 0) {
        --e.flow;
        u = e.vend;
        break;
      }
    }
  }
  path2.push_back(h);
  // Вывод.
  for (int v : path1) std::cout << v << " ";
  std::cout << "\n";
  for (int v : path2) std::cout << v << " ";
}
