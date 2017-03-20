#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "rds.h"

#define NUM_OF_EXPERIMENT 1000

int main(){
    uint64_t pre, post;
    int clientSocket;
    char buffer[1024] = "111";
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
    //serverAddr.sin_addr.s_addr = inet_addr("10.160.21.140");
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.101");
    //serverAddr.sin_addr.s_addr = inet_addr("100.81.39.82");
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    
    struct timeval t1;
    struct timeval t2;
    double elapsedTime;
    double totalTime;
    double totalCycle;
    
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    for(int i =0; i < NUM_OF_EXPERIMENT; i++){

        char received[1024];

        gettimeofday(&t1, NULL);
        CPUID;
        RDTSC(pre);
        int count_send = send(clientSocket,buffer,1024,0);
        printf("Byte count sended is %d\n",count_send);
        int count = recv(clientSocket, received, 1024, 0);
        if(count != 1024){
            printf("Data received is %s\n",received);
            printf("Data byte count is %d\n",count);
            printf("recv failed\n");
            //return -1;
        }
        //printf("Data received: %s\n",received);   
        //printf("Data byte count: %d\n",count);   
        RDTSCP(post);
        CPUID;
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
        printf("Round trip : %llu cycles\n", post - pre);
        printf("Round trip time elapsed in ms : %f\n", elapsedTime);
        totalTime += elapsedTime;
        totalCycle += (double)(post-pre) / NUM_OF_EXPERIMENT;
    }

    totalTime = totalTime / NUM_OF_EXPERIMENT;
    //totalCycle = totalCycle / NUM_OF_EXPERIMENT;
    printf("Averaged round trip : %f cycles\n", totalCycle);
    printf("Averaged Round trip time elapsed in ms : %f\n", totalTime);
    
    close(clientSocket);
    
    return 0;
}
