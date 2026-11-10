#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){

    int sockfd, clientfd;
    struct sockaddr_in server,client;
    socklen_t addr_len;
    char filename[100];
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    print("File Server Running");

    while(1){
        addr_len = sizeof(client);
        clientfd = accept(sockfd, (struct sockaddr *)&client, &addr_len);

        if (fork == 0){
            close(sockfd);
            recv(clientfd, filename, sizeof(filename),0);
            FILE *fp = fopen(filename, "r");
            sprintf(buffer, "Server PID:%d\n\n", getpid());
            send(clientfd,buffer, strlen(buffer), 0);
            if (fp == NULL){
                strcpy(buffer, "Requested file does not exist\n");
                send(clientfd, buffer, sizeof(buffer), 0);
            }
            else{
                while(fgets(buffer, BUFFER_SIZE, fp)!=NULL){
                    send(clientfd, buffer, strlen(buffer), 0);
                }
                fclose(fp);
            }
            close(clientfd);
            exit(0);
        }
        close(clientfd);
    }
    return 0;
}