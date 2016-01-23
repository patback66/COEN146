//Matthew Koken

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

    char* str = malloc((sizeof(char)*256));

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
    socklen_t len;
    int num_bytes=recvfrom(sockfd, str, 257, 0, (struct sockaddr*)&server, &len);

    FILE *fp = fopen(argv[2], "w"); //r/w -> write overwrites or creates
    fwrite(str, 1, 256, fp); //write the file
    //Done writing
    fclose(fp);

    return 0;
}

