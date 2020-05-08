/*
** EPITECH PROJECT, 2020
** Kitchen.hpp
** File description:
** Kitchen.hpp
*/

#pragma once

#include <vector>
#include <map>
#include "APizza.hpp"
#include <unistd.h>
#include <deque>
#include <mutex>
#include "IPC.hpp"

class Cook;
class Kitchen {
    public:
        Kitchen() = default;
        Kitchen(int multiplier, int nb_cook, int time, int id);
        ~Kitchen();
        void refill_kitchen();
        void loop();
        int ping_cook();
        void setup_cooking(std::shared_ptr<APizza> tmp_pizza);
        int getStatus();
        bool check_ingredients(std::shared_ptr<APizza> pizza);
        void clean_cook();
        void recieveOrder(int cfd);
        std::string readSocket(int cfd);
        void check_pizza(std::string str);
        int count_dot(std::string str);
        void display_ingredient(std::string tmp);

    private:
        int nb_cook;
        int actual_cook;
        int refill;
        int id;
        std::vector<std::shared_ptr<Cook>> cook;
        std::vector<std::shared_ptr<APizza>> pizza;
        int kitchen_fd;
    protected:
        int multiplier;
        std::map<APizza::PizzaIngredient, int> ingredient;
};