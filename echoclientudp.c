#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAXLINE 4096

int main(int argc, char **argv)
{
    int sockfd, n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server_IP>\n", argv[0]);
        return 1;
    }

    printf("This is the echo client. Please type some text here followed by ENTER :\n");

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        return 1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(50000);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        perror("inet_pton error");
        return 1;
    }

    /* La fonction bind est inutile dans un client, elle peut être retirée */
    /* bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)); */

    fgets(sendline, MAXLINE, stdin);
    if (sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("sendto failed");
        return 1;
    }

    n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
    if (n < 0) {
        perror("recvfrom failed");
        return 1;
    }

    recvline[n] = 0;  // Terminate the received string
    fputs(recvline, stdout);

    return 0;
}
