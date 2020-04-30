/*
** EPITECH PROJECT, 2020
** Cook.hpp
** File description:
** Cook.hpp
*/

#pragma once

#include <APizza.hpp>

class Cook
{
    public:
        Cook(int multiplier);
        ~Cook();

        bool cooking(APizza &);
    private:
        int multiplier;
};