/*
** EPITECH PROJECT, 2020
** Cook.hpp
** File description:
** Cook.hpp
*/

#pragma once

#include "APizza.hpp"
#include <thread>
#include <iostream>


typedef struct arg_s {
    std::shared_ptr<APizza> pizza;
    int multiplier;
} arg_t;


class Cook {
    private:

    int status = -1;
    std::thread _thread;
    
    
    public:
        Cook(std::shared_ptr<APizza> pizza, int multiplier);
        ~Cook() = default;
        int get_status() const;
        void wait_thread();
        void start_thread(std::shared_ptr<APizza> pizza, int multiplier);
};