#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd, clientfd;
    struct sockaddr_in server;
    int N, A[10][10], i, j;
    char buffer[100];

    int diagonal = 1;
    int upper = 1;
    int lower = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8054);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    listen(sockfd, 5);

    printf("Waiting...\n");

    while (1)
    {
        clientfd = accept(sockfd, NULL, NULL);

        if (clientfd < 0)
        {
            perror("accept");
            continue;
        }

        diagonal = 1;
        upper = 1;
        lower = 1;
        memset(A, 0, sizeof(A));

        if (recv(clientfd, &N, sizeof(N), 0) != sizeof(N))
        {
            close(clientfd);
            continue;
        }

        if (N < 1 || N > 10)
        {
            strcpy(buffer, "Invalid matrix size");
            send(clientfd, buffer, sizeof(buffer), 0);
            close(clientfd);
            continue;
        }

        if (recv(clientfd, A, sizeof(A), 0) <= 0)
        {
            close(clientfd);
            continue;
        }

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (i != j && A[i][j] != 0)
                    diagonal = 0;

                if (i < j && A[i][j] != 0)
                    lower = 0;

                if (i > j && A[i][j] != 0)
                    upper = 0;
            }
        }

        memset(buffer, 0, sizeof(buffer));

        if (diagonal == 1)
            strcpy(buffer, "Diagonal Matrix");
        else if (upper == 1)
            strcpy(buffer, "Upper Triangular Matrix");
        else if (lower == 1)
            strcpy(buffer, "Lower Triangular Matrix");
        else
            strcpy(buffer, "Neither");

        send(clientfd, buffer, sizeof(buffer), 0);

        printf("Sent: %s\n", buffer);

        close(clientfd);
    }

    close(sockfd);

    return 0;
}
