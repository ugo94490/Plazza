/*
** EPITECH PROJECT, 2020
** Americana.hpp
** File description:
** Americana.hpp
*/

#pragma once

#include <memory>
#include "APizza.hpp"

class Americana : public APizza
{
    public:
        Americana(APizza::PizzaType, APizza::PizzaSize);
        virtual ~Americana();
};