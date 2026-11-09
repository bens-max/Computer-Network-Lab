#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd, clientfd;
    struct sockaddr_in server;
    int A[10][10],N,i,j;
    char buffer[100];

    int diagonal = 1;
    int upper = 1;
    int lower = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    printf("Waiting for client\n");

    clientfd = accept(sockfd, NULL, NULL);

    recv(clientfd, &N, sizeof(N), 0);
    recv(clientfd, A, sizeof(A), 0);

    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            if (i!=j && A[i][j]!=0)
            diagonal = 0;
            if (i<j && A[i][j])
            lower = 0;
            if (i>j && A[i][j])
            upper = 0;
        }
    }

    if (diagonal == 1){
        strcpy(buffer, "Diagonal Matrix");
    }
    else if (lower == 1){
        strcpy(buffer,"Lower Tringular Matrix");
    }
    else if (upper == 1){
        strcpy(buffer,"Upper Triangular Matrix");
    }
    else
        strcpy(buffer,"Neither");
    
    send(clientfd,buffer,sizeof(buffer),0);

    close(clientfd);
    close(sockfd);

    return 0;
}