/*
** EPITECH PROJECT, 2020
** Regina.hpp
** File description:
** Regina.hpp
*/

#pragma once

#include "APizza.hpp"

class Regina : public APizza
{
    public:
        Regina(APizza::PizzaType, APizza::PizzaSize);
        virtual ~Regina();
};