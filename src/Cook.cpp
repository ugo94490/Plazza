/*
** EPITECH PROJECT, 2020
** Cook.cpp
** File description:
** Cook.cpp
*/

#include <unistd.h>
#include <iostream>
#include "APizza.hpp"
#include "Cook.hpp"


typedef struct arg_s {
    std::shared_ptr<APizza> pizza;
    int multiplier;
} arg_t;

static void sleep_cooker(arg_t *arg) {
    usleep((arg->pizza->getTime() * arg->multiplier) * 1000000);
    std::cout << APizza::pack(arg->pizza) << std::endl;
}

Cook::Cook(std::shared_ptr<APizza> pizza, int multiplier) {
    this->start_thread(pizza,multiplier);
}

void Cook::start_thread(std::shared_ptr<APizza> pizza, int multiplier) {
    this->status = 1;
    arg_t *arg = new arg_t();
    arg->pizza = pizza;
    arg->multiplier = multiplier;
    this->_thread = std::thread(sleep_cooker, arg);
    this->status = 2;
}

int Cook::get_status() const{
    if (this->status == 0)
        return 0;
    if (this->status == 1)
        return 1;
    if (this->status == 2)
        return 2;
    return -1;
}

void Cook::wait_thread() {
    this->_thread.join();
    this->status = 0;
}
