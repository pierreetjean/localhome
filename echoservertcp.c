#include <stdio.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#define MAXLINE 4096 
#define LISTENQ 1024 
 
int main(int argc, char **argv) 
{ 
    int sockfd, connfd, n; 
    char mesg[MAXLINE]; 
    struct sockaddr_in servaddr; 
     
    printf("This is the echo server using TCP.\n"); 
     
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
     
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(50000); 
     
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)); 
    listen(sockfd, LISTENQ); 
     
    for ( ; ; ){ 
        connfd = accept(sockfd, (struct sockaddr *) NULL, NULL); 
         
        n = read(connfd, mesg, MAXLINE); 
        mesg[n] = 0; 
        fputs(mesg, stdout); 
         
        write(connfd, mesg, strlen(mesg)); 
         
        close(connfd); 
         
    } 
} 
