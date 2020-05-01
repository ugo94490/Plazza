/*
** EPITECH PROJECT, 2020
** Cook.cpp
** File description:
** Cook.cpp
*/

#include <unistd.h>
#include "Cook.hpp"

Cook::Cook(APizza &pizza, int multiplier)
{
    usleep((pizza.getTime() * multiplier) * 1000000);
}

Cook::~Cook()
{
}