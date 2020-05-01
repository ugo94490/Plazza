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
#include "Cook.hpp"
#include <unistd.h>

class Kitchen {
    public:
        Kitchen(int multiplier, int nb_cook, int time);
        ~Kitchen();
        void refill_kitchen();
        void loop();
        int getStatus();
        int create_cook(std::shared_ptr<APizza> pizza, int multiplier);
        void clean_cook();

    private:
        int nb_cook;
        int refill;
        std::vector<std::shared_ptr<Cook>> cook;
        std::vector<std::shared_ptr<APizza>> pizza;
    protected:
        int multiplier;
        std::map<APizza::PizzaIngredient, int> ingredient;
};