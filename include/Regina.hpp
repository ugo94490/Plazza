/*
** EPITECH PROJECT, 2020
** Regina.hpp
** File description:
** Regina.hpp
*/

#pragma once

#include "APizza.hpp"

class Regin : public APizza
{
    public:
        Regin(APizza::PizzaType, APizza::PizzaSize);
        virtual ~Regin();
};