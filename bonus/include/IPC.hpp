/*
** EPITECH PROJECT, 2020
** IPC.hpp
** File description:
** IPC.hpp
*/

#pragma once

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

class IPC {
    public:
        static int init_server(int port);
        static struct sockaddr_in init_my_addr(int port);
        static int setUpListener(int port);
        int get_status(int i, std::vector<int> fd_tab);
    private:

};
