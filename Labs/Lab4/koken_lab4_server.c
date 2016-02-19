
/* Matthew Koken <mkoken@scu.edu>
   COEN 146 - Lab 4
   koken_lab4_server.c
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
    char *msgs[5] = {"Server: 1", "Server: 2", "Server: 3", "Server: 4", "Server: 5"};

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
    bind(sockfd, (struct sockaddr*)&server, sizeof(server)); //take control of the port
    socklen_t len = sizeof(struct sockaddr_in);

    while(!done) {
        //send a message
        struct Packet *r;
        int i;
        for(i = 0; i < 5; i++) {
          //make space for the packet
          r = malloc(sizeof(struct Packet));
          //Receive data
          //receive a message from the client
          int num_bytes_received=recvfrom(sockfd, r, sizeof(struct Packet), 0, (struct sockaddr*)&server, &len);

          //Check for sequence & checksum
          if(r->checksum == 17 && r->seq == i){
            //packet was good
            printf("Received: ");
            printf("Sequence: %d, Message: ", r->seq);
            printf("%s,", r->msg);
            printf(" Checksum: %d\n", r->checksum);
            //modify the message -> convert to upper
            int j;
            for(j = 0; j < 64; j++) {
              r->msg[j]=toupper(r->msg[j]);
            }
            r->seq++;
          } else {
            //not what we expected, send the same packet back for resend
            i--; //get ready for resend
          }

          //send a message
          int num_bytes_sent=sendto(sockfd, r, sizeof(struct Packet), 0, (struct sockaddr*)&server, sizeof(server));

          free(r);
        }
        done=1;
    }
    close(sockfd);

    return 0;
}
