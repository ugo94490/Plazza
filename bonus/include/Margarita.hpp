/*
** EPITECH PROJECT, 2020
** Margarita.hpp
** File description:
** Margarita.hpp
*/

#pragma once

#include "APizza.hpp"

class Margarit : public APizza
{
    public:
        Margarit(APizza::PizzaType, APizza::PizzaSize);
        virtual ~Margarit();
};