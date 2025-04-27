#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

// Перевод в двоичную СС.
std::string HexToBin(std::string tmp) {
  const std::string nums[16] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                                 "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    std::string ans;
    for (char c : tmp) {
        if (isdigit(c)) {
            ans += nums[c - '0'];
        } else {
            ans += nums[10 + toupper(c) - 'A'];
        }
    }
    return ans;
}

// Проверка путём вычисления A*B*r - C*r
bool MonteCarlo(const Matrix& A, const Matrix& B, const Matrix& C, const std::vector<int>& r, int n) {
  std::vector<int> br(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      br[i] = (br[i] + B[i][j] * r[j]) % 2;
    }
  }
  std::vector<int> cr(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cr[i] = (cr[i] + C[i][j] * r[j]) % 2;
    }
  }
  std::vector<int> abr(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      abr[i] = (abr[i] + A[i][j] * br[j]) % 2;
    }
  }

  for (int i = 0; i < n; i++) {
    if (abr[i] - cr[i] != 0) {
      return false;
    }
  }
  return true;
}

bool checking_mult(const Matrix& A, const Matrix& B, const Matrix& C, int n) {
  // Генерим 25 случайных векторов и проверяем.
  std::vector<int> r(n);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  for (int i = 0; i < 25; ++i) {
    for (int i = 0; i < n; ++i) {
      r[i] = dis(gen);
    }
    if (!MonteCarlo(A, B, C, r, n)) {
      return false;
    }
  }
  return true;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::string tmp;
  // Инициализация A.
  Matrix A(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    tmp = HexToBin(tmp);
    for (int j = 0; j < n; ++j) {
      A[i][j] = tmp[j] - '0';
    }
  }
  // Инициализация B.
  Matrix B(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    tmp = HexToBin(tmp);
    for (int j = 0; j < n; ++j) {
      B[i][j] = tmp[j] - '0';
    }
  }
  // Инициализация C.
  Matrix C(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    tmp = HexToBin(tmp);
    for (int j = 0; j < n; ++j) {
      C[i][j] = tmp[j] - '0';
    }
  }

  if (checking_mult(A, B, C, n)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}
