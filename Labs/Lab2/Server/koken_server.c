//Matthew Koken

//server sends, client receives
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
    if(argc < 3) {//ERROR => not enough arguments
        printf("NOT ENOUGH ARGUMENTS\n");
        return 1;
    }

    FILE *fp = fopen(argv[2], "r"); //r/w -> write overwrites or creates
    char* str = malloc((sizeof(char)*256));
    fread(str, 1, 256, fp); //read in the file
    fclose(fp);
    //we're done, close the file

    struct hostent* server_addr = gethostbyname(argv[1]);
    //can use localhost or hostname given by terminal

    struct sockaddr_in server;
    bzero((char*)&server, sizeof(server)); //clear allocated memory with 0's
    server.sin_family=AF_INET; //use IPV4
    bcopy((char*)server_addr->h_addr,(char*)&server.sin_addr,server_addr->h_length);
    server.sin_port=htons(5656); //pick a number, just needs to be the same on both
                            //find out what htons does
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0); //check that the number return > 0
                                          //returns -1 if can't open the socket
    if(sockfd<0) {
        printf("ERROR CONNECTING\n");
        return 1;
    }
    //send the data
    int num_bytes=sendto(sockfd, str, 256, 0, (struct sockaddr*)&server, sizeof(server));

    return 0;
}
