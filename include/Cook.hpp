/*
** EPITECH PROJECT, 2020
** Cook.hpp
** File description:
** Cook.hpp
*/

#pragma once

#include "Kitchen.hpp"
#include "APizza.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

class Cook {
    private:
        int id = 0;
        int status = -1;
        std::thread _thread;
        std::condition_variable cooker_locker;
        std::mutex cooker_mutex;
        std::mutex tmp_pizza_mutex;
        std::shared_ptr<APizza> tmp_pizza = nullptr;
        float cook_mutiplier;

    public:
        Cook(float multiplier, int id);
        ~Cook();
        int get_status() const;
        void unlock_cooker();
        void get_pizzou(std::shared_ptr<APizza> pizza);
        void loop();
};