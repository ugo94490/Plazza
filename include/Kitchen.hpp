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

class Cook;
class Kitchen {
    public:
        Kitchen() = default;
        Kitchen(int multiplier, int nb_cook, int time);
        ~Kitchen();
        void refill_kitchen();
        void loop();
        int ping_cook();
        void setup_cooking(std::shared_ptr<APizza> tmp_pizza);
        int getStatus();
        bool check_ingredients(std::shared_ptr<APizza> pizza);
        void clean_cook();


    private:
        int nb_cook;
        int actual_cook;
        int refill;
        std::vector<std::shared_ptr<Cook>> cook;
        std::vector<std::shared_ptr<APizza>> pizza;
    protected:
        int multiplier;
        std::map<APizza::PizzaIngredient, int> ingredient;
};