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

class Kitchen
{
    public:
        Kitchen(int multiplier, int nb_cook, int time);
        ~Kitchen();
        void refill_kitchen();
        void loop();
        int getStatus();
        std::vector<std::shared_ptr<Cook>> create_cook(int nb_cook);
    private:
        int nb_cook;
        int refill;
        std::vector<std::shared_ptr<Cook>> cook;
        std::vector<APizza> pizza;
    protected:
        int multiplier;
        std::map<APizza::PizzaIngredient, int> ingredient;
};