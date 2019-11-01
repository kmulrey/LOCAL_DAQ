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
#include <poll.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h> /* Added for the nonblocking socket */

#include "extra.h"
#include "event.h"
#include "io.h"
#include "socket_functions.h"

#define    PORT1    8002
#define    PORT2    8003


char runnr[80];
//g++ -o LORA LORA_PC.cc


int main(int argc, char **argv)
{
    

    if (argc < 2) {
        printf("Using default runnr 000\n");
        strcpy(runnr,"000");
    }
    else{
        strcpy(runnr,argv[1]);
    }
    printf("runnr: %s\n",runnr);

    
    
    
    disable_canonical();
    

    
    DEVICE *unit = new DEVICE();
    char filename[]="input.txt";
    char mode_filename[]="mode_parameters.txt";

    unit->Read_Message_File(filename,1);
    unit->Read_Message_File(filename,2);
    unit->Read_Message_File(filename,3);
    unit->Read_Message_File(filename,4);

    unit->Read_Parameter_Mode_File(mode_filename);
    unit->Build_Messages(1);
    unit->Build_Messages(2);
    unit->Build_Messages(3);
    unit->Build_Messages(4);

    unit->Build_Mode_Messages();
    unit->Build_Finish_Messages();
    
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
    
   
    func_read(sock_listen.connfd); // read that client is conncted
    
    
    sleep(1);
    

    //write control mode parameters
    func_write_control_message(sock_send.connfd,unit->Control_Mode_Messages,sizeof(unit->Control_Mode_Messages));
    usleep(100000);
    
    // write messages for each channel
    for(int j=0; j<4; j++){
        func_write_control_message(sock_send.connfd,unit->Control_Messages[j],sizeof(unit->Control_Messages[j]));
        usleep(100000);
    }
    printf("writing finish messages...\n");

    func_write_control_message(sock_send.connfd,unit->Finish_Message,sizeof(unit->Finish_Message));
    usleep(100000);
    
    
    /////////////////////////////////// listen mode ///////////////////////////////////
    
    
    
    int r;
    printf("press 'x' to exit\n");

    while(true){

        
        r=func_listen(sock_listen.connfd);
        if(key_pressed('x')){
            Stop_Lora(sock_send.connfd);
            break;
        }
        
        
        
        usleep(5000);
        //std::cout << "looping...\n";
    }
    
    
    
    enable_canonical();
    
   
     ////////////////////////////////////////////////////////////////////////
    
    
    

    close(sock_listen.sockfd);
    close(sock_send.sockfd);
    
    printf("sockets closed. bye!\n");
    
    return 0;
}


