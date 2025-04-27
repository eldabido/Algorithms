#include <iostream>
#include <vector>
#include <string>

// Ищется алгоритмом Манакера.
long long cntPal(std::string s) {
  int n = s.size();
  if (n == 0) return 0;
  std::string t = "*";
  for (char c : s) {
    t += c;
    t += '*';
  }
  int m = t.size();
  // Длины палиндромов.
  std::vector<int> len_pals(m, 0);

  int center = 0;
  int right = 0;
  for (int i = 1; i < m - 1; ++i) {
    int mirror = 2 * center - i;
    if (i < right) {
        len_pals[i] = std::min(right - i, len_pals[mirror]);
    }
    while (i + len_pals[i] + 1 < m && i - len_pals[i] - 1 >= 0 && t[i + len_pals[i] + 1] == t[i - len_pals[i] - 1]) {
      len_pals[i]++;
    }
    if (i + len_pals[i] > right) {
      center = i;
      right = i + len_pals[i];
    }
  }

  long long cnt = 0;
  for (int len : len_pals) {
    cnt += (len + 1) / 2;
  }

  return cnt;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << cntPal(s);
}
