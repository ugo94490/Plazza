/*
** EPITECH PROJECT, 2020
** Core.hpp
** File description:
** Core.hpp
*/

#pragma once

#include "APizza.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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
        static APizza::PizzaType getType(std::string str);
        static APizza::PizzaSize getSize(std::string str);
        int getNb(std::string str);
        void check_pizza(std::shared_ptr<APizza> pizza);
        static std::shared_ptr<APizza> fill_pizza(std::vector<std::string> tab);
        void status();
        void create_kitchen(std::vector<std::shared_ptr<APizza>> tab_pizza);
        std::vector<std::shared_ptr<APizza>> sent_pizza(int nb, int i, std::vector<std::shared_ptr<APizza>> tab_pizza);
        int get_status(int fd);
        void change_color(int i, std::vector<sf::RectangleShape> tab_button, std::vector<sf::Text> tab_txt);
        std::vector<sf::Text> create_text();
        sf::Sprite draw_pizza(std::shared_ptr<APizza> tab_pizza);
        std::shared_ptr<APizza> convert_pizza(int type, int size);
    private:
        float multiplier;
        int nb_cook;
        int replace;
        int fd_socket;
        std::vector<int> fd_tab;
        fd_set current;
        fd_set ready;
        sf::RenderWindow window;
        sf::Font font;
        int nb_kitchen;
        sf::Texture pizza_1;
        sf::Texture pizza_2;
        sf::Texture pizza_3;
        sf::Texture pizza_4;
};