#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "rds.h"
#include "bw.h"
#include <stdlib.h>

// DATA_SIZE defined by bw.h

int main(){
    int welcomeSocket, newSocket;
    char* buffer;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    uint64_t pre, post;
    struct timeval t1, t2;
    double elapsedTime;
    socklen_t addr_size;

    buffer = malloc(DATA_SIZE);
    if (!buffer)
    {
      // buffer not initialized
      fprintf(stderr, "Could not initialize buffer to be size %d. Got %x.\n", DATA_SIZE, buffer);
      return 1;
    }

    memset(buffer, 0, DATA_SIZE);

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(7891);
    /* Set IP address to localhost */
    
    //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.101");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*---- Bind the address struct to the socket ----*/
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    /*---- Listen on the socket, with 5 max connection requests queued ----*/
    if(listen(welcomeSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");

    /*---- Accept call creates a new socket for the incoming connection ----*/
    addr_size = sizeof serverStorage;

    while(1)
    {
        newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
        printf("accept a connection\n");
        gettimeofday(&t1, NULL);
        CPUID;
        RDTSC(pre);
        printf("%d\n",send(newSocket,buffer,DATA_SIZE,0));
        RDTSCP(post);
        CPUID;
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
        printf("roundtrip time took %llu cycles\n", post - pre);
        printf("roundtrip time took %f ms\n", elapsedTime);
        printf("transfer rate was %f bit/s\n", DATA_SIZE * 8.0 / elapsedTime);
        close(newSocket);
        sleep(1);
    }


    return 0;
}
