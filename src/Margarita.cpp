/*
** EPITECH PROJECT, 2020
** Margarita.cpp
** File description:
** Margarita.cpp
*/

#include "Core.hpp"
#include "Margarita.hpp"

Margarita::Margarita(APizza::PizzaType pizza, APizza::PizzaSize taille)
{
    type = pizza;
    size = taille;
    time = 1;
    ingredient.push_back(APizza::PizzaIngredient::Doe);
    ingredient.push_back(APizza::PizzaIngredient::Tomato);
    ingredient.push_back(APizza::PizzaIngredient::Gruyere);
}

Margarita::~Margarita()
{
}