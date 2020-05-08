/*
** EPITECH PROJECT, 2020
** Americana.hpp
** File description:
** Americana.hpp
*/

#pragma once

#include <memory>
#include "APizza.hpp"

class American : public APizza
{
    public:
        American(APizza::PizzaType, APizza::PizzaSize);
        virtual ~American();
};