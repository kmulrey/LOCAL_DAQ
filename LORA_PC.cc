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

#define    PORT1    8002
#define    PORT2    8003

#define MAX 80
#define SA struct sockaddr

//g++ -o LORA LORA_PC.cc


struct socket_connection
{
    int port;
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;
    //sockaddr_in servaddr, cli;

} ;








void make_socket(socket_connection* sock){
    // socket create and verification
    
    sock->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    printf("Socket successfully created..\n");
    bzero(&sock->servaddr, sizeof(sock->servaddr));
    
    // assign IP, PORT
    sock->servaddr.sin_family = AF_INET;
    sock->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->servaddr.sin_port = htons(sock->port);
}

void bind_socket(socket_connection* sock){
    // Binding newly created socket to given IP and verification
    
    
    int enable = 1;
    if (setsockopt(sock->sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
    
    
    if ((bind(sock->sockfd, (struct sockaddr*)&sock->servaddr, sizeof(sock->servaddr))) != 0) {

    //if ((bind(sock->sockfd, (SA*)&sock->servaddr, sizeof(sock->servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
    printf("Socket successfully binded..\n");
}



void listen_socket(socket_connection* sock){
    // Now server is ready to listen and verification
    if ((listen(sock->sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    printf("Server listening..\n");
    sock->len = sizeof(sock->cli);
}

void accept_socket(socket_connection* sock){
    // Accept the data packet from client and verification
    //sock->connfd = accept(sock->sockfd, (SA*)&sock->cli, &sock->len);
    sock->connfd = accept(sock->sockfd, (struct sockaddr*)&sock->cli, &sock->len);

    if (sock->connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
    printf("server acccepted the client...\n");
}

void func(int sockfd)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
        
        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
        ;
        
        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));
        
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

void func_read(int sockfd1)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (int i=0; i<5; i++) {
        bzero(buff, MAX);
        // read the message from client and copy it in buffer
        read(sockfd1, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            
            printf("Client Exit...\n");
            break;
        }

        bzero(buff, MAX);
        n = 0;
    }
}


int main(int argc, char **argv)
{
    struct socket_connection sock_listen;
    struct socket_connection sock_send;

    sock_listen.port=PORT1;
    sock_send.port=PORT2;

    make_socket(&sock_listen);
    bind_socket(&sock_listen);
    
    make_socket(&sock_send);
    bind_socket(&sock_send);
    
    
    listen_socket(&sock_listen);
    accept_socket(&sock_listen);

    
    func_read(sock_listen.connfd);
    
    
    
    
    
    
    
    
    close(sock_listen.sockfd);
    close(sock_send.sockfd);


   
    
    return 0;
}
