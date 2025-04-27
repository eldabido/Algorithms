#include "avl_tree.h"
#include <iostream>

Node::Node(int value): value(value), left(nullptr), right(nullptr), height(1) {}

Node::~Node() {
  delete(left);
  delete(right);
}

AVLTree::AVLTree(): root_(nullptr), size_(0) {}

AVLTree::AVLTree(int value) {
  root_ = nullptr;
  size_ = 0;
  insert(value);
}

int AVLTree::getHeight() {
  if (root_ == nullptr) {
    return 0;
  }
  return root_->height;
}

void AVLTree::insert(int value) {
  // Если элемента нет, то вставляем.
  if (!find(value)) {
    root_ = insertNode(root_, value);
    ++size_;
  }
}

void AVLTree::erase(int value) {
  // Если элемент есть, то удаляем.
  if (find(value)) {
    root_ = removeNode(root_, value);
    --size_;
  }
}

int* AVLTree::find(int value) {
  Node* f = findNode(root_, value);
  if (f)
    return &f->value;
  return nullptr;

}

int *AVLTree::traversal() {
  // Массив итоговый.
  int* array_ = new int[size_];
  int index = 0;
  traversalInternal(root_, array_, &index);
  return array_;
}

int *AVLTree::lowerBound(int value) {
  Node* result = lowerBoundInternal(root_, value);
  return result ? &result->value : nullptr;
}

bool AVLTree::empty() {
  return size_ == 0;
}

Node *AVLTree::getRoot() {
  return root_;
}

int AVLTree::getSize() {
  return size_;
}

AVLTree::~AVLTree() {
  delete(root_);
}

int AVLTree::getNodeHeight(Node *node) {
  if (node == nullptr)
    return 0;
  return node->height;
}

int AVLTree::balanceFactor(Node *node) {
  if (node == nullptr)
    return 0;
  return getNodeHeight(node->left) - getNodeHeight(node->right);
}

void AVLTree::balanceHeight(Node *node) {
  node->height = std::max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
}

Node *AVLTree::rotateRight(Node *node) {
  Node* newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;
  balanceHeight(node);
  balanceHeight(newRoot);
  return newRoot;
}

Node *AVLTree::rotateLeft(Node *node) {
  Node* newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;
  balanceHeight(node);
  balanceHeight(newRoot);
  return newRoot;
}

Node *AVLTree::insertNode(Node *node, int value) {
  if (node == nullptr)
    return new Node(value);

  if (value < node->value) {
    node->left = insertNode(node->left, value);
  } else if (value > node->value) {
    node->right = insertNode(node->right, value);
  } else {
    return node;
  }
   return balanceNode(node);
}

Node *AVLTree::findMinNode(Node *node) {
  // Идем влево максимально.
  if(node->left == nullptr)
    return node;
  if (node != nullptr) {
    return findMinNode(node->left);
  }
  return node;
}

Node *AVLTree::removeMinNode(Node *node) {
  if( node->left == 0)
		return node->right;
  // Идем влево максимально.
	node->left = removeMinNode(node->left);
	return balanceNode(node);
}

Node *AVLTree::balanceNode(Node *node) {
  if (node == nullptr) {
    return node;
  }
  balanceHeight(node);
  // Если высота вышла за пределы 1, 0, -1, то балансируем.
	if(balanceFactor(node) < -1) {
		if(balanceFactor(node->right) > 0)
			node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	if(balanceFactor(node) > 1) {
		if(balanceFactor(node->left) < 0)
			node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	return node;
}

Node *AVLTree::removeNode(Node *node, int value) {
  if (!node)
    return nullptr;
  if (value < node->value)
    node->left = removeNode(node->left, value);
  else if (value > node->value)
    node->right = removeNode(node->right, value);
  else {
      Node* temp1 = node->left;
      Node* temp2 = node->right;
      delete node;
      if (!temp2) {
        return temp1;
      }
      Node* min_ = findMinNode(temp2);
      min_->right = removeMinNode(temp2);
      min_->left = temp1;
      return balanceNode(min_);
  }
  return balanceNode(node);
}

Node *AVLTree::findNode(Node *node, int value) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->value == value) {
    return node;
  }
  if (value < node->value) {
    return findNode(node->left, value);
  }
  return findNode(node->right, value);
}

void AVLTree::traversalInternal(Node *node, int *arr, int *index) {
  if (node) {
    // Сначала идем влево максимально, и оттуда начинаем собирать массив.
    traversalInternal(node->left, arr, index);
    arr[(*index)++] = node->value;
    traversalInternal(node->right, arr, index);
  }
}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {
  if (!current)
    return nullptr;
  if (current->value > value) {
    Node* leftResult = lowerBoundInternal(current->left, value);
    return leftResult ? leftResult : current;
  } else if (current->value == value) {
    return current;
  } else {
    return lowerBoundInternal(current->right, value);
  }
}

int main() {
  AVLTree avl = AVLTree();
  avl.insert(6);
  avl.insert(423);
  avl.insert(423);
  avl.erase(423);
  avl.erase(42);
  avl.erase(42);
  avl.erase(42);
  avl.erase(42);
  avl.erase(42);
  avl.erase(42);
  avl.find(6);
  avl.insert(-2);
  int* a = avl.lowerBound(-1);
  std::cout << " " << avl.getSize() << " " <<"\n";
}

