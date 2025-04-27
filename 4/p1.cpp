#include <iostream>

// Узел дерева.
struct Node {
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// Методы для дерева.
struct BinaryTree {
  // Возвращает высоту.
  int height(Node* tr) {
    if (tr == nullptr) {
      return 0;
    }
    return tr->height;
  }

  // Проверка баланса.
  std::pair<bool, int> checkBalance(Node* tr) {
    if (tr == nullptr) {
      return {true, 0};
    }
    // Нужно проверять левое и правое дерево на балансированность.
    std::pair<bool, int> left = checkBalance(tr->left);
    std::pair<bool, int> right = checkBalance(tr->right);

    // Если хоть что-то не выполняется, то несбалансированно.
    bool ans = left.first && right.first && std::abs(left.second - right.second) <= 1;
    int cur_height = std::max(left.second, right.second) + 1;
    return {ans, cur_height};
  }

  // Вставка.
  Node* inssert(Node* tr, int key) {
    // Если пустое дерево, то создаем новое.
    if (tr == nullptr) {
      return new Node(key);
    }
    // Вставка не в пустое.
    if (key < tr->key) {
      tr->left = inssert(tr->left, key);
    }
    else if (key > tr->key) {
      tr->right = inssert(tr->right, key);
    }
    // Изменение высоты.
    tr->height = std::max(height(tr->left), height(tr->right)) + 1;
    return tr;
  }
};

int main() {
  Node* tree = nullptr;
  BinaryTree methods = BinaryTree();
  int n;
  std::cin >> n;
  while (n != 0) {
    tree = methods.inssert(tree, n);
    std::cin >> n;
  }
  if (methods.checkBalance(tree).first) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}
