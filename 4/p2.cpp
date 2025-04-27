#include <iostream>
#include <vector>
#include <string>

struct Node {
  int key;
  std::string color;
  int left;
  int right;
};

struct RedBlackTree {
  int n;
  int root;
  int height;
  std::vector<Node> nodes;

  RedBlackTree(int n, int root, const std::vector<Node>& nodes): n(n), root(root), nodes(nodes) {}

  bool check() {
    height = -1;
    return isBST(root, INT_MIN, INT_MAX) && checkColors(root) && height != -1;
  }

  // Проверка на бинарное дерево поиска.
  bool isBST(int index, int minKey, int maxKey) {
    if (index == -1) return true;
    const Node& node = nodes[index];
    if (node.key <= minKey || node.key >= maxKey) return false;

    return isBST(node.left, minKey, node.key) && isBST(node.right, node.key, maxKey);
  }

  // Получение высоты.
  int getBlackHeight(int index) {
    if (index == -1) return 0;
    const Node& node = nodes[index];
    int leftHeight = getBlackHeight(node.left);
    int rightHeight = getBlackHeight(node.right);
    if (node.color == "B") {
        return std::max(leftHeight, rightHeight) + 1;
    } else {
        return std::max(leftHeight, rightHeight);
    }
  }

  // Проверка верных цветов.
  bool checkColors(int index) {
    if (index == -1) {
      if (height == -1) {
        height = 1; // NIL считается черным.
      }
      return true; // NIL
    }
    const Node& node = nodes[index];

    if (index == root && node.color != "B") return false;

    if (node.color == "R") {
      if ((node.left != -1 && nodes[node.left].color == "R") || (node.right != -1 && nodes[node.right].color == "R")) {
          return false;
      }
    }

    bool leftCheck = checkColors(node.left);
    bool rightCheck = checkColors(node.right);

    int leftBlackHeight = getBlackHeight(node.left);
    int rightBlackHeight = getBlackHeight(node.right);

    if (leftBlackHeight != rightBlackHeight) return false;

    return leftCheck && rightCheck;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  if (n != 0) {
    int root;
    std::cin >> root;
    int number, key;
    std::string left, right, color;
    // Вектор, где храним узлы.
    std::vector<Node> tree(n);
    for (int i = 0; i < n; ++i) {
      // Вычитаем 1, чтоб с нуля начиналось.
      std::cin >> number;
      --number;
      std::cin >> tree[number].key >> left >> right >> tree[number].color;
      // Так как в left и right может быть слово, то принимаем как строку, а потом преобразуем.
      if (left == "null") {
        tree[number].left = -1;
      } else {
        tree[number].left = std::stoi(left) - 1;
      }
      if (right == "null") {
        tree[number].right = -1;
      } else {
        tree[number].right = std::stoi(right) - 1;
      }
    }
    // Проверяем.
    RedBlackTree rbt = RedBlackTree(n, --root, tree);
    if (rbt.check()) {
      std::cout << "YES";
    } else {
      std::cout << "NO";
    }
  } else {
    std::cout << "NO";
  }
}
