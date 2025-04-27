#include <iostream>
#include <vector>
#include <stdexcept>
#include "list.h"

// Конструкторы.

List::List(): head(nullptr), tail(nullptr), _size(0) {} 

// В этих двух просто проходим циклом и делаем push_back.

List::List(const List& other) {
    tail = nullptr;
    head = nullptr;
    _size = 0;
    for (Node* elem = other.head; elem != nullptr; elem = elem->next) {
        push_back(elem->value);
    }
}

List::List(std::vector<int> array) {
    tail = nullptr;
    head = nullptr;
    _size = 0;
    for (const auto& elem : array) {
        push_back(elem);
    }
}

// Деструктор.

List::~List() {
    clear();
}

// Возврат начала и конца очереди.

int List::front() {
    if (head != nullptr) {
        return head->value;
    } else {
        return 0;
    }
}


int List::back() {
    if (tail != nullptr) {
        return tail->value;
    } else {
        return 0;
    }
}

// Вставки в начало и конец.

void List::push_back(int value) {
    // Создаем узел.
    Node* elem = new Node(value);
    if (tail != nullptr) {
        // Если не пуст список, то вставляем.
        tail->next = elem;
        elem->prev = tail;
        tail = elem;
    } else {
        // Если пустой.
        head = elem;
        tail = elem;
    }
    ++_size;
}

void List::push_front(int value) {
    // Аналогично push_back, только с head.
    Node* elem = new Node(value);
    if (head != nullptr) {
        elem->next = head;
        head->prev = elem;
        head = elem;
    } else {
        // Если пустой.
        head = elem;
        tail = elem;
    }
    ++_size;
}

// Вставка в pos. 
void List::insert(Node* pos, int value) {
    // Если nullptr или pos вне листа, то кидаем ошибку.
    if (pos == nullptr) {
         throw std::runtime_error("nullptr!");
    }
    Node* cur = head;
    bool result = false;

    while (cur != nullptr) {
        if (cur == pos) {
            result = true;
            break;
        }
        cur = cur->next;
    }

    if (!result) {
        throw std::runtime_error("Pos is not in list");
    }
    // Если все хорошо, то создаем узел и вставляем.
    Node* elem = new Node(value);
    elem->prev = pos;
    elem->next = pos->next;
    if (pos->prev != nullptr) {
        pos->next->prev = elem;
    // Начало.
    } else {
        tail = elem;
    }
    pos->next = elem;
    ++_size;
}

// Удаление начала или конца. Создаем узел del, продвигаем head, и удаляем del.

void List::pop_front() {
    if (head != nullptr) {
        Node* del = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete del;
        --_size;
    }
}

void List::pop_back() {
    if (tail != nullptr) {
        Node* del = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete del;
        --_size;
    }
}

// Удаление с позиции pos.

void List::erase(Node* pos) {
    if (pos != nullptr) {
        if (pos->prev != nullptr) {
            // Делать pos-prev-next нужно, чтоб не терять ссылку на pos для delete.
            pos->prev->next = pos->next;
        } else {
            head = pos->next;
        }
        if (pos->next != nullptr) {
            pos->next->prev = pos->prev;
        } else {
            tail = pos->prev;
        }
        delete pos;
        --_size;
    } else {
        throw std::runtime_error("Incorrect position!");
    }
}

// Метод clear для очистки.

void List::clear() {
    while (tail != nullptr) {
        pop_back();
    }
}

// Метод reverse, переворачивающий список.

void List::reverse() {
    Node* walker = head;
    Node* tmp = nullptr;
    while (walker != nullptr) {
        tmp = walker->prev;
        walker->prev = walker->next;
        walker->next = tmp;
        walker = walker->prev;
    }

    if (tmp != nullptr) {
        tail = head;
        head = tmp->prev;
    }
}

// Метод remove_duplicates, удаляющий одинаковые элементы.

void List::remove_duplicates() {
    // Просто проходим по списку двумя Node* и удаляем, если один равен другому.
    Node* walker = head;
    while (walker != nullptr) {
        Node* sec_walker = walker->next;
        while (sec_walker != nullptr) {
            if (sec_walker->value == walker->value) {
                Node* del = sec_walker;
                sec_walker = sec_walker->next;
                erase(del);
            } else {
                sec_walker = sec_walker->next;
            }
        }
        walker = walker->next;
    }
}

// Метод replace - замена старого значения на новое.

void List::replace(int old_value, int new_value) {
    // Просто проходим, если встретили старое, то меняем.
    Node* walker = head;
    while (walker != nullptr) {
        if (walker->value == old_value) {
            walker->value = new_value;
        }
        walker = walker->next;
    }
}

// Метод merge - слияние двух списков.

void List::merge(const List& other) {
    // Проходим по второму списку и делаем push_back по его элементам.
    for (Node* elem = other.head; elem != nullptr; elem = elem->next) {
        push_back(elem->value);
    }
}

// Метод check_cycle - проверка на цикличность списка.

bool List::check_cycle() const {
    // Делаем методом кролика и черепашки, как на семинаре.
    Node *turtle = head;
    Node *rabbit = head;
    while (rabbit != nullptr && rabbit->next != nullptr) {
        turtle = turtle->next;
        rabbit = rabbit->next->next;
        if (turtle == rabbit) {
            return true;
        }
    }
    return false;
}

// Метод size - возврат размера списка.

size_t List::size() const {
    return _size;
}

// Метод empty - проверка на пустоту.

bool List::empty() const{
    return _size == 0;
}

// Метод copy - копирование переданного списка в наш.

void List::copy(const List& other) {
    // Сначала чистим наш.
    clear();
    // Если передали пустой, то просто инициализируем пустотой.
    if (other.head == nullptr) {
        head = nullptr;
        tail = nullptr;
        _size = 0;
        return;
    }
    // Создаем новые узлы, и проводим копирование.
    Node* elem = other.head;
    while (elem != nullptr) {
        push_back(elem->value);
        elem =  elem->next;
    }
    _size = other._size;
}

int main() {
    std::vector<int> v(5);
    for (int i = 0; i < 5; ++i) {
        v[i] = i;
    }
    List l = List(v);
    l.insert(l.tail, 10);
    std::cout << l.front();

}