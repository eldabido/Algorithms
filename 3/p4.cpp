#include <iostream>
#include <string>
#include <vector>

// Структура дроби.
struct Fraction {
  // Числитель и знаменатель.
  int num = 0;
  int denom = 0;
  Fraction() {

  }

  Fraction(int a, int b) {
    num = a;
    denom = b;
  }

  // Компаратор.
  bool compare(const Fraction& other) {
    return (num * other.denom <= denom * other.num);
  }

  void print() {
    std::cout << num << "/" << denom << " ";
  }
};

// Соединение двух частей в алгоритме Merge Sort.
void merg(std::vector<Fraction>& fractions, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<Fraction> L(n1);
  std::vector<Fraction> R(n2);
  for (int i = 0; i < n1; i++)
        L[i] = fractions[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = fractions[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].compare(R[j])) {
            fractions[k] = L[i];
            i++;
        } else {
            fractions[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        fractions[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        fractions[k] = R[j];
        j++;
        k++;
    }
}

// известный алгоритм Merge Sort.
void mergeSort(std::vector<Fraction>& fractions, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(fractions, left, mid);
    mergeSort(fractions, mid + 1, right);
    merg(fractions, left, mid, right);
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  if (n != 0) {
    std::string frac;
    std::vector<Fraction> fractions(n);
    // Инициализация.
    for (int i = 0; i < n; ++i) {
      std::cin >> frac;
      int j = 0;
      int num = 0;
      int denom = 0;
      while (frac[j] != '/') {
        num = num * 10 + (frac[j] - '0');
        ++j;
      }
      ++j;
      while (j < frac.length()) {
        denom = denom * 10 + (frac[j] - '0');
        ++j;
      }
      fractions[i] = {num, denom};
    }
    // Сортировка с помощью Merge Sort.
    mergeSort(fractions, 0, n - 1);
    for (int i = 0; i < n; ++i) {
      fractions[i].print();
    }
  }
}
