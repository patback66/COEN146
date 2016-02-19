
/* Matthew Koken <mkoken@scu.edu>
   COEN 146 - Lab 3
   koken_lab3_server.c
*/
#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"

int main(int argc, char* argv[]) {
    // ./client localhost file.txt
    //      0       1       2
    if(argc < 2) {//ERROR => not enough arguments
        printf("NOT ENOUGH ARGUMENTS\n");
        return 1;
    }

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

    printf("\"QUIT!\" to exit\n");
    while(1) {
        //send a message
        char toSend[256];
        char toReceive[256];

        //receive a message from the client
        printf("Them> ");
        int num_bytes_received=recvfrom(sockfd, toReceive, 256, 0, (struct sockaddr*)&server, &len);
        printf("%s\n", toReceive);
        if(strcmp(toReceive, "QUIT!\n")==0) { //check for client quitting
            printf("Client has disconnected.\n");
            break;
        }

        //send a message
        printf("Me> ");
        fgets(toSend, 256, stdin);
        int num_bytes_sent=sendto(sockfd, toSend, 256, 0, (struct sockaddr*)&server, sizeof(server));
        if(strcmp(toSend, "QUIT!\n")==0) { //check for us wanting to quit
            printf("Exiting...\n");
            break;
        }
    }
    close(sockfd);

    return 0;
}
