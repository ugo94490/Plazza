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
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(1600, 800), "Plazza", sf::Style::Close, settings);
    window.setFramerateLimit(60);
    window.clear(sf::Color::White);
    window.display();
    nb_kitchen = 0;
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

    //std::cout << "THIS FD ==> " << fd <<std::endl;
    while (j < nb && tab_pizza.size() != 0) {
        data = APizza::pack(tab_pizza.front()) + ':';
        dprintf(fd, data.c_str());
        tab_pizza.erase(tab_pizza.begin());
        j++;
    }
    //std::cout << "ON A LOOP J ==> " << j << std::endl;
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
            //std::cout << "KITCHEN CREATE" << std::endl;
            Kitchen kitchen(multiplier, nb_cook, replace, i);
            //std::cout << "KITCHEN FINISH" << std::endl;
            exit(0);
        } else {
            nb_kitchen += 1;
            FD_ZERO(&ready);
            FD_SET(fd_socket, &ready);
            while (ok != true) {
                select(FD_SETSIZE, &ready, NULL, NULL, NULL);
                if (FD_ISSET(fd_socket, &ready)) {
                    ok = true;
                    fd_kitchen = accept(fd_socket, (struct sockaddr *) &my_addr, &lenght);
                    FD_SET(fd_kitchen, &current);
                    fd_tab.push_back(fd_kitchen);
                    //std::cout << "IS SET" << std::endl;
                }
            }
            ok = false;
            tab_pizza = sent_pizza(nb_cook * 2, fd_kitchen, tab_pizza); //sent pizza ici
        }
    }
}

int IPC::get_status(int i, std::vector<int> fd_tab)
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
            if ((tmp = IPC::get_status(i)) < (nb_cook * 2))
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

std::vector<sf::RectangleShape> create_button()
{
    std::vector<sf::RectangleShape> tab_button;
    std::vector<sf::Vector2f> tab_pos = {
        {40, 60},
        {230, 60},
        {420, 60},
        {610, 60},
        {40, 250},
        {230, 250},
        {420, 250},
        {610, 250},
        {325, 440},
        {40, 680}
    };

    for (int i = 0; i < tab_pos.size(); i++) {
        sf::RectangleShape rectangle(sf::Vector2f(150, 150));
        rectangle.setPosition(tab_pos[i]);
        rectangle.setFillColor(sf::Color::Green);
        rectangle.setOutlineThickness(5);
        rectangle.setOutlineColor(sf::Color::Black);
        if (i == 9)
            rectangle.setSize({720, 100});
        tab_button.push_back(rectangle);
    }
    return (tab_button);
}

std::vector<sf::Text> Core::create_text()
{
    std::vector<sf::Text> tab_txt;
    sf::Text txt;
    int size_font = 30;
    std::vector<std::string> phrase = {
        "Regina",
        "Margarita",
        "Americana",
        "Fantasia",
        "S",
        "M",
        "L",
        "XL",
        "XXL",
        "SUBMIT",
        "Nombre de cuisine\n  depuis le debut",
        "CHOIX"
    };
    std::vector<sf::Vector2f> tab_pos = {
        {40, 60},
        {230, 60},
        {420, 60},
        {610, 60},
        {40, 250},
        {230, 250},
        {420, 250},
        {610, 250},
        {325, 440},
        {340, 680},
        {80, 440},
        {590, 440}
    };

    font.loadFromFile("SNES.ttf");
    for (int i = 0; i < phrase.size(); i++)
        tab_txt.push_back(txt);
    for (int i = 0; i < phrase.size(); i++) {
        tab_txt[i].setFont(font);
        tab_txt[i].setCharacterSize(size_font);
        tab_txt[i].setFillColor(sf::Color::Black);
        if (i < phrase.size() - 3)
            tab_txt[i].setPosition({tab_pos[i].x + (150 / 2) - (phrase[i].size() * 4), tab_pos[i].y + (150 / 2) - 20});
        else if (i == 9) {
            tab_txt[i].setCharacterSize(60);
            tab_txt[i].setPosition({tab_pos[i].x, tab_pos[i].y + 10});
        }
        else {
            tab_txt[i].setCharacterSize(40);
            tab_txt[i].setPosition(tab_pos[i]);
            tab_txt[i].setFillColor(sf::Color::White);
        }
        tab_txt[i].setString(phrase[i]);
    }
    return (tab_txt);
}

void Core::change_color(int i, std::vector<sf::RectangleShape> tab_button, std::vector<sf::Text> tab_txt)
{
    tab_button[i].setFillColor(sf::Color::White);
    window.draw(tab_button[i]);
    for (int i = 0; i < tab_txt.size(); i++)
        window.draw(tab_txt[i]);
    window.display();
    usleep(100000);
    tab_button[i].setFillColor(sf::Color::Green);
}

std::string disp_pizza(int type, int size)
{
    std::string res = "Pizza";

    if (type == 0)
        res += " Regina";
    if (type == 1)
        res += " Margarita";
    if (type == 2)
        res += " Americana";
    if (type == 3)
        res += " Fantasia";
    if (size == 4)
        res += " S";
    if (size == 5)
        res += " M";
    if (size == 6)
        res += " L";
    if (size == 7)
        res += " XL";
    if (size == 8)
        res += " XXL";
    return (res);
}

std::string format_str(int type, int size)
{
    std::string res;

    if (type == 0)
        res += "regina";
    if (type == 1)
        res += "margarita";
    if (type == 2)
        res += "americana";
    if (type == 3)
        res += "fantasia";
    if (size == 4)
        res += " S";
    if (size == 5)
        res += " M";
    if (size == 6)
        res += " L";
    if (size == 7)
        res += " XL";
    if (size == 8)
        res += " XXL";
    res += " x1";
    return (res);
}

sf::Sprite Core::draw_pizza(std::shared_ptr<APizza> tab_pizza)
{
    sf::Sprite pizza;
    std::string name;
    int timer = 0;
    sf::Vector2f scale;
    sf::Vector2f pos;

    srand(time(NULL));
    if (tab_pizza->getType() == 1)
        pizza.setTexture(pizza_1);
    if (tab_pizza->getType() == 2)
        pizza.setTexture(pizza_2);
    if (tab_pizza->getType() == 4)
        pizza.setTexture(pizza_3);
    if (tab_pizza->getType() == 8)
        pizza.setTexture(pizza_4);
    if (tab_pizza->getSize() == 1)
        scale = {0.5, 0.5};
    if (tab_pizza->getSize() == 2)
        scale = {0.75, 0.75};
    if (tab_pizza->getSize() == 4)
        scale = {1, 1};
    if (tab_pizza->getSize() == 8)
        scale = {1.5, 1.5};
    if (tab_pizza->getSize() == 16)
        scale = {2.0, 2.0};
    pos.x = 800 + rand() % 600;
    pos.y = 0 + rand() % 600;
    pizza.setScale(scale);
    pizza.setPosition(pos);
    return (pizza);
}

std::shared_ptr<APizza> Core::convert_pizza(int type, int size)
{
    int nb_type = 0;
    std::string nb_size;

    if (type == 0)
        nb_type = 1;
    if (type == 1)
        nb_type = 2;
    if (type == 2)
        nb_type = 4;
    if (type == 3)
        nb_type = 8;
    if (size == 4)
        nb_size = "S";
    if (size == 5)
        nb_size = "M";
    if (size == 6)
        nb_size = "L";
    if (size == 7)
        nb_size = "XL";
    if (size == 8)
        nb_size = "XXL";
    if (nb_type == APizza::PizzaType::Americana) {
        std::shared_ptr<APizza> ptr (new American(APizza::PizzaType::Americana, getSize(nb_size)));
        return (ptr);
    }
    if (nb_type == APizza::PizzaType::Fantasia) {
        std::shared_ptr<APizza> ptr (new Fantasi(APizza::PizzaType::Fantasia, getSize(nb_size)));
        return (ptr);
    }
    if (nb_type == APizza::PizzaType::Regina) {
        std::shared_ptr<APizza> ptr (new Regin(APizza::PizzaType::Regina, getSize(nb_size)));
        return (ptr);
    }
    if (nb_type == APizza::PizzaType::Margarita) {
        std::shared_ptr<APizza> ptr (new Margarit(APizza::PizzaType::Margarita, getSize(nb_size)));
        return (ptr);
    }
    return (nullptr);
}

void Core::restaurant()
{
    std::string str;
    static clock_t timer = 0;
    sf::Event event;
    int type = -1;
    int size = -1;
    sf::RectangleShape line(sf::Vector2f(800, 5));
    sf::Sprite back;
    sf::Texture back_t;
    sf::Sprite kitchen;
    sf::Texture kitchen_t;
    std::vector<sf::RectangleShape> tab_button = create_button();
    std::vector<sf::Text> tab_txt = create_text();
    std::vector<sf::Sprite> tab_sprite;
    pid_t pid = 0;
    sf::Text nb_ki;
    sf::Text pizza_tmp;

    pizza_1.loadFromFile("pizza_1.png");
    pizza_2.loadFromFile("pizza_2.png");
    pizza_3.loadFromFile("pizza_3.png");
    pizza_4.loadFromFile("pizza_4.png");
    back_t.loadFromFile("menu.jpg");
    back_t.setSmooth(true);
    kitchen_t.loadFromFile("kitchen.jpg");
    kitchen_t.setSmooth(true);
    kitchen.setTexture(kitchen_t);
    kitchen.setPosition({800, 0});
    back.setTexture(back_t);
    back.setPosition({0, 0});
    line.setFillColor(sf::Color::Black);
    line.setPosition({800, 0});
    line.rotate(90);
    nb_ki.setFont(font);
    pizza_tmp.setFont(font);
    nb_ki.setCharacterSize(40);
    nb_ki.setPosition({160, 520});
    nb_ki.setFillColor(sf::Color::White);
    pizza_tmp.setCharacterSize(40);
    pizza_tmp.setPosition({520, 500});
    pizza_tmp.setFillColor(sf::Color::White);
    fd_socket = IPC::init_server(4242);
    FD_ZERO(&current);
    FD_SET(fd_socket, &current);
    while (window.isOpen()) {
        nb_ki.setString(std::to_string(nb_kitchen));
        pizza_tmp.setString(disp_pizza(type, size));
        window.draw(back);
        window.draw(line);
        window.draw(kitchen);
        window.draw(nb_ki);
        window.draw(pizza_tmp);
        for (int i = 0; i < tab_button.size(); i++)
            window.draw(tab_button[i]);
        for (int i = 0; i < tab_sprite.size(); i++)
            window.draw(tab_sprite[i]);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left)
                    for (int i = 0; i < tab_button.size(); i++) {
                        if (event.mouseButton.x >= tab_button[i].getPosition().x && event.mouseButton.x <= (tab_button[i].getPosition().x + tab_button[i].getSize().x) && event.mouseButton.y >= tab_button[i].getPosition().y && event.mouseButton.y <= (tab_button[i].getPosition().y + tab_button[i].getSize().y)) {
                            change_color(i, tab_button, tab_txt);
                            if (i <= 3)
                                type = i;
                            if (i > 3 && i < 9)
                                size = i;
                            if (i == 9 && type != -1 && size != -1) {
                                parse_pizza(format_str(type, size));
                                tab_sprite.push_back(draw_pizza(convert_pizza(type, size)));
                            }
                        }
                    }
        }
        for (int i = 0; i < tab_txt.size(); i++)
            window.draw(tab_txt[i]);
        window.display();
        /*getline(std::cin, str);
        if (std::cin.eof() == 1)
            return;
        if (str.size() == 0)
            continue;
        if (str[str.size() - 1] == '\n')
            str = str.substr(0, str.size() - 1);
        if (str.compare("status") == 0)
            status();
        else
            parse_pizza(str);*/
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