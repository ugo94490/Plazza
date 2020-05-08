/*
** EPITECH PROJECT, 2020
** Kitchen.cpp
** File description:
** Kitchen.cpp
*/

#include <fcntl.h>
#include "Kitchen.hpp"
#include "Margarita.hpp"
#include "Cook.hpp"

Kitchen::Kitchen(int multi, int nb, int temps, int id)
{
    multiplier = multi;
    nb_cook = nb;
    refill = temps;
    actual_cook = 0;
    this->id = id;
    //std::cout << "ID ==>" << this->id <<std::endl;
    for (int i = 0; i < 5; i++)
        refill_kitchen();
    kitchen_fd = IPC::setUpListener(4242);
    fcntl(kitchen_fd, F_SETFL, fcntl(kitchen_fd, F_GETFL, 0) | O_NONBLOCK);
    loop();
}

Kitchen::~Kitchen()
{
    write(kitchen_fd, "destroy", 7);
    this->clean_cook();
}

void Kitchen::refill_kitchen()
{
    for (int i = 0; i <= APizza::PizzaIngredient::Chief_Love; i++)
        ingredient[static_cast<APizza::PizzaIngredient>(i)]++;
}

void Kitchen::loop()
{
    static clock_t timer = 0;
    static clock_t ingredient_timer = 0;

    while ((clock() - timer) < 5000000) {
        recieveOrder(kitchen_fd);
        if (getStatus() < (nb_cook * 2))
            timer = clock();
        if (pizza.empty() != true) {
            //std::cout << "KITCHEN ID ==> " << this->id << " PIZZA SIZE ==>  "<< pizza.size() <<std::endl;
            for (int i = pizza.size() - 1; i >= 0; i--) {
                if (this->check_ingredients(pizza[i]) && this->ping_cook() > 0) {
                    setup_cooking(pizza[i]);
                    pizza.pop_back();
                    timer = clock();
                    break;
                }
            }
        }
        if ((clock() - ingredient_timer) >= refill * 1000) {
            ingredient_timer = clock();
            this->refill_kitchen();
        }
    }
}

void Kitchen::setup_cooking(std::shared_ptr<APizza> tmp_pizza) {
    if (ping_cook() == 2) {
        std::shared_ptr<Cook> ptr(new Cook(this->multiplier, this->actual_cook));
        this->actual_cook += 1;
        ptr->get_pizzou(tmp_pizza);
        this->cook.push_back(ptr);
    } else {
        for (size_t i = 0; i < this->actual_cook; i++) {
            if (this->cook[i]->get_status() == 2) {
                cook[i]->get_pizzou(tmp_pizza);
                cook[i]->unlock_cooker();
                return;
            }
        }
    }
}

int Kitchen::ping_cook() {
    for (size_t i = 0; i < this->actual_cook; i++)
        if (this->cook[i]->get_status() == 2)
            return 1;
    if (this->actual_cook < this->nb_cook)
        return 2;
    return 0;
}

int Kitchen::getStatus()
{
    int value = nb_cook * 2;
    int stock = -1;

    value -= pizza.size();
    for (int i = 0; i < this->actual_cook; i++) {
        stock = this->cook[i]->get_status();
        if (stock == 1) {
            value--;
        }
    }
    return value;
}

bool Kitchen::check_ingredients(std::shared_ptr<APizza> pizza)
{
    std::vector<APizza::PizzaIngredient> ingre = pizza->getIngredients();
    int count = 0;

    for (auto i = ingredient.begin(); i != ingredient.end(); i++)
        for (int j = 0; j < ingre.size(); j++)
            if (i->first == ingre[j] && i->second > 0)
                count++;
    if (count != ingre.size())
        return (false);
    for (auto i = ingredient.begin(); i != ingredient.end(); i++)
        for (int j = 0; j < ingre.size(); j++)
            if (i->first == ingre[j] && i->second > 0)
                i->second--;
    return (true);
}

void Kitchen::clean_cook() {
    int status = -1;

    for (auto it = this->cook.begin(); it != this->cook.end(); it++) {
        status = it->get()->get_status();
        if (status == 2) {
            it->get()->~Cook();
            this->cook.erase(it--);
            this->actual_cook -= 1;
        }
    }
}

int my_putstr(int fd, char *str)
{
    int i = 0;

    for (; str[i]; i++);
    return write(fd, str, i);;
}

int error(const char *msg)
{
    std::cout << msg <<  std::endl;
    return 84;
}

int IPC::setUpListener(int port)
{
    struct sockaddr_in saddr = IPC::init_my_addr(port);
    int cfd;

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0)
        return (error("socket creation error\n"));
    if (connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        close(cfd);
        return (error("connection error\n"));
    }
    return cfd;
}

int Kitchen::count_dot(std::string str)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == ':')
            count++;
    return (count);
}

void Kitchen::check_pizza(std::string str)
{
    int nb = count_dot(str);
    int off = 0;
    int start = 0;
    std::string tmp;
    std::shared_ptr<APizza> ptr;

    for (int i = 0; i < nb; i++) {
        off = str.find(':', 0);
        tmp = str.substr(0, off);
        ptr = APizza::unpack(tmp);
        pizza.push_back(ptr);
    }
}

std::string Kitchen::readSocket(int cfd)
{
    char buffer[108 + 1] = {0};
    int len = read(cfd, buffer, 108);
    std::string res = "";

    res = std::string(buffer);
    while (len >= 108) {
        buffer[108] = 0;
        res += std::string(buffer);
        len = read(cfd, buffer, 108);
    }
    return res;
}

void Kitchen::display_ingredient(std::string tmp)
{
    std::string res = "Il y a ";
    for (auto i = ingredient.begin(); i != ingredient.end(); i++) {
        if (i->first == APizza::PizzaIngredient::Doe)
            res += std::to_string(i->second) + " Doe";
        if (i->first == APizza::PizzaIngredient::Tomato)
            res += std::to_string(i->second) + " Tomato";
        if (i->first == APizza::PizzaIngredient::Gruyere)
            res += std::to_string(i->second) + " Gruyere";
        if (i->first == APizza::PizzaIngredient::Ham)
            res += std::to_string(i->second) + " Ham";
        if (i->first == APizza::PizzaIngredient::Mushrooms)
            res += std::to_string(i->second) + " Mushrooms";
        if (i->first == APizza::PizzaIngredient::Steak)
            res += std::to_string(i->second) + " Steak";
        if (i->first == APizza::PizzaIngredient::Eggplant)
            res += std::to_string(i->second) + " Eggplant";
        if (i->first == APizza::PizzaIngredient::Goat_Cheese)
            res += std::to_string(i->second) + " Goat Cheese";
        if (i->first == APizza::PizzaIngredient::Chief_Love)
            res += std::to_string(i->second) + " Chief Love";
        res += ", ";
    }
    res[res.size() - 2] = '.';
    tmp = tmp + "\n" + res;
    std::cout << tmp << std::endl;
}

void Kitchen::recieveOrder(int cfd)
{
    std::string str = readSocket(cfd);
    std::string tmp = "Il y a ";

    if (str.empty() == false) {
        if (str == "nb_pizza")
            dprintf(kitchen_fd, std::to_string(getStatus()).c_str());
        else if (str == "status") {
            tmp = tmp + std::to_string(getStatus()) + " place de libre dans la cuisine.";
            display_ingredient(tmp);
        } else {
            check_pizza(str);
        }
    }
}