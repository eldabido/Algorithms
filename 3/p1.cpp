#include <iostream>
#include <vector>

void heapify(std::vector<int>& gunmens, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && gunmens[left] > gunmens[largest]) {
    largest = left;
  }

  if (right < n && gunmens[right] > gunmens[largest]) {
    largest = right;
  }

  if (largest != i) {
    std::swap(gunmens[i], gunmens[largest]);
    heapify(gunmens, n, largest);
  }
}

void buildMaxHeap(std::vector<int>& gunmens) {
  size_t n = gunmens.size();
  for (int i = n / 2 - 1; i >= 0; --i) {
    heapify(gunmens, n, i);
  }
}

void heapSort(std::vector<int>& gunmens) {
  size_t n = gunmens.size();
  buildMaxHeap(gunmens);
  for (int i = n - 1; i > 0; --i) {
    std::swap(gunmens[0], gunmens[i]);
    heapify(gunmens, i, 0);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<int> gunmens(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> gunmens[i];
  }
  heapSort(gunmens);

  for (size_t i = 0; i < n; ++i) {
    std::cout << gunmens[i] << " ";
  }
}
