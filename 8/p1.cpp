#include <iostream>
#include <vector>
#include <string>

std::vector<int> KnutMorPrat(std::string s) {
  // Итоговый массив.
  // Поиск по алгоритму Кнута-Морриса-Прата.
  std::vector<int> pi(s.size(), 0);
  for (int i = 1; i < s.size(); ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = pi[j - 1];
    }
    if (s[i] == s[j]) {
      ++j;
    }
    pi[i] = j;
  }

  return pi;
}

int main() {
  // Принимаем строку.
  std::string s;
  std::cin >> s;
  // Вычисление.
  std::vector<int> pi = KnutMorPrat(s);
  // Вывод.
  for (int pref: pi) {
    std::cout << pref << " ";
  }
}
