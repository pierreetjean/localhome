#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAXLINE 4096

int main(int argc, char **argv)
{
    int sockfd, n;
    char mesg[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    printf("This is the echo server.\n");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        return 1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(50000);

    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        return 1;
    }

    for (;;) {
        n = recvfrom(sockfd, mesg, MAXLINE, 0, (struct sockaddr *) &cliaddr, &len);
        if (n < 0) {
            perror("recvfrom failed");
            return 1;
        }

        if (sendto(sockfd, mesg, n, 0, (struct sockaddr *) &cliaddr, len) < 0) {
            perror("sendto failed");
            return 1;
        }
    }

    return 0;
}
