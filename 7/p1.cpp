#include <iostream>
#include <vector>
#include <queue>
#include <climits>

// Структура "Ребро".
struct Edge {
  long long vend; // Вершина, в которую ведёт ребро.
  long long weight; // Пропускная способность.
  long long flow; // Текущий поток.
  long long rev; // Индекс обратного ребра.
};


// Делаем с помощью алгоритма Диница.
class Dinic {
public:
  // Список смежности.
  std::vector<std::vector<Edge>> graph_adj;
  // Уровни вершин.
  std::vector<long long> level;
  std::vector<size_t> ptr;

  Dinic(long long n) : graph_adj(n), level(n), ptr(n) {}

  void addEdge(long long beg, long long vend, long long weight) {
    graph_adj[beg].push_back({vend, weight, 0, (long long)graph_adj[vend].size()});
    graph_adj[vend].push_back({beg, 0, 0, (long long)graph_adj[beg].size() - 1});
  }

  bool bfs(long long s, long long t) {
    for (long long i = 0; i < level.size(); ++i) {
      level[i] = -1;
    }
    level[s] = 0;
    std::queue<long long> q;
    q.push(s);

    while (!q.empty()) {
      long long u = q.front();
      q.pop();

      for (const Edge& e : graph_adj[u]) {
        if (level[e.vend] == -1 && e.flow < e.weight) {
          level[e.vend] = level[u] + 1;
          q.push(e.vend);
        }
      }
    }
    return level[t] != -1;
  }

  long long dfs(long long u, long long t, long long flow) {
    if (flow == 0) {
      return 0;
    }
    if (u == t) {
      return flow;
    }

    for (size_t i = ptr[u]; i < graph_adj[u].size(); ++i) {
      Edge& e = graph_adj[u][i];
      if (level[e.vend] == level[u] + 1 && e.flow < e.weight) {
        long long pushed = dfs(e.vend, t, std::min(flow, e.weight - e.flow));
        if (pushed > 0) {
          e.flow += pushed;
          graph_adj[e.vend][e.rev].flow -= pushed;
          ptr[u] = i;
          return pushed;
        }
      }
    }
    ptr[u] = graph_adj[u].size();
    return 0;
  }

  long long flow(long long s, long long t) {
    long long totalFlow = 0;
    while (bfs(s, t)) {
      std::fill(ptr.begin(), ptr.end(), 0);
      while (long long pushed = dfs(s, t, LLONG_MAX)) {
        totalFlow += pushed;
      }
    }
    return totalFlow;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  long long n;
  long long m;
  std::cin >> n >> m;
  Dinic dinic(n);
  long long beg;
  long long vend;
  long long weight;
  for (long long i = 0; i < m; ++i) {
    std::cin >> beg >> vend >> weight;
    dinic.addEdge(beg - 1, vend - 1, weight);
  }
  long long s = 0;
  long long t = n - 1;
  std::cout << dinic.flow(s, t);
}
