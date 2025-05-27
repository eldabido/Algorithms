#include <iostream>
#include <vector>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node *next;

    Node(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:

    HashTable(): tableSize(100), num(0), coef(0.5), hasher(Func()) {
      table.resize(tableSize, nullptr);
    }

    HashTable(Func func) : tableSize(100), num(0), coef(0.5), hasher(func) {
      table.resize(tableSize, nullptr);
    }

    HashTable(size_t tableSize, double coeff, Func func = std::hash<KeyType>()): tableSize(tableSize), num(0), coef(coeff), hasher(func) {
      if (coeff <= 0 || coeff > 1) {
        coef = 0.5;
      }
      table.resize(tableSize, nullptr);
    }

    ~HashTable() {
      clear();
    }

    void clear() {
      // Проходим по вектору нодов и поочерёдно удаляем.
      for (size_t i = 0; i < tableSize; ++i) {
        Node<KeyType, ValueType>* cur = table[i];
        while (cur != nullptr) {
          Node<KeyType, ValueType>* temp = cur;
          cur = cur->next;
          delete temp;
        }
        table[i] = nullptr;
      }
      num = 0;
    }

    void insert(KeyType key, ValueType value) {
      // Высчитываем индекс.
      size_t index = hasher(key) % tableSize;
      Node<KeyType, ValueType>* cur = table[index];
      // Вставляем.
      while (cur != nullptr) {
        if (cur->key == key) {
          cur->value = value;
          return;
        }
        cur = cur->next;
      }
      // Если не найден.
      Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(key, value);
      newNode->next = table[index];
      table[index] = newNode;
      ++num;
      // Превышение коэффа.
      if (static_cast<double>(num) / tableSize > coef) {
        rehash();
      }
    }

    void rehash() {
      // Новый размер.
      size_t newSize = tableSize * 2;
      std::vector<Node<KeyType, ValueType>*> newTable(newSize, nullptr);
      // Перехеширование.
      for (size_t i = 0; i < tableSize; ++i) {
        Node<KeyType, ValueType>* cur = table[i];
        while (cur != nullptr) {
          Node<KeyType, ValueType>* next = cur->next;
          size_t newIndex = hasher(cur->key) % newSize;
          cur->next = newTable[newIndex];
          newTable[newIndex] = cur;
          cur = next;
        }
      }
      table = newTable;
      tableSize = newSize;
    }
    ValueType *find(KeyType key) {
      // Высчитываем и по циклу ищем.
      size_t index = hasher(key) % tableSize;
      Node<KeyType, ValueType>* cur = table[index];
      while (cur != nullptr) {
        if (cur->key == key) {
          return &(cur->value);
        }
        cur = cur->next;
      }
      return nullptr;
    }
    void erase(KeyType key) {
      // Вычисляем.
      size_t index = hasher(key) % tableSize;
      // Поиск элемента и проход.
      Node<KeyType, ValueType>* cur = table[index];
      Node<KeyType, ValueType>* prev = nullptr;
      while (cur != nullptr) {
        if (cur->key == key) {
            // Удаляем.
          if (prev == nullptr) {
            table[index] = cur->next;
          } else {
            prev->next = cur->next;
          }
          delete cur;
          --num;
          return;
        }
        prev = cur;
        cur = cur->next;
      }
    }

    Node<KeyType, ValueType> &operator[](uint64_t hash) {
      if (hash >= tableSize) {
        throw std::out_of_range("out of range");
    }
    if (table[hash] == nullptr) {
        throw std::runtime_error("RE");
    }
    return *table[hash];
    }

    Node<KeyType, ValueType> at(uint64_t hash) {
    if (hash >= tableSize) {
        throw std::out_of_range("out of range");
    }
    if (table[hash] == nullptr) {
        throw std::runtime_error("RE");
    }
    return *table[hash];
    }

    int size() const {
      return num;
    };
    int capacity() const {
      return tableSize;
    };

    // Размер таблицы.
    size_t tableSize;
    // Кол-во.
    size_t num;
    // Коэф.
    double coef;
    // Функция-хэшер.
    Func hasher;
    // Вектор нодов - таблица.
    std::vector<Node<KeyType, ValueType>*> table;
};
