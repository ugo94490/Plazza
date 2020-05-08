/*
** EPITECH PROJECT, 2020
** APizza.cpp
** File description:
** APizza.cpp
*/

#include <iostream>
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

std::vector<APizza::PizzaIngredient> APizza::getIngredients()
{
    return (ingredient);
}


int APizza::getTime(void)
{
    return (time);
}

std::string APizza::pack(std::shared_ptr<APizza> pizza)
{
    std::string str = "Pizza ";
    if (pizza->type == APizza::PizzaType::Americana)
        str = str + "Americana";
    if (pizza->type == APizza::PizzaType::Fantasia)
        str = str + "Fantasia";
    if (pizza->type == APizza::PizzaType::Margarita)
        str = str + "Margarita";
    if (pizza->type == APizza::PizzaType::Regina)
        str = str + "Regina";
    if (pizza->size == APizza::PizzaSize::S)
        str = str + " S";
    if (pizza->size == APizza::PizzaSize::M)
        str = str + " M";
    if (pizza->size == APizza::PizzaSize::L)
        str = str + " L";
    if (pizza->size == APizza::PizzaSize::XL)
        str = str + " XL";
    if (pizza->size == APizza::PizzaSize::XXL)
        str = str + " XXL";
    return (str);
}

std::shared_ptr<APizza> APizza::unpack(std::string str)
{
    std::string tmp = str.substr(6);
    std::string name;
    std::string size;
    std::vector<std::string> arg;
    std::shared_ptr<APizza> ptr;
    int space = 0;

    space = tmp.find(' ');
    name = tmp.substr(0, space);
    size = tmp.substr(space + 1);
    arg.push_back(name);
    arg.push_back(size);
    ptr = Core::fill_pizza(arg);
    return (ptr);
}