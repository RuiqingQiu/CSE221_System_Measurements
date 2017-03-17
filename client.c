#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include "rds.h"

int main(){
    uint64_t pre, post;
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(7891);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;


    clock_t start = clock();
    CPUID;
    RDTSC(pre);
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    RDTSCP(post);
    CPUID;
    clock_t stop = clock();
    printf("%d\n", CLOCKS_PER_SEC);
    double elasped = (double)(stop - start) * 1000.0 /CLOCKS_PER_SEC;
    printf("Time elapsed in ms : %f", elasped);
    printf("connection time: %llu cycles\n", post - pre);
    
    /*---- Read the message from the server into the buffer ----*/
    recv(clientSocket, buffer, 1024, 0);

    /*---- Print the received message ----*/
    printf("Data received: %s",buffer);   

    CPUID;
    RDTSC(pre);
    close(clientSocket);
    RDTSCP(post);
    CPUID;
    printf("tear down time: %llu cycles\n", post - pre);

    return 0;
}
