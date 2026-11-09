#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<arpa/inet.h>

int main(){

    int sockfd, N, A[10][10], i,j;
    struct sockaddr_in server;
    char buffer[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Enter order of matrix:\n");
    scanf("%d", &N);
    srand(time(0));
    printf("Generated Matrix:\n");
    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            A[i][j] = rand() % 50;
            printf("%3d", A[i][j]);
        }
        printf("\n");
    }
    send(sockfd,&N,sizeof(N),0);
    send(sockfd,A,sizeof(A),0);
    recv(sockfd,buffer,sizeof(buffer),0);
    printf("Matrix type:%s\n", buffer);

    close(sockfd);
    return 0;
}