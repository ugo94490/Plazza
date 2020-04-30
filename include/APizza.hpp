/*
** EPITECH PROJECT, 2020
** Pizza.hpp
** File description:
** Pizza.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <memory>

typedef struct pizza_s
{
    int type;
    int size;
    int nb;
} pizza_t;

class APizza
{
    public:
        enum PizzaType
        {
            PizzaError = 0,
            Regina = 1,
            Margarita = 2,
            Americana = 4,
            Fantasia = 8
        };

        enum PizzaSize
        {
            SizeError = 0,
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };

        enum PizzaIngredient
        {
            Doe = 0,
            Tomato = 1,
            Gruyere = 2,
            Ham = 3,
            Mushrooms = 4,
            Steak = 5,
            Eggplant = 6,
            Goat_Cheese = 7,
            Chief_Love = 8
        };
        APizza() = default;
        APizza(APizza::PizzaType, APizza::PizzaSize);
        virtual ~APizza() = 0;
        APizza::PizzaType getType(void);
        APizza::PizzaSize getSize(void);
        std::string pack(APizza &);
        std::shared_ptr<APizza> unpack(std::string);

    protected:
        APizza::PizzaType type;
        APizza::PizzaSize size;
        std::vector<APizza::PizzaIngredient> ingredient;
        int time;
};