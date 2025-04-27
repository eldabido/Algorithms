#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Тут две почти одинаковые версии функций, но одна с помощью бин поиска, другая прямолинейная.

std::pair<int, std::pair<int, int>> find(const std::vector<int>& a, const std::vector<int>& b) {
  int n = a.size();
  int m = b.size();
  int max_length = 0;
  int start_a = -1;
  int start_b = -1;
  int begin = 0;
  int end = std::min(n, m) + 1;

  while (begin < end) {
    int k = (begin + end) / 2;
    std::unordered_map<int, int> count_a, count_b;
    for (int i = 0; i < k; ++i) {
      ++count_a[a[i]];
      ++count_b[b[i]];
    }
    bool found = false;
    for (int i = 0; i <= n - k; ++i) {
      if (i > 0) {
        --count_a[a[i - 1]];
        if (count_a[a[i - 1]] == 0) {
          count_a.erase(a[i - 1]);
        }
        ++count_a[a[i + k - 1]];
      }
      std::unordered_map<int, int> temp_count_b = count_b;
      for (int j = 0; j <= m - k; ++j) {
        if (j > 0) {
          --temp_count_b[b[j - 1]];
          if (temp_count_b[b[j - 1]] == 0) {
            temp_count_b.erase(b[j - 1]);
          }
          ++temp_count_b[b[j + k - 1]];
        }
        if (count_a == temp_count_b) {
          max_length = k;
          start_a = i + 1;
          start_b = j + 1;
          found = true;
          break;
        }
      }
      if (found) break;
    }
    if (found) {
        begin = k + 1;
    } else {
        end = k;
    }
  }
  return {max_length, {start_a, start_b}};
}

std::pair<int, std::pair<int, int>> find_for_small(const std::vector<int>& a, const std::vector<int>& b) {
  int n = a.size();
  int m = b.size();
  int max_length = 0;
  int start_a = -1;
  int start_b = -1;

  for (int k = std::min(n, m); k >= 1; --k) {
    std::unordered_map<int, int> count_a, count_b;
    for (int i = 0; i < k; ++i) {
      ++count_a[a[i]];
      ++count_b[b[i]];
    }
    for (int i = 0; i <= n - k; ++i) {
      if (i > 0) {
        --count_a[a[i - 1]];
        if (count_a[a[i - 1]] == 0) {
          count_a.erase(a[i - 1]);
        }
        ++count_a[a[i + k - 1]];
      }
      std::unordered_map<int, int> temp_count_b = count_b;
      for (int j = 0; j <= m - k; ++j) {
        if (j > 0) {
          --temp_count_b[b[j - 1]];
          if (temp_count_b[b[j - 1]] == 0) {
            temp_count_b.erase(b[j - 1]);
          }
          ++temp_count_b[b[j + k - 1]];
        }
        if (count_a == temp_count_b) {
          max_length = k;
          start_a = i + 1;
          start_b = j + 1;
          return {max_length, {start_a, start_b}};
        }
      }
    }
  }
  return {max_length, {start_a, start_b}};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  std::vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  // Если n и m маленькие, то делаем обычный проход от максимума к минимуму, если больше, то по бинарному поиску.
  auto result = n <= 10 && m <= 10? find_for_small(a, b) : find(a, b);
  if (result.first == 0) {
    std::cout << "0 -1 -1\n";
  } else {
    std::cout << result.first << " " << result.second.first << " " << result.second.second << "\n";
  }
}
