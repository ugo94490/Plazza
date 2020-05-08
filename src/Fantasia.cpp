/*
** EPITECH PROJECT, 2020
** Fantasia.cpp
** File description:
** Fantasia.cpp
*/

#include "Core.hpp"
#include "Fantasia.hpp"

Fantasi::Fantasi(APizza::PizzaType pizza, APizza::PizzaSize taille)
{
    type = pizza;
    size = taille;
    time = 4;
    ingredient.push_back(APizza::PizzaIngredient::Doe);
    ingredient.push_back(APizza::PizzaIngredient::Tomato);
    ingredient.push_back(APizza::PizzaIngredient::Eggplant);
    ingredient.push_back(APizza::PizzaIngredient::Goat_Cheese);
    ingredient.push_back(APizza::PizzaIngredient::Chief_Love);
}

Fantasi::~Fantasi()
{
}