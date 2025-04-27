#include <iomanip>
#include <iostream>
#include <vector>

// Класс, содержащий информацию об участке пути.
class Ways {
public:
  int time;
  int speed;
  int dist = 0;
};

// Функция считает пройденное расстояние к определенному времени.
double Distance(const std::vector<Ways>& ways, double time) {
  double ans = 0;
  double cur_time = 0;
  for (const auto& way: ways) {
    cur_time += way.time;
    if (time <= cur_time) {
      return ans + (time - cur_time + way.time)  * way.speed;
    } else {
      ans += way.time * way.speed;
    }
  }
  return ans;
}

// Функция показывает, подходит ли нам время.
bool time_is_good(const std::vector<Ways>& ways, double L, double time, double max_time) {
  double dist1 = 0;
  double dist2 = 0;
  int cur_time1 = 0;
  int cur_time2 = time;
  dist1 = Distance(ways, time);
  if (dist1 < L) {
    return false;
  }
  // Смотрим на участки смены скорости поездов, и считаем расстояния между ними в этот момент. Если меньше L, то стоп.
  for (const auto& way: ways) {
    cur_time1 += way.time;
    cur_time2 += way.time;
    if (time < cur_time1) {
      dist1 = Distance(ways, cur_time1);
      dist2 = Distance(ways, cur_time1 - time);
      if (dist1 - dist2 < L) {
        return false;
      }
    }
    if (cur_time2 > time && cur_time2 <= max_time) {
      dist1 = Distance(ways, cur_time2);
      dist2 = Distance(ways, cur_time2 - time);
      if (dist1 - dist2 < L) {
        return false;
      }
    }
  }
  return true;
}

// Основная функция. С помощью бинарного поиска находит нужное время.
double find_min_time(const std::vector<Ways>& ways, int L, double max_time) {
  double left = 0;
  double right = max_time;
  double ans = max_time;
  while (right - left > 1e-3) {
    double mid = (left + right) / 2.0;
    if (time_is_good(ways, L, mid, max_time)) {
      right = mid;
      ans = mid;
    } else {
      left = mid;
    }
  }
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int L, N;
  std::cin >> L >> N;
  std::vector<Ways> ways(N);
  double maximum_time = 0;
  std::cin >> ways[0].time >> ways[0].speed;
  ways[0].dist = ways[0].time * ways[0].speed;
  maximum_time += ways[0].time;
  for (int i = 1; i < N; ++i) {
    std::cin >> ways[i].time >> ways[i].speed;
    maximum_time += ways[i].time;
    ways[i].dist = ways[i - 1].dist + ways[i].time * ways[i].speed;
  }
  double min_time = find_min_time(ways, L, maximum_time);
  std::cout << std::fixed << std::setprecision(3);
  std::cout << min_time;
}
