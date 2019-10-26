#include <poll.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <iostream>



void disable_canonical();

void enable_canonical();
bool key_pressed(char c);
