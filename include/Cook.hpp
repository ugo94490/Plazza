/*
** EPITECH PROJECT, 2020
** Cook.hpp
** File description:
** Cook.hpp
*/

#pragma once

#include "APizza.hpp"

class Cook
{
    public:
        Cook(APizza &pizza, int multiplier);
        ~Cook();
};