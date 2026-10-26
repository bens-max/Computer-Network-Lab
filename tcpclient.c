#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd;
    struct sockaddr_in server;
    int N, A[10][10], i, j;
    char buffer[100];

    signal(SIGPIPE, SIG_IGN);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8054);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Cannot connect to server. Is tcpserver running?\n");
        close(sockfd);
        return 1;
    }

    printf("Enter order of matrix: ");
    scanf("%d", &N);

    if (N < 1 || N > 10)
    {
        printf("Invalid matrix size\n");
        close(sockfd);
        return 1;
    }

    srand(time(0));

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            A[i][j] = rand() % 50;
    }

    printf("Generated Matrix:\n");

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%3d ", A[i][j]);
        printf("\n");
    }

    memset(buffer, 0, sizeof(buffer));

    if (send(sockfd, &N, sizeof(N), 0) != sizeof(N) ||
        send(sockfd, A, sizeof(A), 0) != sizeof(A))
    {
        printf("Failed to send matrix to server\n");
        close(sockfd);
        return 1;
    }

    memset(buffer, 0, sizeof(buffer));

    if (recv(sockfd, buffer, sizeof(buffer) - 1, 0) <= 0)
    {
        printf("No reply from server\n");
        close(sockfd);
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    printf("Matrix type: %s\n", buffer);

    close(sockfd);

    return 0;
}
