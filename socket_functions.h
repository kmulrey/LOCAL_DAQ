#include <sstream>
#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>


struct socket_connection
{
    int port;
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;
    
} ;

void make_socket(socket_connection*);

void bind_socket(socket_connection*);
void listen_socket(socket_connection*);
void accept_socket(socket_connection*);


void func_read(int);
void func_write(int);
void func_read_auto(int);
void func_write_auto(int);














