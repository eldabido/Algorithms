#include <algorithm>
#include <cmath>
#include <float.h>
#include <iostream>
#include <vector>

// Максимальное кол-во элементов.
const int MAX_POINTS = 1000000;

// Класс Point - содержит информацию о точках.
class Point {
public:
  long long x;
  long long y;

  Point() {
    x = 0;
    y = 0;
  }
  Point(long long x1, long long y1) {
    x = x1;
    y = y1;
  }

  // Находит квадрат расстояния.
  long long dist(const Point& a){
    return ((*this).x - a.x) * ((*this).x - a.x) + ((*this).y - a.y) * ((*this).y - a.y);
}
};

// Компараторы.
bool compareX(const Point& a, const Point& b) {
  return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
  return a.y < b.y;
}

// Простой способ нахождения расстояния.
double simple_way(std::vector<Point>& points, int start, int finish) {
    double minim = std::numeric_limits<double>::max();
    for (int i = start; i < finish; ++i) {
      for (int j = i + 1; j < finish; ++j) {
        if (points[i].dist(points[j]) < minim) {
          minim = points[i].dist(points[j]);
        }
      }
    }
    return minim;
}

// Нашли координаты по x, здесь по y находим.
double less_than_d(std::vector<Point>& points, int n, double d) {
  std::sort(points.begin(), points.end(), compareY);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n && (points[j].y - points[i].y) < d; ++j) {
      if (points[i].dist(points[j]) < d) {
        d = points[i].dist(points[j]);
      }
    }
  }
  return d;
}

// Основная функция. С помощью разделяй-и-властвуй находим расстояние.
double find_closest(std::vector<Point>& points, int start, int finish) {
  if (finish - start <= 10) {
    return simple_way(points, start, finish);
  }
  int mid = start + (finish - start) / 2;
  Point median = points[mid];
  double dl = find_closest(points, start, mid);
  double dr = find_closest(points, mid, finish);
  double d = std::min(dl, dr);
  std::vector<Point> rang;
  // Сначала по x, потом по y.
  for (int i = start; i < finish; ++i) {
    if (std::abs(points[i].x - median.x) < d) {
      rang.push_back(points[i]);
    }
  }
  return std::min(d, less_than_d(rang, rang.size(), d));
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<Point> points(MAX_POINTS);
  long long n = 0;
  long long x, y;
  while (std::cin >> x >> y) {
    points[n] = Point(x, y);
    ++n;
  }
  std::sort(points.begin(), points.begin() + n, compareX);
  std::cout << (long long)std::sqrt(find_closest(points, 0, n));
}
