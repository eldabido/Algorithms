#include <iostream>
#include <vector>
#include <string>

std::vector<int> search_gift(std::string gift, std::string text) {
  // Уточнение грани строки.
  std::vector<int> ans;
  int m = gift.size();
  int n = text.size();
  if (m == 0 || n == 0 || m > n) {
    return ans;
  }
  std::vector<int> pi(m, 0);
  int k = 0;
  for (int i = 1; i < m; ++i) {
    while (k > 0 && gift[k] != gift[i]) {
      k = pi[k - 1];
    }
    if (gift[k] == gift[i]) {
      ++k;
    }
    pi[i] = k;
  }
  // Поиск.
  int p = 0;
  for (int i = 0; i < n; ++i) {
    while (p > 0 && gift[p] != text[i]) {
      p = pi[p - 1];
    }
    if (gift[p] == text[i]) {
      ++p;
    }
    if (p == m) {
      ans.push_back(i - m + 1);
      p = pi[p - 1];
    }
  }
  return ans;
}

int main() {
  std::string gift, text;
  std::cin >> gift;
  std::cin >> text;

  std::vector<int> ans = search_gift(gift, text);

  std::cout << ans.size() << "\n";
  for (int position: ans) {
      std::cout << position << "\n";
  }
}
