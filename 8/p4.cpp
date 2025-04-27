#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

std::vector<int> boyerMooreHorspool(std::string pattern, std::string text) {
  std::vector<int> ans;
  int m = pattern.length();
  int n = text.length();
  if (m == 0 || n == 0 || m > n) {
    return ans;
  }
  // Таблица сдвигов. Представим ее в виде unordered_map.
  std::unordered_map<char, int> Table;
  for (int i = 0; i < m - 1; ++i) {
    Table[pattern[i]] = m - i - 1;
  }
  int i = 0;
  while (i <= n - m) {
    int j = m - 1;
    while (j >= 0 && pattern[j] == text[i + j]) {
      --j;
    }
    if (j < 0) {
      ans.push_back(i);
      ++i;
    } else {
      char c = text[i + m - 1];
      if (Table.find(c) != Table.end()) {
        i += Table[c];
      } else {
        i += m;
      }
    }
  }
  return ans;
}

int main() {
  std::string P, T;
  std::cin >> P >> T;
  std::vector<int> ans = boyerMooreHorspool(P, T);
  std::cout << ans.size() << "\n";
  for (int position : ans) {
    std::cout << position << "\n";
  }
}
