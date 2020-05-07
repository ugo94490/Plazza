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
#include "Kitchen.hpp"
#include "IPC.hpp"

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
    if (multiplier <= 0 || nb_cook < 1 || replace < 0)
        throw(Exception ("Bad argument"));
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

APizza::PizzaType Core::getType(std::string str)
{
    for (auto i = enum_pizza.begin(); i != enum_pizza.end(); i++)
        if (strcasecmp(i->first.c_str(), str.c_str()) == 0)
            return (i->second);
    return (APizza::PizzaType::PizzaError);
}

APizza::PizzaSize Core::getSize(std::string str)
{
    for (auto i = enum_size.begin(); i != enum_size.end(); i++)
        if (i->first.compare(str) == 0)
            return (i->second);
    return (APizza::PizzaSize::SizeError);
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
}

std::shared_ptr<APizza> Core::fill_pizza(std::vector<std::string> tab)
{
    if (getType(tab[0]) == APizza::PizzaType::Americana) {
        std::shared_ptr<APizza> ptr (new American(getType(tab[0]), getSize(tab[1])));
        return (ptr);
    }
    if (getType(tab[0]) == APizza::PizzaType::Fantasia) {
        std::shared_ptr<APizza> ptr (new Fantasi(getType(tab[0]), getSize(tab[1])));
        return (ptr);
    }
    if (getType(tab[0]) == APizza::PizzaType::Regina) {
        std::shared_ptr<APizza> ptr (new Regin(getType(tab[0]), getSize(tab[1])));
        return (ptr);
    }
    if (getType(tab[0]) == APizza::PizzaType::Margarita) {
        std::shared_ptr<APizza> ptr (new Margarit(getType(tab[0]), getSize(tab[1])));
        return (ptr);
    }
    throw(Exception ("Bad type of pizza"));
    return (nullptr);
}

std::vector<std::shared_ptr<APizza>> Core::get_pizza(std::string str, std::vector<std::shared_ptr<APizza>> tab)
{
    std::stringstream stream(str);
    std::shared_ptr<APizza> ptr;
    std::string tmp;
    std::vector<std::string> parse;

    while (std::getline(stream, tmp, ' '))
        parse.push_back(tmp);
    if (parse.size() != 3)
        throw(Exception ("Command Invalid (Invalid Pizza)"));
    if (getNb(parse[2]) == -1)
        throw(Exception ("Bad number of pizza"));
    for (int i = 0; i < getNb(parse[2]); i++) {
        ptr = fill_pizza(parse);
        check_pizza(ptr);
        tab.push_back(ptr);
    }
    return (tab);
}

std::vector<std::shared_ptr<APizza>> Core::create_command(std::vector<std::string> tab_command)
{
    std::vector<std::shared_ptr<APizza>> tab;

    if (tab_command.size() == 0)
        throw(Exception ("Command Invalid (No Argument)"));
    for (size_t i = 0; i < tab_command.size(); i++)
        tab = get_pizza(tab_command[i], tab);
    return (tab);
}

std::vector<std::shared_ptr<APizza>> Core::sent_pizza(int nb, int fd, std::vector<std::shared_ptr<APizza>> tab_pizza)
{
    std::string data;
    int j = 0;

    if (tab_pizza.size() < nb)
        nb = tab_pizza.size();
    for (; j < nb; j++) {
        data = APizza::pack(tab_pizza[j]) + ':';
        dprintf(fd, data.c_str());
    }
    for (int k = 0; k < j; k++)
        tab_pizza.erase(tab_pizza.begin());
    return (tab_pizza);
}

void Core::create_kitchen(std::vector<std::shared_ptr<APizza>> tab_pizza)
{
    int nb = 0;
    pid_t pid = 0;
    bool ok = false;
    int fd_kitchen = 0;
    struct sockaddr_in my_addr = IPC::init_my_addr(4242);
    socklen_t lenght = sizeof(my_addr);

    nb = (tab_pizza.size() / (nb_cook * 2));
    nb += (tab_pizza.size()) % (nb_cook * 2) != 0 ? 1 : 0;
    for (int i = 0; i < nb; i++) {
        pid = fork();
        if (pid == 0) {
            std::cout << "KITCHEN CREATE" << std::endl;
            Kitchen kitchen(multiplier, nb_cook, replace);
            std::cout << "KITCHEN FINISH" << std::endl;
            exit(0);
        } else {
            FD_ZERO(&ready);
            FD_SET(fd_socket, &ready);
            while (ok != true) {
                select(FD_SETSIZE, &ready, NULL, NULL, NULL);
                if (FD_ISSET(fd_socket, &ready)) {
                    ok = true;
                    fd_kitchen = accept(fd_socket, (struct sockaddr *) &my_addr, &lenght);
                    FD_SET(fd_kitchen, &current);
                    fd_tab.push_back(fd_kitchen);
                }
            }
            tab_pizza = sent_pizza(nb_cook * 2, fd_kitchen, tab_pizza);
        }
    }
}

int Core::get_status(int i)
{
    char res[80];
    fd_set tmp;
    int fd = fd_tab[i];
    bool ok = false;

    FD_ZERO(&tmp);
    FD_SET(fd, &tmp);
    select(FD_SETSIZE, &tmp, NULL, NULL, NULL);
    if (FD_ISSET(fd, &tmp)) {
        read(fd, res, 80);
        fd_tab.erase(fd_tab.begin() + i);
        FD_ZERO(&tmp);
        return (-1);
    } else {
        while (ok != true) {
            select(FD_SETSIZE, &tmp, NULL, NULL, NULL);
            if (FD_ISSET(fd_tab[i], &tmp)) {
                read(fd, res, 80);
                ok = true;
            }
        }
        return (std::stoi(res));
    }
    return (-1);
}

void Core::parse_pizza(std::string str)
{
    std::vector<std::shared_ptr<APizza>> tab_pizza;
    std::vector<std::string> tab_command;
    int tmp = 0;

    tab_command = divide_command(str);
    tab_pizza = create_command(tab_command);
    //if (fd_tab.size() == 0) {
        create_kitchen(tab_pizza);
    /*} else {
        for (size_t i = 0; i < fd_tab.size(); i++) {
            if ((tmp = get_status(i)) < (nb_cook * 2))
                if (tmp == -1)
                    i -= 1;
                else
                    tab_pizza = sent_pizza(tmp, fd_tab[i], tab_pizza);
        }
        if (tab_pizza.empty() != true)
            create_kitchen(tab_pizza);
    }*/
}

void Core::status()
{
    if (fd_tab.size() == 0)
        std::cout << "No Kitchen running" << std::endl;
    else {
        for (int i = 0; i < fd_tab.size(); i++)
            write(fd_tab[i], "status", 6);
    }
}

struct sockaddr_in IPC::init_my_addr(int port)
{
    struct sockaddr_in my_addr;

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(port);
    return (my_addr);
}

int IPC::init_server(int port)
{
    int my_socket = 0;
    int option = 1;
    struct sockaddr_in my_addr = init_my_addr(port);
    socklen_t lenght_socket = sizeof(my_addr);

    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket == -1)
        return (0);
    lenght_socket = sizeof(my_addr);
    if (setsockopt(my_socket, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR),
        (char *)&option, sizeof(option)) < 0)
        return (0);
    if (bind(my_socket, (struct sockaddr *) &my_addr, lenght_socket) == -1)
        return (0);
    if (listen(my_socket, 100) == -1)
        perror("Listen");
    return (my_socket);
}

void Core::restaurant()
{
    std::string str;
    static clock_t timer = 0;

    fd_socket = IPC::init_server(4242);
    FD_ZERO(&current);
    FD_SET(fd_socket, &current);
    while (1) {
        getline(std::cin, str);
        if (std::cin.eof() == 1)
            return;
        if (str.size() == 0)
            continue;
        if (str[str.size() - 1] == '\n')
            str = str.substr(0, str.size() - 1);
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