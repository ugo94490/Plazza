/*
** EPITECH PROJECT, 2020
** Kitchen.cpp
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Margarita.hpp"

Kitchen::Kitchen(int multi, int nb, int temps)
{
    multiplier = multi;
    nb_cook = nb;
    refill = temps;
    actual_cook = 0;
    for (int i = 0; i < 4; i++) {
        std::shared_ptr<APizza> ptr (new Margarit(APizza::Margarita, APizza::S));
        pizza.push_back(ptr);
        //std::cout << APizza::pack(ptr) << std::endl;
    }
    loop();
}

Kitchen::~Kitchen()
{
}

void Kitchen::refill_kitchen()
{

}

void Kitchen::loop() {
    sleep(1);
    for (auto it = pizza.begin(); it != pizza.end(); it++) {
        if (this->create_cook(*it, multiplier) == 1)
            this->pizza.erase(it--);
    }
}

int Kitchen::getStatus()
{
    int value = 6;
    int stock = -1;

    value -= pizza.size();
    for (size_t i = 0; i < 3; i++) {
        stock = this->cook[i]->get_status();
        if (stock == 1) {
            value--;
        }
    }
    return value;
}

int Kitchen::create_cook(std::shared_ptr<APizza> pizza, int multiplier) {
    int status = -1;
    
    if (this->actual_cook != 3) {
        std::shared_ptr<Cook> ptr(new Cook(pizza, multiplier));
        this->cook.push_back(ptr);
        this->actual_cook += 1;
        std::cout << "thread crée et lancé avec succés" << std::endl;
        return 0;
    } else {
        for (size_t i = 0; i < 3; i++) {
            printf("%d\n", i);
            printf("%d\n", this->nb_cook);
            status = this->cook[i]->get_status();
            if (status == 2) {
                this->cook[i]->wait_thread();
                this->cook[i]->start_thread(pizza,multiplier);
                std::cout << "thread lancer avec la fonction" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "stock max atin et pas de thread dispo" << std::endl;
    return 84;
}

void Kitchen::clean_cook() {
    int status = -1;

    for (auto it = this->cook.begin(); it != this->cook.end(); it++) {
        status = it->get()->get_status();
        if (status == 2) {
            it->get()->wait_thread();
            this->cook.erase(it--);
            this->actual_cook -= 1;
            std::cout << "thread suprimer" << std::endl;
        }
    }
}