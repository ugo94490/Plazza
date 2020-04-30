/*
** EPITECH PROJECT, 2020
** Core.hpp
** File description:
** Core.hpp
*/

#pragma once

#include "Pizza.hpp"

class Core {
    public:

        enum PizzaType
        {
            Regina = 1,
            Margarita = 2,
            Americana = 4,
            Fantasia = 8
        };

        enum PizzaSize
        {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };

        Core(char **av);
        ~Core();
        void restaurant();
        void parse_pizza(std::string str);
        int count_part(std::string str);
        std::vector<std::string> divide_command(std::string);
        std::vector<pizza_t> create_command(std::vector<std::string> tab_command);
        pizza_t get_pizza(std::string str);
        int getType(std::string str);
        int getSize(std::string str);
        int getNb(std::string str);
        void check_pizza(pizza_t pizza);
        pizza_t fill_pizza(std::vector<std::string> tab);
        void status();
    private:
        float multiplier;
        int nb_cook;
        int replace;
};