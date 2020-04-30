/*
** EPITECH PROJECT, 2020
** Margarita.hpp
** File description:
** Margarita.hpp
*/

#pragma once

#include "APizza.hpp"

class Margarita : public APizza
{
    public:
        Margarita(APizza::PizzaType, APizza::PizzaSize);
        virtual ~Margarita();
};