#include <algorithm>
#include <iostream>
#include <vector>

void radixSort(std::vector<int>& A) {
  int maximum = *std::max_element(A.begin(), A.end());
  int minimum = *std::min_element(A.begin(), A.end());
  // Сдвиг для учитывания отрицательных чисел.
  int offset = std::abs(minimum);
  int n = A.size();
  // Вектор, куда помещаем итог после каждой итерации.
  std::vector<int> tmp(n);
  for (long long exp = 1; (maximum + offset) / exp != 0; exp *= 256) {
    // Вектор счетчиков.
    std::vector<int> counters(256, 0);
    for (int i = 0; i < n; ++i) {
      ++counters[(A[i] + offset) / exp % 256];
    }
    for (int i = 1; i < 256; ++i) {
      counters[i] += counters[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      tmp[--counters[(A[i] + offset) / exp % 256]] = A[i];
    }
    for (int i = 0; i < n; ++i) {
      A[i] = tmp[i];
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  std::cin >> n;
  if (n != 0) {
    std::vector<int> beastmen(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> beastmen[i];
    }
    radixSort(beastmen);
    for (int i = 0; i < n; ++i) {
      std::cout << beastmen[i] << " ";
    }
  }
}
