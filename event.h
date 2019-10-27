#include <stdio.h>
#include <stdlib.h>
//#include "add.h"
//#include <iostream>
#include <sys/wait.h>
//#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include "time.h"



#define DATA_MAX_SAMP   4096                       //!< Maximal trace length (samples)
#define MAX_READOUT     (70 + DATA_MAX_SAMP*8 + 2) //!< Maximal raw event size
#define MSG_START    0x99 //!< start of fpga message
#define MSG_END      0x66 //!< end of fpga message


/* PPS definition */
#define PPS_BCNT        2 //332 bytes
#define PPS_TIME        4
#define PPS_STATUS     11
#define PPS_CTP        12
#define PPS_QUANT      16
#define PPS_FLAGS      20
#define PPS_RATE       24
#define PPS_GPS        26
#define PPS_CTRL       66
#define PPS_WINDOWS    78
#define PPS_CH1        94
#define PPS_CH2       106
#define PPS_CH3       118
#define PPS_CH4       130
#define PPS_TRIG1     142
#define PPS_TRIG2     154
#define PPS_TRIG3     166
#define PPS_TRIG4     178
#define PPS_FILT11    190
#define PPS_FILT12    206
#define PPS_FILT21    222
#define PPS_FILT22    238
#define PPS_FILT31    254
#define PPS_FILT32    270
#define PPS_FILT41    286
#define PPS_FILT42    302
#define PPS_END       318
#define PPS_LENGTH    (320) //!< Total size of the PPS message

/*----------------------------------------------------------------------*/
/* Event definition */
#define EVENT_BCNT        2 //bytecount
#define EVENT_TRIGMASK    4
#define EVENT_GPS         6
#define EVENT_STATUS     13
#define EVENT_CTD        14
#define EVENT_LENCH1     18
#define EVENT_LENCH2     20
#define EVENT_LENCH3     22
#define EVENT_LENCH4     24
#define EVENT_THRES1CH1  26
#define EVENT_THRES2CH1  28
#define EVENT_THRES1CH2  30
#define EVENT_THRES2CH2  32
#define EVENT_THRES1CH3  34
#define EVENT_THRES2CH3  36
#define EVENT_THRES1CH4  38
#define EVENT_THRES2CH4  40
#define EVENT_CTRL       42
#define EVENT_WINDOWS    54
#define EVENT_ADC        70

#define N_BASELINE       50

void read_fake_file(char*,uint8_t *);
void handle_event(uint8_t *);
void write_event(uint8_t *);
