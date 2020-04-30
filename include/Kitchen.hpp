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
#include <Cook.hpp>

class Kitchen
{
    public:
        Kitchen(int multiplier, int nb_cook, int time);
        ~Kitchen();
        void refill_kitchen();
        void loop();
        int getStatus();
    private:
        int multiplier;
        int nb_cook;
        int time;
        std::vector<Cook> cook;
        std::vector<APizza> pizza;
        std::map<APizza::PizzaIngredient, int> ingredient;
};