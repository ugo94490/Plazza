/*
** EPITECH PROJECT, 2020
** bootstrap_plazza
** File description:
** main
*/

#include "./main.hpp"
#include "./poll.hpp"

void increm(stock_t *stock) {
    stock->mtx.lock();
    stock->stock += 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    stock->mtx.unlock();
    std::cout << stock->stock << std::endl;
}

int main (void) {
    int n = 12;
    stock_t stock;
    stock.mtx.unlock();
    Poll poll;

    poll.create_thread(increm, &stock);
    poll.create_thread(increm, &stock);
    poll.create_thread(increm, &stock);
    poll.create_thread(increm, &stock);
    poll.create_thread(increm, &stock);

    poll.cleen_poll();
    poll.create_thread(increm, &stock);
    poll.cleen_poll();
    std::cout << stock.stock << std::endl;
    return 0;
}