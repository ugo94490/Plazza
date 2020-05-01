/*
** EPITECH PROJECT, 2020
** bootstrap_plazza
** File description:
** poll
*/

#ifndef POLL_HPP_
#define POLL_HPP_

#include "./main.hpp"

class Poll {
    private:
    std::vector<std::shared_ptr<Threads>> _poll;
    int total = 0;

    public:
        Poll() = default;
        ~Poll() = default;
        void create_thread(void (*fct)(stock_t *stock), stock_t *value);
        void cleen_poll();
};

void Poll::create_thread(void (*fct)(stock_t *stock), stock_t *value) {
    int status = -1;
    
    if (total != 3) {
        std::shared_ptr<Threads> ptr(new Threads(fct, value));
        this->_poll.push_back(ptr);
        this->total += 1;
        std::cout << "thread crée et lancé avec succés" << std::endl;
        return;
    } else {
        for (size_t i = 0; i < 3; i++) {
            status = this->_poll[i]->get_status();
            if (status == 2) {
                this->_poll[i]->wait_thread();
                this->_poll[i]->start_thread(fct,value);
                std::cout << "thread lancer avec la fonction" << std::endl;
                return;
            }
        }
    }
    std::cout << "stock max atin et pas de thread dispo" << std::endl;
}

void Poll::cleen_poll() {
    int status = -1;

    for (auto it = this->_poll.begin(); it != this->_poll.end(); it++) {
        status = it->get()->get_status();
        if (status == 2) {
            it->get()->wait_thread();
            this->_poll.erase(it--);
            this->total -= 1;
            std::cout << "thread suprimer" << std::endl;
        }
    }
}


#endif /* !POLL_HPP_ */
