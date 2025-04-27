#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> countingSort(std::vector<int>& stars) {
  int minimum = *std::min_element(stars.begin(), stars.end());
  int maximum = *std::max_element(stars.begin(), stars.end());
  size_t n = stars.size();
  // Сдвиг для отрицательных чисел.
  int offset = std::abs(minimum);
  // Вектор из счетчиков. Максимальный его размер - максимум + offset исходного массива.
  std::vector<int> counters(maximum + offset + 1, 0);

  // Заполняем его.
  for (int i = 0; i < n; ++i) {
    ++counters[stars[i] + offset];
  }

  // Получаем итоговый.
  std::vector<int> sorted_stars(n);
  int k = 0;
  for (int i = 0; i < maximum + offset + 1; ++i) {
    if (counters[i] != 0) {
      while (counters[i] != 0) {
        --counters[i];
        sorted_stars[k++] = i - offset;
      }
    }
  }
  return sorted_stars;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  std::cin >> n;
  if (n != 0) {
    std::vector<int> stars(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> stars[i];
    }
    stars = countingSort(stars);
    for (int i = 0; i < n; ++i) {
      std::cout << stars[i] << " ";
    }
  }
}
