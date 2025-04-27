#include <iostream>
#include <string>
#include <vector>

// Решалось алгоритмом Тоома-Кука. Храним не одну цифру, а сразу девять в одной ячейке вектора.
// То есть  берем систему счисления с девятью цифрами.
const int base = 1000000000;

// Основная функция.
std::vector<int> toom_cook(std::vector<int> a, std::vector<int> b) {
  // Результат в c.
  std::vector<int> c(a.size() + b.size());
  for (size_t i = 0; i < a.size(); ++i) {
    // Умножение в соответствующей СС.
    int carry = 0;
    for (size_t j = 0; j < b.size() || carry; ++j) {
      long long num = c[i+j] + a[i] * 1ll * (j < b.size() ? b[j] : 0) + carry;
      c[i + j] = num % base;
      carry = num / base;
    }
  }

  // Удаление ведущих нулей.
  while (c.size() > 1 && c.back() == 0)
    c.pop_back();
    return c;
}

// Вывод числа.
void print(std::vector<int> a) {
  if (a.empty()) {
    std::cout << 0;
  } else {
    std::cout << a.back();
  }

  for (int i = a.size() - 2; i>=0; --i) {
    printf ("%09d", a[i]);
  }
}

int main() {
  std::vector<int> a;
  std::vector<int> b;
  std::string A, B;
  std::cin >> A;
  std::cin >> B;
  // Считываем число A по 9 цифр.
  for (int i= A.length(); i > 0; i -= 9) {
	if (i < 9) {
		a.push_back (std::atoi (A.substr (0, i).c_str()));
	} else {
		a.push_back (std::atoi (A.substr (i-9, 9).c_str()));
    }
  }
  // Считываем число B по 9 цифр.
  for (int i = B.length(); i > 0; i -= 9) {
    if (i < 9) {
      b.push_back (std::atoi (B.substr (0, i).c_str()));
    } else {
      b.push_back (std::atoi (B.substr (i-9, 9).c_str()));
    }
  }
  // Начинаем умножение.
  print(toom_cook(a, b));
}
