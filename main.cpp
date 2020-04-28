/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main.cpp
*/

#include <iostream>
#include <ostream>
#include <string.h>
#include "Core.hpp"
#include "Exception.hpp"

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
}

Core::~Core()
{
}

void Core::restaurant()
{
    
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