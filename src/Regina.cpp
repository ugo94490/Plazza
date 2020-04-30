/*
** EPITECH PROJECT, 2020
** Regina.cpp
** File description:
** Regina.cpp
*/

#include "Core.hpp"
#include "Regina.hpp"

Regin::Regin(APizza::PizzaType pizza, APizza::PizzaSize taille)
{
    type = pizza;
    size = taille;
    time = 2;
    ingredient.push_back(APizza::PizzaIngredient::Doe);
    ingredient.push_back(APizza::PizzaIngredient::Tomato);
    ingredient.push_back(APizza::PizzaIngredient::Gruyere);
    ingredient.push_back(APizza::PizzaIngredient::Ham);
    ingredient.push_back(APizza::PizzaIngredient::Mushrooms);
}

Regin::~Regin()
{
}