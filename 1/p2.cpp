#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

int main() {
  size_t n = 0;
  std::cin >> n;
  // Наш массив.
  std::vector<long long> arr(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  // Заводим число Хэмминга и счетчик сдвигов.
  int hamm_num = -1;
  int counter = 0;
  // Также нам нужно учесть то, что могут быть одинаковые массивы при разных сдвигах.
  // Поэтому создадим множество тех массивов, которые уже получались.
  // Будем хранить их строками, так удобнее.
  std::unordered_set<std::string> checked_arrs;
  // Начинаем проход.
  for (size_t i = 0; i < n; ++i) {
    // Массив, с которым будем сравнивать.
    std::vector<long long> cmp(n);
    // Осуществляем сдвиг.
    for (size_t j = 0; j < n; ++j) {
      cmp[j] = arr[(i + j) % n];
    }
    // Преобразуем в строку для удобства.
    std::string str = "";
    for (int m = 0; m < n; ++m) {
      str += std::to_string(cmp[m]);
    }
    // Считаем расстояние.
    if (checked_arrs.find(str) == checked_arrs.end()) {
      int dist = 0;
      for (size_t k = 0; k < n; ++k) {
        if (arr[k] != cmp[k]) {
          ++dist;
        }
      }
      // Анализируем результат.
      if (dist > hamm_num) {
        hamm_num = dist;
        counter = 1;
      } else if (dist == hamm_num) {
        ++counter;
      }
      checked_arrs.insert(str);
    }
  }
  std::cout << counter;
}