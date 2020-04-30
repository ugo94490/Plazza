/*
** EPITECH PROJECT, 2020
** Fantasia.hpp
** File description:
** Fantasia.hpp
*/

#pragma once

#include "APizza.hpp"

class Fantasia : public APizza
{
    public:
        Fantasia(APizza::PizzaType, APizza::PizzaSize);
        virtual ~Fantasia();
};