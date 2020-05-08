/*
** EPITECH PROJECT, 2020
** Fantasia.hpp
** File description:
** Fantasia.hpp
*/

#pragma once

#include "APizza.hpp"

class Fantasi : public APizza
{
    public:
        Fantasi(APizza::PizzaType, APizza::PizzaSize);
        virtual ~Fantasi();
};