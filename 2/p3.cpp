#include <iostream>
#include <vector>

// Матрицу представим как вектор векторов.
using Matrix = std::vector<std::vector<long long>>;

// Обычное умножение матриц для маленьких случаев.
Matrix common_multiply(Matrix A, Matrix B, size_t n) {

	Matrix C(n, std::vector<long long>(n));
  long long sum = 0;
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			for (size_t k = 0; k < n; ++k) {
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
			sum = 0;
		}
	}
	return C;
}

// Разность матриц.
Matrix sub(Matrix A, Matrix B, size_t n) {
  Matrix C(n, std::vector<long long>(n));

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

// Сумма матриц.
Matrix sum(Matrix A, Matrix B, size_t n) {
  Matrix C(n, std::vector<long long>(n));

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

// Основная функция, вычисляющая произведение матриц с помощью метода Штрассена.
Matrix strassen(Matrix A, Matrix B, size_t n) {
  // Если n < 128, то применяем простое умножение.
  if (n < 128) {
    return common_multiply(A, B, n);
  }

  // Здесь сам метод Штрассена, делим матрицы на 4 части и в соответствии с алгоритмом оперируем.
  Matrix C(n, std::vector<long long>(n));
  size_t k = n / 2;

  Matrix A11(k, std::vector<long long>(k));
  Matrix A12(k, std::vector<long long>(k));
  Matrix A21(k, std::vector<long long>(k));
  Matrix A22(k, std::vector<long long>(k));
  Matrix B11(k, std::vector<long long>(k));
  Matrix B12(k, std::vector<long long>(k));
  Matrix B21(k, std::vector<long long>(k));
  Matrix B22(k, std::vector<long long>(k));

  for (size_t i = 0; i < k; ++i) {
    for (size_t j = 0; j < k; ++j) {
      A11[i][j] = A[i][j];
			A12[i][j] = A[i][k + j];
			A21[i][j] = A[k + i][j];
			A22[i][j] = A[k + i][k + j];
			B11[i][j] = B[i][j];
			B12[i][j] = B[i][k + j];
			B21[i][j] = B[k + i][j];
			B22[i][j] = B[k + i][k + j];
    }
  }

  Matrix S1 = sub(B12, B22, k);
	Matrix S2 = sum(A11, A12, k);
	Matrix S3 = sum(A21, A22, k);
	Matrix S4 = sub(B21, B11, k);
	Matrix S5 = sum(A11, A22, k);
	Matrix S6 = sum(B11, B22, k);
	Matrix S7 = sub(A12, A22, k);
	Matrix S8 = sum(B21, B22, k);
	Matrix S9 = sub(A11, A21, k);
	Matrix S10 = sum(B11, B12, k);

	Matrix P1 = strassen(A11, S1, k);
	Matrix P2 = strassen(S2, B22, k);
	Matrix P3 = strassen(S3, B11, k);
	Matrix P4 = strassen(A22, S4, k);
	Matrix P5 = strassen(S5, S6, k);
	Matrix P6 = strassen(S7, S8, k);
	Matrix P7 = strassen(S9, S10, k);

	Matrix C11 = sub(sum(sum(P5, P4, k), P6, k), P2, k);
	Matrix C12 = sum(P1, P2, k);
	Matrix C21 = sum(P3, P4, k);
  Matrix C22 = sub(sub(sum(P5, P1, k), P3, k), P7, k);

  // Собираем матрицу из четырех частей.
  for (size_t i = 0; i < k; ++i) {
		for (size_t j = 0; j < k; ++j) {
			C[i][j] = C11[i][j];
			C[i][j + k] = C12[i][j];
			C[k + i][j] = C21[i][j];
			C[k + i][k + j] = C22[i][j];
		}
	}
	return C;
}

// Вывод матрицы.
void print(Matrix A, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      std::cout << A[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  Matrix A(n,std::vector<long long>(n));
  Matrix B(n,std::vector<long long>(n));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      std::cin >> A[i][j];
    }
  }
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      std::cin >> B[i][j];
    }
  }
  print(strassen(A, B, n), n);
}
