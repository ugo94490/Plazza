/*
** EPITECH PROJECT, 2020
** Americana.cpp
** File description:
** Americana.cpp
*/

#include "Core.hpp"
#include "Americana.hpp"

Americana::Americana(APizza::PizzaType pizza, APizza::PizzaSize taille)
{
    type = pizza;
    size = taille;
    time = 2;
    ingredient.push_back(APizza::PizzaIngredient::Doe);
    ingredient.push_back(APizza::PizzaIngredient::Tomato);
    ingredient.push_back(APizza::PizzaIngredient::Gruyere);
    ingredient.push_back(APizza::PizzaIngredient::Steak);
}

Americana::~Americana()
{
}