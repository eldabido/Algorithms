#include <iostream>
#include <vector>


struct Interval {
    int left  = 0;
    int right = 0;

// Конструкторы.
    Interval() {

    }

    Interval(int l, int r) {
      left = l;
      right = r;
    }

    Interval& operator=(const Interval& other) {
      left = other.left;
      right = other.right;
      return *this;
    }

    Interval(const Interval& other) {
      left = other.left;
      right = other.right;
    }

    size_t length() {
      if (left > right) {
        return 0;
      }
      return right - left + 1;
    }

    Interval overlap(const Interval& other) {
      int s_left = 0;
      // Если конец первого меньше начала второго, то пересечения нет.
      if (right < other.left) {
        return {0, -1};
      }
      // Иначе находим пересечение.
      if (left >= other.left) {
        s_left = left;
      } else {
        s_left = other.left;
      }
      int s_right = 0;
      if (right <= other.right) {
        s_right = right;
      } else {
        s_right = other.right;
      }
      return {s_left, s_right};
    }

    bool compare(const Interval& other) {
    // Сравнение для сортировки.
    return left < other.left || (left == other.left && right < other.right);
    }

    void print() {
      std::cout << left << " " << right << "\n";
    }
};

// Слияние двух векторов интервалов по известному алгоритму.
void merge(std::vector<Interval>& intervals, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Interval> L(n1);
    std::vector<Interval> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = intervals[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = intervals[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].compare(R[j])) {
            intervals[k] = L[i];
            i++;
        } else {
            intervals[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        intervals[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        intervals[k] = R[j];
        j++;
        k++;
    }
}

// Функция сортировки слиянием.
void mergeSort(std::vector<Interval>& intervals, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(intervals, left, mid);
        mergeSort(intervals, mid + 1, right);
        merge(intervals, left, mid, right);
    }
}

// Нахождение максимума.
Interval FindMax(std::vector<Interval>& intervals, int left, int right) {
  if (left >= right) {
    return {0, -1};
  }
  int mid = left + (right - left) / 2;
  // Тоже методом разделяй-и-властвуй.
  auto leftResult = FindMax(intervals, left, mid);
  auto rightResult = FindMax(intervals, mid + 1, right);
  Interval maxInterval = {0, -1};

  auto currentInterval = intervals[left];
  // После нахождения левой и правой границы, нужно пройти по всему отсортированному вектору еще раз.
  // Найти здесь свой максимум (чтобы исключить случаи, когда по разные стороны нужные интервалы).
  // И потом сравнить наши три полученных интервала.
  for (int i = left + 1; i <= right; ++i) {
      Interval overlapp = Interval(currentInterval.overlap(intervals[i]));
      if (overlapp.length() > maxInterval.length()) {
        maxInterval = Interval(overlapp);
      }
      if (intervals[i].right > currentInterval.right) {
          currentInterval = intervals[i];
      }
  }
  if (leftResult.length() > rightResult.length() && leftResult.length() > maxInterval.length()) {
    return leftResult;
  } else if (rightResult.length() > leftResult.length() && rightResult.length() > maxInterval.length()) {
    return rightResult;
  } else {
    return maxInterval;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<Interval> intervals(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> intervals[i].left >> intervals[i].right;
  }

  mergeSort(intervals, 0, intervals.size() - 1);

  Interval max_interval = Interval(FindMax(intervals, 0, intervals.size() - 1));
  if (max_interval.length() == 0) {
    std::cout << max_interval.length() << "\n";
  } else {
    std::cout << max_interval.length() << "\n";
    std::cout << max_interval.left << " " << max_interval.right << "\n";
  }
}
