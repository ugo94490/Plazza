/*
** EPITECH PROJECT, 2020
** APizza.cpp
** File description:
** APizza.cpp
*/

#include "Core.hpp"

APizza::APizza(APizza::PizzaType pizza, APizza::PizzaSize taille)
{
    type = pizza;
    size = taille;
}

APizza::PizzaType APizza::getType(void)
{
    return (type);
}

APizza::PizzaSize APizza::getSize(void)
{
    return (size);
}

std::string APizza::pack(APizza &pizza)
{
    if (pizza.type == APizza::PizzaType::Americana)
        return ("Americana");
    if (pizza.type == APizza::PizzaType::Fantasia)
        return ("Fantasia");
    if (pizza.type == APizza::PizzaType::Margarita)
        return ("Margarita");
    if (pizza.type == APizza::PizzaType::Regina)
        return ("Regina");
}

APizza &APizza::unpack(std::string str)
{
    
}