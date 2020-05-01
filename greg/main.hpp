/*
** EPITECH PROJECT, 2020
** bootstrap_plazza
** File description:
** main
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <iterator>
#include <unistd.h>

typedef struct stock_s {
  int stock = 0;
  std::mutex mtx;
} stock_t;


class Threads {
    private:
      int status = 2;
      std::thread _thread;

    public:
      int get_status() const;
      void wait_thread();
      void start_thread(void (*fct)(stock_t *stock), stock_t *value);       //* genereciter obtenable sur les parametre de la fonction prise avec le pointeur
      Threads(void (*fct)(stock_t *stock), stock_t *value);
      ~Threads() = default;
};

Threads::Threads(void (*fct)(stock_t *stock), stock_t *value) {
    start_thread(fct,value);
}


int Threads::get_status() const{
  if (this->status == 0) {
    return 0;
  }
  if (this->status == 1) {
    return 1;
  }
  if (this->status == 2) {
    return 2;
  }
  return -1;
}

void Threads::start_thread(void (*fct)(stock_t *stock), stock_t *value) {
  this->status = 1;
  this->_thread = std::thread(fct, value);
  this->status = 2;
}

void Threads::wait_thread() {
  this->_thread.join();
  this->status = 0;
}


#endif /* !MAIN_HPP_ */
