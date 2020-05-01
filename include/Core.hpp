/*
** EPITECH PROJECT, 2020
** Core.hpp
** File description:
** Core.hpp
*/

#pragma once

#include "APizza.hpp"
#include <memory>

class Core {
    public:
        Core(char **av);
        ~Core();
        void restaurant();
        void parse_pizza(std::string str);
        int count_part(std::string str);
        std::vector<std::string> divide_command(std::string);
        std::vector<std::shared_ptr<APizza>> create_command(std::vector<std::string> tab_command);
        std::vector<std::shared_ptr<APizza>> get_pizza(std::string str, std::vector<std::shared_ptr<APizza>> tab);
        APizza::PizzaType getType(std::string str);
        APizza::PizzaSize getSize(std::string str);
        int getNb(std::string str);
        void check_pizza(std::shared_ptr<APizza> pizza);
        std::shared_ptr<APizza> fill_pizza(std::vector<std::string> tab);
        void status();
    private:
        float multiplier;
        int nb_cook;
        int replace;
        int nb_kitchen;
};