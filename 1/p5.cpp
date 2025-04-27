#include <iostream>
#include <queue>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Отключить синхронизацию между iostream и stdio.
  std::cin.tie(nullptr);        // Отключить синхронизацию между std::cin и std::cout.
  int n;
  std::cin >> n;
  // Очереди бойцов. Чтоб вставка в середину была быстрой, заведем две очереди, которые делят исходную пополам.
  std::deque<int> fighters_1;
  std::deque<int> fighters_2;
  // Строка с запросом.
  std::string request;
  // Номер бойца.
  int fighter;
  for (int i = 0; i < n; ++i) {
    std::cin >> request;
    if (request == "+") {
      std::cin >> fighter;
      fighters_2.push_back(fighter);
    } else if (request == "*") {
      std::cin >> fighter;
      // Вставляем столпа в середину (в начало второй очереди).
      fighters_2.push_front(fighter);
    } else {
      std::cout << fighters_1.front() << "\n";
      fighters_1.pop_front();
    }
    // Если в задней очереди скопилось слишком много, то уравниваем.
    while(fighters_1.size() < fighters_2.size()) {
      fighters_1.push_back(fighters_2.front());
      fighters_2.pop_front();
    }
  }
}