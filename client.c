#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
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
    //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_addr.s_addr = inet_addr("100.81.39.82");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;


    struct timeval t1;
    struct timeval t2;
    double elapsedTime;
    gettimeofday(&t1, NULL);
    CPUID;
    RDTSC(pre);
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    RDTSCP(post);
    CPUID;
    clock_t stop = clock();
    
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("connection time: %llu cycles\n", post - pre);
    printf("Connection time elapsed in ms : %f\n", elapsedTime);
    
    /*---- Read the message from the server into the buffer ----*/
    recv(clientSocket, buffer, 1024, 0);

    /*---- Print the received message ----*/
    printf("Data received: %s",buffer);   

    gettimeofday(&t1, NULL);
    CPUID;
    RDTSC(pre);
    close(clientSocket);
    RDTSCP(post);
    CPUID;
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("tear down time: %llu cycles\n", post - pre);
    printf("Tead down time elapsed in ms : %f\n", elapsedTime);

    return 0;
}
