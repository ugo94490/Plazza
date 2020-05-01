/*
** EPITECH PROJECT, 2020
** Kitchen.cpp
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(int multi, int nb, int temps)
{
    multiplier = multi;
    nb_cook = nb;
    refill = temps;
    loop();
}

Kitchen::~Kitchen()
{
}

std::vector<std::shared_ptr<Cook>> Kitchen::create_cook(int nb_cook)
{
    std::vector<std::shared_ptr<Cook>> ptr;
    return (ptr);
}

void Kitchen::refill_kitchen()
{
}

void Kitchen::loop()
{

}

int Kitchen::getStatus()
{
    return (0);
}