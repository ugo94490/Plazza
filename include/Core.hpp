/*
** EPITECH PROJECT, 2020
** Core.hpp
** File description:
** Core.hpp
*/

class Core {
    public:
        Core(char **av);
        ~Core();
        void restaurant();
    private:
        float multiplier;
        int nb_cook;
        int replace;
};