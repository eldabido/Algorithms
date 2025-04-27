#include <iostream>
#include <vector>
#include <string>

int search_min_len(std::string s) {
  // Решаем с помощью префикс-функций.
  int n = s.size();
  std::vector<int> pi(n, 0);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = pi[j - 1];
    }
    if (s[i] == s[j]) {
      ++j;
    }
    pi[i] = j;
  }
  int ans = n - pi[n - 1];
  // Проверка, если приходится обрезать, как во втором тесте.
  for (int i = ans; i < n; ++i) {
    if (s[i] != s[i % ans]) {
      return n;
    }
  }
  return ans;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << search_min_len(s);
}

