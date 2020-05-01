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

APizza::~APizza()
{
}

APizza::PizzaType APizza::getType(void)
{
    return (type);
}

APizza::PizzaSize APizza::getSize(void)
{
    return (size);
}

int APizza::getTime(void)
{
    return (time);
}

std::string APizza::pack(APizza &pizza)
{
    std::string str = "Pizza ";
    if (pizza.type == APizza::PizzaType::Americana)
        str + "Americana";
    if (pizza.type == APizza::PizzaType::Fantasia)
        str + "Fantasia";
    if (pizza.type == APizza::PizzaType::Margarita)
        str + "Margarita";
    if (pizza.type == APizza::PizzaType::Regina)
        str + "Regina";
    if (pizza.size == APizza::PizzaSize::S)
        str + " S";
    if (pizza.size == APizza::PizzaSize::M)
        str + " M";
    if (pizza.size == APizza::PizzaSize::L)
        str + " L";
    if (pizza.size == APizza::PizzaSize::XL)
        str + " XL";
    if (pizza.size == APizza::PizzaSize::XXL)
        str + " XXL";
    return (str);
}

std::shared_ptr<APizza> APizza::unpack(std::string str)
{
    return (nullptr);
}