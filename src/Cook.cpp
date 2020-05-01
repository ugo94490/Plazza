/*
** EPITECH PROJECT, 2020
** Cook.cpp
** File description:
** Cook.cpp
*/

#include <unistd.h>
#include <iostream>
#include "APizza.hpp"
#include "Cook.hpp"

Cook::Cook(APizza &pizza, int multiplier)
{
    usleep((pizza.getTime() * multiplier) * 1000000);
    std::cout << APizza::pack(pizza) << std::endl;
}

Cook::~Cook()
{
}