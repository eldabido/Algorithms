#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <string>

// Реализация Ахо-Корасик.

struct Vertex {
  std::map<char, int> next;
  std::vector<int> pattern_inds;
  int link = -1;
  int exit_link = -1;
  int len = 0;
};

// Дерево.
std::vector<Vertex> t(1);

// Добавляем строку в дерево.
void add(std::string pattern, int ind) {
  int cur = 0;
  for (char c : pattern) {
    if (t[cur].next.find(c) == t[cur].next.end()) {
      t[cur].next[c] = t.size();
      t.emplace_back();
    }
    cur = t[cur].next[c];
  }
  t[cur].pattern_inds.push_back(ind);
  t[cur].len = pattern.size();
}

// Построение ссылок.
void link() {
  // С помощью BFS-обхода.
  std::queue<int> q;
  q.push(0);
  t[0].link = 0;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (auto &edge : t[cur].next) {
      char c = edge.first;
      int child = edge.second;
      int link = t[cur].link;

      while (link != 0 && t[link].next.find(c) == t[link].next.end()) {
        link = t[link].link;
      }

      if (cur != 0 && t[link].next.find(c) != t[link].next.end()) {
        t[child].link = t[link].next[c];
      } else {
        t[child].link = 0;
      }

      if (!t[t[child].link].pattern_inds.empty()) {
        t[child].exit_link = t[child].link;
      } else {
        t[child].exit_link = t[t[child].link].exit_link;
      }
      q.push(child);
    }
  }
}

// Поиск.
std::vector<std::vector<int>> search(std::string text, int n) {
  // Начинается с корня.
  std::vector<std::vector<int>> ans(n);
  int cur = 0;
  for (int i = 0; i < text.size(); ++i) {
    char c = text[i];
    while (cur != 0 && t[cur].next.find(c) == t[cur].next.end()) {
      cur = t[cur].link;
    }
    if (t[cur].next.find(c) != t[cur].next.end()) {
      cur = t[cur].next[c];
    } else {
      cur = 0;
    }
    int node = cur;
    while (node != -1 && node != 0) {
      for (int ind : t[node].pattern_inds) {
        int start = i - t[node].len + 2;
        ans[ind].push_back(start);
      }
      node = t[node].exit_link;
    }
  }
  return ans;
}

int main() {
  // Инициализация.
  std::string text;
  std::cin >> text;
  int n;
  std::cin >> n;
  // Шаблоны, что нужно искать.
  std::vector<std::string> patterns(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> patterns[i];
    add(patterns[i], i);
  }

  link();
  std::vector<std::vector<int>> ans = search(text, n);

  for (int i = 0; i < n; ++i) {
    std::cout << ans[i].size() << " ";
    std::sort(ans[i].begin(), ans[i].end());
    for (int position: ans[i]) {
      std::cout << position << " ";
    }
    std::cout << "\n";
  }
}
