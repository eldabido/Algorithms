#include <iostream>
#include <string>
#include <stack>
#include <queue>

int main() {
  // В этой задаче удобно представить тупик как стек, а поезда как очередь.
  std::queue<int> trains;
  std::stack<int> deadlock;
  int n;
  std::cin >> n;
  // Переменная нужного вагона.
  int need_train = 1;
  // Переменная количества поездов, заводимых в тупик.
  int num_of_trains = 0;
  // Для хранения номера рассматриваемого вагона.
  int tmp;
  std::string output = ""; // строка для вывода.
  for (int i = 0; i < n; i++) {
    std::cin >> tmp;
    trains.push(tmp);
  }
  // Получается, заводим вагоны в тупик, как только видим нужный, то выводим его в путь 2.
  // Если идут несколько подряд нужных, то выводим, пока не встретим нужный.
  while (!trains.empty()) {
    tmp = trains.front(); // Первый вагон заезжает в тупик
    trains.pop();
    deadlock.push(tmp);
    ++num_of_trains;
    if (tmp == need_train) {
      output += "1 " + std::to_string(num_of_trains) + "\n";
      num_of_trains = 0;
      while (deadlock.top() == need_train) {
        deadlock.pop();
        ++num_of_trains;
        if (need_train == n) { 
          break;
        }
        ++need_train;
        if (deadlock.empty()) {
          break;
        }
      }
      output += "2 " + std::to_string(num_of_trains) + "\n";
      num_of_trains = 0;
    }
  }
  if (deadlock.empty()) {
    std::cout << output;
  } else {
    std::cout << "0";
  }
}
