#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main()
{
    int sockfd;
    char message[MAX], buffer[MAX];
    struct sockaddr_in server;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter sentence: ");
    fgets(message, MAX, stdin);

    sendto(sockfd, message, strlen(message) + 1, 0,
           (struct sockaddr *)&server, sizeof(server));

    recvfrom(sockfd, buffer, MAX, 0,
             (struct sockaddr *)&server, &(socklen_t){sizeof(server)});

    printf("Translated sentence: %s\n", buffer);

    close(sockfd);

    return 0;
}
