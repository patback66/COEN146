/* Matthew Koken <mkoken@scu.edu>
   COEN 146 - Lab 4
   koken_lab4_client.c
*/
#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"

struct Packet{
  unsigned short seq;
  unsigned short checksum;
  char msg[64];
};

int main(int argc, char* argv[]) {
    // ./client localhost file.txt
    //      0       1       2
    if(argc < 2) {//ERROR => not enough arguments
        printf("NOT ENOUGH ARGUMENTS\n");
        return 1;
    }
    int done = 0;
    char *msgs[5] = {"Client: 1", "Client: 2", "Client: 3", "Client: 4", "Client: 5"};

    struct hostent* server_addr = gethostbyname(argv[1]);
    //can use localhost or hostname given by terminal

    struct sockaddr_in server;
    bzero((char*)&server, sizeof(server)); //clear allocated memory with 0's
    server.sin_family=AF_INET; //use ipv4
    bcopy((char*)server_addr->h_addr,(char*)&server.sin_addr,server_addr->h_length);
    server.sin_port=htons(5656); //pick a number, just needs to be the same on both
                                //find out what htons does -> convert numebr to tcp/ip byte order
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0); //check that the number return > 0
                                              //returns -1 if can't open the socket
    if(sockfd<0) {
        printf("ERROR CONNECTING\n");
        return 1;
    }
    socklen_t len = sizeof(struct sockaddr_in);

    while(!done) {
        //send a message
        struct Packet *r;

        //Send data

        //To send a message
        //send it
        int i;
        for(i = 0; i < 5; i++) {
          //build the packet to send
          //make space for the packet to send, also the packet to receive
          struct Packet *p = malloc(sizeof(struct Packet));
          r = malloc(sizeof(struct Packet));
          p->checksum = 17;
          p->seq = i;
          strcpy(p->msg, msgs[i]);

          //send it
          int num_bytes_sent=sendto(sockfd, p, sizeof(struct Packet), 0, (struct sockaddr*)&server, sizeof(server));

          //Receive data

          //To receive a message
          //wait on receive
          int num_bytes_received=recvfrom(sockfd, r, sizeof(struct Packet), 0, (struct sockaddr*)&server, &len);

          //print the packet received from the server
          printf("Received: ");
          printf("Sequence: %d, Message: ", r->seq);
          printf("%s,", r->msg);
          printf(" Checksum: %d\n", r->checksum);

          //check sequence
          if(r->seq <= i)
            i--; //we need to resend the message
          //dealloc the malloced spaces
          free(p);
          free(r);
        }
      done=1;
    }
    close(sockfd);

    return 0;
}
