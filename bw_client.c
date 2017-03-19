#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "rds.h"
#include "bw.h"

// DATA_SIZE defined by bw.h

int main(){
    uint64_t pre, post;
    int clientSocket;
    char buffer[DATA_SIZE];
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
    //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_addr.s_addr = inet_addr("100.81.39.82");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;


    struct timeval t1;
    struct timeval t2;
    double elapsedTime;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    /*---- Read the message from the server into the buffer ----*/
    gettimeofday(&t1, NULL);
    CPUID;
    RDTSC(pre);
    recv(clientSocket, buffer, DATA_SIZE, 0);
    RDTSCP(post);
    CPUID;
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("Cycles used: %llu cycles\n", post - pre);
    printf("Time elapsed: %f\n", elapsedTime);
    double avg_bw = DATA_SIZE * 8.0 / elapsedTime;
    printf("Average bandwidth: %f bit/s\n", avg_bw);

    close(clientSocket);

    return 0;
}
