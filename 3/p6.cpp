#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

// Подсчет количество пар бьющих.
int calculate_of_threats(int n) {
    if (n < 2) {
      return 0;
    } else if (n == 2) {
      return 1;
    }
    return (n - 1) * n / 2;
}

// Подсчет количества ферзей, бьющих друг друга.
int estimate(std::vector<int> queens) {
  int n = queens.size();
  int threats = 0;
  std::vector<int> diag_threats1(n);
  std::vector<int> diag_threats2(n);

  for (int i = 0; i < n; i++) {
    diag_threats1[i] = queens[i] + i;
    diag_threats2[i] = i - queens[i];
  }

  std::sort(diag_threats1.begin(), diag_threats1.end());
  std::sort(diag_threats2.begin(), diag_threats2.end());

  int count1 = 1;
  int count2 = 1;
  int j = 1;
  for (int i = 0; i < n - 1; i++) {
    if (diag_threats1[i] == diag_threats1[j]) {
      count1 += 1;
    }
    else {
      threats += calculate_of_threats(count1);
      count1 = 1;
    }
    if (diag_threats2[i] == diag_threats2[j]) {
      count2 += 1;
    }
    else {
      threats += calculate_of_threats(count2);
      count2 = 1;
    }
    if (j == n - 1) {
      threats += calculate_of_threats(count1);
      threats += calculate_of_threats(count2);
      break;
    }
    ++j;
  }
  return threats;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int num = 0;
  std::cin >> num;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<int> queens(num);
  for (int i = 0; i < num; ++i) {
    queens[i] = i;
  }
  // Алгоритм, как на семинаре.
  std::shuffle(queens.begin(), queens.end(), gen);
  int energy = estimate(queens);
  double temp = 30000;
  double coef = 0.99;
  std::vector<int> new_queens(num, 0);
  while (temp != 0) {
    temp *= coef;
    new_queens = queens;
    while (true) {
      int rand1 = std::rand() % num;
      int rand2 = std::rand() % num;
      if (rand1 != rand2) {
        std::swap(new_queens[rand1], new_queens[rand2]);
        break;
      }
    }
    int new_energy = estimate(new_queens);
    int dE = new_energy - energy;
    if (dE < 0){
      queens = new_queens;
      energy = new_energy;
    } else {
      double p = exp(-dE / temp);
      if (std::rand() / double(RAND_MAX) < p) {
        queens = new_queens;
        energy = new_energy;
      }
    }
    if (energy == 0) {
      for (int i = 0; i < num; ++i) {
        std::cout << queens[i] + 1 << " ";
      }
      break;
    }
  }
}
