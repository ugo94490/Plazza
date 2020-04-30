/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main.cpp
*/

#include <iostream>
#include <ostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <map>
#include <time.h>
#include "Core.hpp"
#include "APizza.hpp"
#include "Exception.hpp"
#include "Americana.hpp"
#include "Regina.hpp"
#include "Margarita.hpp"
#include "Fantasia.hpp"

static const std::map<std::string, APizza::PizzaType> enum_pizza {
    {"regina", APizza::PizzaType::Regina},
    {"margarita", APizza::PizzaType::Margarita},
    {"americana", APizza::PizzaType::Americana},
    {"fantasia", APizza::PizzaType::Fantasia}
};

static const std::map<std::string, APizza::PizzaSize> enum_size {
    {"S", APizza::PizzaSize::S},
    {"M", APizza::PizzaSize::M},
    {"L", APizza::PizzaSize::L},
    {"XL", APizza::PizzaSize::XL},
    {"XXL", APizza::PizzaSize::XXL}
};

bool isInt(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
        if  (str[i] < '0' || str[i] > '9')
            return (false);
    return (true);
}

bool isFloat(std::string str)
{
    int count = 0;

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '.') {
            count++;
            continue;
        }
        if  (str[i] < '0' || str[i] > '9')
            return (false);
    }
    return (count >= 2 ? false : true);
}

Core::Core(char **av)
{
    if (!isFloat(av[1]) || !isInt(av[2]) || !isInt(av[3]))
        throw(Exception ("One argument is not a number"));
    multiplier = std::stof(av[1]);
    nb_cook = std::stoi(av[2]);
    replace = std::stoi(av[3]);
    restaurant();
}

Core::~Core()
{
}

std::vector<std::string> Core::divide_command(std::string str)
{
    std::stringstream stream(str);
    std::vector<std::string> parse;
    std::string tmp;

    while (std::getline(stream, tmp, ';')) {
        if (tmp[0] == ' ')
            parse.push_back(tmp.substr(1, tmp.size() - 1));
        else
            parse.push_back(tmp);
    }
    return (parse);
}

int Core::getType(std::string str)
{
    for (auto i = enum_pizza.begin(); i != enum_pizza.end(); i++)
        if (strcasecmp(i->first.c_str(), str.c_str()) == 0)
            return (i->second);
    return (-1);
}

int Core::getSize(std::string str)
{
    for (auto i = enum_size.begin(); i != enum_size.end(); i++)
        if (i->first.compare(str) == 0)
            return (i->second);
    return (-1);
}

int Core::getNb(std::string str)
{
    std::string nb;
    int number = 0;

    if (str.size() < 1 || str[0] != 'x')
        return (-1);
    nb = str.substr(1, str.size() - 1);
    if (!isInt(nb))
        return (-1);
    number = std::stoi(nb);
    if (number <= 0 || number > 99)
        return (-1);
    return (number);
}

void Core::check_pizza(std::shared_ptr<APizza> ptr)
{
    if (ptr->getSize() == -1)
        throw(Exception ("Bad size of pizza"));
    /*if (pizza.nb == -1)
        throw(Exception ("Bad number of pizza"));*/
}

std::shared_ptr<APizza> Core::fill_pizza(std::vector<std::string> tab)
{
    std::shared_ptr<APizza> ptr = nullptr;

    if (getType(tab[0]) == APizza::PizzaType::Americana)
        ptr = new Americana(getType(tab[0]), getSize(tab[1]));
    if (getType(tab[0]) == APizza::PizzaType::Fantasia)
        ptr = new Fantasia(getType(tab[0]), getSize(tab[1]));
    if (getType(tab[0]) == APizza::PizzaType::Regina)
        ptr = new Regina(getType(tab[0]), getSize(tab[1]));
    if (getType(tab[0]) == APizza::PizzaType::Margarita)
        ptr = new Margarita(getType(tab[0]), getSize(tab[1]));
    if (ptr == nullptr)
        throw(Exception ("Bad type of pizza"));

    /*ptr.nb = getNb(tab[2]);*/
    return (ptr);
}

std::shared_ptr<APizza> Core::get_pizza(std::string str)
{
    std::stringstream stream(str);
    std::shared_ptr<APizza> ptr;
    std::string tmp;
    std::vector<std::string> parse;

    while (std::getline(stream, tmp, ' '))
        parse.push_back(tmp);
    if (parse.size() != 3)
        throw(Exception ("Command Invalid (Invalid Pizza)"));
    ptr = fill_pizza(parse);
    check_pizza(ptr);
    return (ptr);
}

std::vector<std::shared_ptr<APizza>> Core::create_command(std::vector<std::string> tab_command)
{
    std::vector<std::shared_ptr<APizza>> tab;

    if (tab_command.size() == 0)
        throw(Exception ("Command Invalid (No Argument)"));
    for (size_t i = 0; i < tab_command.size(); i++)
        tab.push_back(get_pizza(tab_command[i]));
    return (tab);
}

void Core::parse_pizza(std::string str)
{
    std::vector<std::shared_ptr<APizza>> tab_pizza;
    std::vector<std::string> tab_command;

    tab_command = divide_command(str);
    tab_pizza = create_command(tab_command);
    for (size_t i = 0; i < tab_pizza.size(); i++) {
        std::cout << "Pizza :" << tab_pizza[i]->getType();
        std::cout << "  Size :" << tab_pizza[i]->getSize() << std::endl;
    }
}

void Core::status()
{

}

void Core::restaurant()
{
    std::string str;
    static clock_t timer = 0;

    while (1) {
        getline(std::cin, str);
        if (std::cin.eof() == 1)
            return;
        if (str[str.size() - 1] == '\n')
            str = str.substr(0, str.size() - 1);
        if ((clock() - timer) > (replace * 1000)) {
            timer = clock();
            //refill_kitchen();
        }
        if (str.compare("status") == 0)
            status();
        else
            parse_pizza(str);
    }
}

int main(int ac, char **av)
{
    try {
    if (ac != 4)
        throw(Exception ("Program takes 3 argument"));
    Core core(av);
    return (0);
    } catch (Exception& err) {
        std::cerr << err.what() << std::endl;
    }
}