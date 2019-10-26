#include <poll.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <iostream>
#include "io.h"



void disable_canonical(){
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
}

void enable_canonical(){
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
}

bool key_pressed(char c){
    struct pollfd fds[1];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    int r = poll(fds, 1, 1);
    if(r > 0){
        if(fds[0].revents & POLLIN || fds[0].revents & POLLRDBAND || fds[0].revents & POLLRDNORM){
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            int n = read(0, buffer, sizeof(buffer) -1);
            for(int i = 0; i < n; ++i){
                if(buffer[i] == c){
                    return true;
                }
            }
        }
    }
    return false;
}
