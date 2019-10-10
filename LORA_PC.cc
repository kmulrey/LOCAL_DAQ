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
#include "socket_functions.h"
#include "extra.h"


#define    PORT1    8002
#define    PORT2    8003



//g++ -o LORA LORA_PC.cc


int main(int argc, char **argv)
{
    DEVICE *unit = new DEVICE();
    char filename[]="input.txt";
    unit->Read_Message_File(filename,1);
    unit->Build_Messages();


    
    
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
    listen_socket(&sock_send);
    accept_socket(&sock_send);

    
    func_read(sock_listen.connfd);
    sleep(1);

    //func_write_auto(sock_send.connfd);
    printf("writing control messages...\n");
    func_write_control_message(sock_send.connfd,unit->Control_Messages,sizeof(unit->Control_Messages));
    printf("done control messages...\n");

    usleep(500000);
    //for(int i=0; i<2; i++){
    //     func_write_random(sock_send.connfd);
    //     usleep(500000);
    // }
    
    
    
    Stop_Lora(sock_send.connfd);
    
    close(sock_listen.sockfd);
    close(sock_send.sockfd);
    

    return 0;
}


