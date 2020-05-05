/*
** EPITECH PROJECT, 2020
** Kitchen.cpp
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Margarita.hpp"
#include "Cook.hpp"

Kitchen::Kitchen(int multi, int nb, int temps)
{
    multiplier = multi;
    nb_cook = nb;
    refill = temps;
    actual_cook = 0;
    for (int i = 0; i < 6; i++) {
        std::shared_ptr<APizza> ptr (new Margarit(APizza::Margarita, APizza::S));
        pizza.push_back(ptr);
    }
    loop();
}

Kitchen::~Kitchen()
{
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

    while (1) {
        if (getStatus() == nb_cook * 2) {
            timer = clock();
            while ((clock() - timer) < 5000000) {};
            if (getStatus() == nb_cook * 2)
                return;
        }
        if (pizza.empty() != true) {
            for (int i = pizza.size() - 1; i >= 0; i--) {
                if (/*this->check_ingredients(pizza[i]) && */this->ping_cook() > 0) {
                    setup_cooking(pizza[i]);
                    pizza.pop_back();
                    timer = clock();
                    break;
                }
            }
            //std::cout << "SIZE :" << pizza.size() << std::endl;
        }
        if ((clock() - ingredient_timer) >= refill * 1000) {
            ingredient_timer = clock();
            this->refill_kitchen();
        }
    }
}

void Kitchen::setup_cooking(std::shared_ptr<APizza> tmp_pizza) {
    if (ping_cook() == 2) {
        std::cout << "NEW COOKER" << std::endl;
        std::shared_ptr<Cook> ptr(new Cook(this->multiplier, this->actual_cook));
        this->actual_cook += 1;
        ptr->get_pizzou(tmp_pizza);
        this->cook.push_back(ptr);
    } else {
        for (size_t i = 0; i < this->actual_cook; i++) {
            if (this->cook[i]->get_status() == 2) {
                std::cout << "RE USE COOKER " << i <<std::endl;
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
    for (size_t i = 0; i < this->actual_cook; i++) {
        stock = this->cook[i]->get_status();
        if (stock == 1) {
            value--;
        }
    }
    return value;
}

bool Kitchen::check_ingredients(std::shared_ptr<APizza> pizza)
{
    auto ingredients = pizza->getIngredients();

    for (auto i : ingredients)
        if (ingredient[i] < 1)
            return false;
    for (auto i : ingredients)
        ingredient[i]--;
    return true;
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