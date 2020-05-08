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

void Cook::unlock_cooker() {
    this->status = 1;
    this->cooker_locker.notify_one();
}

void Cook::loop() {
    while (1) {
        usleep((this->tmp_pizza->getTime() * this->cook_mutiplier) * 1000000);
        std::cout << "===" << APizza::pack(tmp_pizza) << "==="/* << " ID THREAD ==> "<< this->id*/ << std::endl;
        this->status = 2;
        std::unique_lock<std::mutex> tmp_mutex(this->cooker_mutex);
        this->cooker_locker.wait(tmp_mutex);
    }
}

void Cook::get_pizzou(std::shared_ptr<APizza> pizza) {
    tmp_pizza_mutex.lock();
    this->tmp_pizza = pizza;
    tmp_pizza_mutex.unlock();
}


Cook::Cook(int multiplier, int id) {
    this->id = id;
    this->status = 1;
    this->cook_mutiplier = multiplier;
    this->_thread = std::thread(&Cook::loop, this);
}

Cook::~Cook() {
    this->_thread.join();
    this->_thread.~thread();
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