#include <iostream>
#include <stack>
#include <string>

int main() {
  // Стек цифр, это удобный формат хранения, учитывая, что используются вложенные скобки.
  std::stack<int> nums;
  std::string input;
  // Аналогично стек строк, нужен из-за вложенности.
  std::stack<std::string> strs;
  std::getline(std::cin, input);
  int cur_num;
  std::string cur_str = "";
  // В цикле проходим по строке.
  for(char c: input) {
    // Если цифра, то сохраняем в переменную.
    if (isdigit(c)) {
      cur_num = c - '0';
      // Если открытая скобка, то сохраняем нашу цифру и строку и обнуляем их.
    } else if (c == '[') {
      strs.push(cur_str);
      nums.push(cur_num);
      cur_str = "";
      cur_num = 0;
      // Если закрытая, то достаем строку и прибавляем к ней нужное число раз(верх стека) нынешнюю строку.
    } else if (c == ']') {
      std::string tmp = strs.top();
      for (int i = 0; i < nums.top(); ++i) {
        tmp += cur_str;
      }
      // И сохраняем в cur_str итог.
      cur_str = tmp;
      nums.pop();
      strs.pop();
    } else {
      cur_str += c;
    }
  }
  std::cout << cur_str;
}