#include "socket_functions.h"
#include <fcntl.h>
#include <sstream>
#include <stdio.h>
#include "event.h"

//#define MAX 32840
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
    int x;
    
    if (sock->connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    
    
    //x=fcntl(sock->sockfd,F_GETFL,0) ;        // Get socket flags
    fcntl(sock->sockfd,F_SETFL, O_NONBLOCK) ;    // Add non-blocking flag
    printf("server acccepted the client... \n");
}


void func_read(int sockfd1)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    //for (;;) {
        bzero(buff, MAX);
        // read the message from client and copy it in buffer
        read(sockfd1, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s", buff);
     //   if ((strncmp(buff, "exit", 4)) == 0) {
            
            //printf("Client Exit...\n");
       //     break;
       // }
        
        bzero(buff, MAX);
        n = 0;
    //}
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
    Control_Messages[0]=0x99;
    int bytes_send=write(sockfd,Control_Messages,n) ;
    //printf("bytes sent %d, %x  %x  %x\n", n,Control_Messages[0],Control_Messages[1],Control_Messages[2]);

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

int scope_raw_read(int sockfd1,uint8_t *bf, int32_t size) //ok 24/7/2012
{
    int ir;
    ir =read(sockfd1, (void *)bf, size);
    return ir;
}

int func_listen(int sockfd1){
    int r=0;
    int nread;
    uint8_t buff[MAX];
    unsigned char rawbuf[4]={0,0,0,0};

    bzero(buff, MAX);
    uint8_t type=0;
    do{                           // flush scope until start-of-message
        nread = scope_raw_read(sockfd1,rawbuf,1);
        // printf("flush\n");
    } while(rawbuf[0] != 0x99 && nread>0);
    
    if(rawbuf[0] != MSG_START && nread>0){    // not a start of message
        printf("Not a message start %x\n",rawbuf[0]);
        return(-1);
    }
    
    int i;
    read(sockfd1, buff, sizeof(buff)-1);

    //if(buff[0]!=0){

        printf("message from client!  %x   %x  %lu\n",buff[0],buff[1],sizeof(buff));
        type=buff[0];
        if(type==0xc0){//c0
            printf("  --->event!\n");
            handle_event(buff,sizeof(buff));
        }
        

        if(type==0xc4){//c4
            printf("PPS\n");
        }
 
    
        
    //}
    //bzero(buff, MAX);
    return type;
}
