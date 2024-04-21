#ifndef LIST_H
#define LIST_H

#include <array>
#include <exception>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <variant>
#include <vector>

/* Задание 2 (30 баллов): Напишите библиотеку, реализующую шаблонный класс для
односвязного списка с поддержкой операций вставки, удаления и поиска заданного
элемента.*/

template <typename T> struct Node {
  T data;
  struct Node *next;
};

template <typename T> class List {
public:
  // private:
  struct Node<T> *head_ = nullptr;
  size_t sz_ = 0;

public:
  List() : head_(nullptr), sz_(0) {}

  List(T &value) : head_((Node<T>){value, nullptr}), sz_(1) {}

  ~List() {
    while (head_) {
      auto tmp = head_->next;
      delete head_;
      head_ = tmp;
    }
  }

  void insert(int pos, T elem) {
    if (pos > sz_) {
      throw std::logic_error("pos more than size of list");
    }

    struct Node<T> *new_node = new Node<T> {
      elem, nullptr
    };
    if (sz_++ == 0) {
      head_ = new_node;
      return;
    }

    if (pos == 0) {
      new_node->next = head_;
      head_ = new_node;
      return;
    }

    size_t i = 0;
    struct Node<T> *prev = head_;
    while (prev->next) {
      prev = prev->next;
      if (++i == pos - 1) {
        // std::cout << "Break!\n";
        break;
      }
    }
    new_node->next = prev->next;
    prev->next = new_node;
    ++sz_;
  }

  void pop(int pos) {
    if (pos >= sz_) {
      throw std::logic_error("pos more than size of list");
    }

    size_t i = 0;
    struct Node<T> *prev = head_;
    struct Node<T> *current = head_;
    while (current->next) {
      prev = current;
      current = current->next;
      if (++i >= pos) {
        break;
      }
    }

    if (pos == 0) {
      delete head_;
      head_ = current;
    } else {
      prev->next = current->next;
      delete current;
    }
    --sz_;
  }

  T *find(int pos) {
    if (pos >= sz_) {
      throw std::logic_error("pos more than size of list");
    }

    size_t i = 0;
    struct Node<T> *current = head_;
    while (current) {
      if (i++ == pos) {
        break;
      }
      current = current->next;
    }
    return &current->data;
  }
};

#endif // LIST_H
