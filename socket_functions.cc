#include "socket_functions.h"
#define MAX 200
#define SA struct sockaddr


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


void func_read(int sockfd1)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
        // read the message from client and copy it in buffer
        read(sockfd1, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            
            //printf("Client Exit...\n");
            break;
        }
        
        bzero(buff, MAX);
        n = 0;
    }
}

void func_write(int sockfd1)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        write(sockfd1, buff, sizeof(buff));
        
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
        bzero(buff, sizeof(buff));
    }
}

void func_read_auto(int sockfd1)
{
    char buff[MAX];
    int n;
    int i;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
        // read the message from client and copy it in buffer
        read(sockfd1, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("%s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            break;
        }
        
        bzero(buff, MAX);
        n = 0;
    }
}
void func_write_auto(int sockfd)
{
    char buff[MAX];
    int n;
    int i;
    for (i=0; i<5; i++) {
        bzero(buff, sizeof(buff));
        strncpy(buff, "hi\n", sizeof buff - 1);
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
    }
    strncpy(buff, "exit\n", sizeof buff - 1);
    write(sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));
    
}



void func_write_control_message(int sockfd,char *Control_Messages,int n)
{
    int bytes_send=write(sockfd,Control_Messages,n) ;
    printf("bytes sent %d\n", n);

}

void Stop_Lora(int sockfd)    //Stopping DAQ in LORA
{
    unsigned char dat[3] ;
    bzero(dat, sizeof(dat));
    dat[0]=0x99 ;
    dat[1]=0xAA ;        //We have used identifier 'AA' for stopping DAQ in LORA
    dat[2]=0x66 ;
    //write(sockfd,dat,3) ;
    int bytes_send=write(sockfd,dat,sizeof(dat)) ;
    //printf("bytes sent %d\n", bytes_send);

}

void func_write_random(int sockfd)
{
    int n;
    n = rand() % 100 + 1;
    char buff[10];
    bzero(buff, sizeof(buff));
    buff[0]=((unsigned short)(n) & 0x00ff) ;
    //sprintf(buff, "%d", n);
    printf("sending %x\n", buff[0]);

    int bytes_send=write(sockfd,buff,sizeof(buff)) ;
}
