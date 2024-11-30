#include <stdio.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#define MAXLINE 4096 

int main(int argc, char **argv) 
{ 
    int sockfd, n; 
    char sendline[MAXLINE], recvline[MAXLINE + 1]; 
    struct sockaddr_in servaddr; 

    printf("This is the echo client using TCP.\n"); 

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(50000); 
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr); 

    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)); 

    printf("Type some text here followed by ENTER : \n"); 

    fgets(sendline, MAXLINE, stdin); 

    write(sockfd, sendline, strlen(sendline)); 

    n = read(sockfd, recvline, MAXLINE); 
    recvline[n] = 0; 

    fputs(recvline, stdout);  

    return 0; 
} 
