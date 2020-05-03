/*
** EPITECH PROJECT, 2020
** test.cpp
** File description:
** test.cpp
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>

char randchar()
{
    std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    return charset[rand() % 62];
}

std::string random_string(size_t length)
{
    std::string str(length,0);
    for (size_t i = 0; i < length; i++)
        str[i] = randchar();
    return str;
}

int generate_pipe(std::string str)
{
    return (mkfifo(str.c_str(), 0777));
}

void send(std::string path, std::string msg)
{
    int fd = open(path.c_str(), O_WRONLY);

    std::cout << "FD :" << fd << std::endl;
    std::cout << "NB PRINT :" << dprintf(fd, msg.c_str()) << std::endl;
    close(fd);
}

std::string recv(std::string path)
{
    int fd = open(path.c_str(), O_RDONLY);
    std::string res;
    char arr[80];
    int nb = 0;

    std::cout << "CHECK" << std::endl;
    nb = read(fd, arr, sizeof(arr));
    arr[nb] = 0;
    res = arr;
    close(fd);
    return (res);
}

int main()
{
    pid_t pid = 0;
    srand(time(NULL));
    std::string print;
    std::string str = random_string(16);
    std::string str1 = random_string(16);
    str = "/tmp/" + str;
    str1 = "/tmp/" + str1;
    std::cout << str << std::endl;
    std::cout << str1 << std::endl;
    std::cout << generate_pipe(str) << std::endl;
    pid = fork();
    if (pid == 0) {
        send(str, "COUCOU");
        exit(0);
    } else {
        print = recv(str);
        std::cout << "RES :" << print << ";" << std::endl;
    }
    remove(str.c_str());
    return (0);
}