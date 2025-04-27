#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

// Проверка на совместимость соков.
bool withoutCleaning(std::set<std::string>& A, std::set<std::string>& B) {
  for (const std::string& comp : A) {
    if (B.find(comp) == B.end()) {
      return false;
    }
  }
  return true;
}

// DFS для алгоритма Куна.
bool dfs(int u, std::vector<std::vector<int>>& graph, std::vector<int>& match, std::vector<bool>& used) {
  if (used[u]) {
    return false;
  }
  used[u] = true;
  for (int v : graph[u]) {
    if (match[v] == -1 || dfs(match[v], graph, match, used)) {
      match[v] = u;
      return true;
    }
  }
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Ввод.
  int n;
  std::cin >> n;
  std::vector<std::set<std::string>> juices(n);
  for (int i = 0; i < n; ++i) {
    int k;
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
      std::string component;
      std::cin >> component;
      juices[i].insert(component);
    }
  }
  std::vector<std::vector<int>> graph(n);
  // Строим граф.
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && withoutCleaning(juices[i], juices[j])) {
        graph[i].push_back(j);
      }
    }
  }
  // Нахождение максимального паросочетания.
  std::vector<int> match(n, -1);
  int matchingSize = 0;
  for (int i = 0; i < n; ++i) {
    std::vector<bool> used(n, false);
    if (dfs(i, graph, match, used)) {
        ++matchingSize;
    }
  }
  std::cout << n - matchingSize;
}
