#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

void translate(char *str)
{
    char result[MAX] = "";
    char word[50];
    int i = 0, j = 0;

    while (sscanf(str + i, "%s", word) == 1)
    {
        for (j = 0; word[j] != '\0'; j++)
            word[j] = tolower(word[j]);

	int len = strlen(word);
        char punct = '\0';
        if (len > 0 && !isalpha((unsigned char)word[len - 1]))
        {
            punct = word[len - 1];
            word[len - 1] = '\0';
        }
        if (strcmp(word, "tbh") == 0)
            strcat(result, "to be honest ");
        else if (strcmp(word, "idc") == 0)
            strcat(result, "i dont care ");
        else if (strcmp(word, "ig") == 0)
            strcat(result, "i guess ");
        else if (strcmp(word, "tbf") == 0)
            strcat(result, "to be fair ");
        else if (strcmp(word, "atm") == 0)
            strcat(result, "at the moment ");
        else if (strcmp(word, "irl") == 0)
            strcat(result, "in real life ");
        else if (strcmp(word, "lol") == 0)
            strcat(result, "laugh out loud ");
        else if (strcmp(word, "asap") == 0)
            strcat(result, "as soon as possible ");
        else if (strcmp(word, "omg") == 0)
            strcat(result, "oh my god ");
        else if (strcmp(word, "ttyl") == 0)
            strcat(result, "talk to you later ");
        else if (strcmp(word, "idk") == 0)
            strcat(result, "i don't know ");
        else if (strcmp(word, "nvm") == 0)
            strcat(result, "never mind ");
        else
            strcat(result, word), strcat(result, " ");

        while (str[i] != ' ' && str[i] != '\0')
            i++;

        while (str[i] == ' ')
            i++;
    }

    strcpy(str, result);
}

int main()
{
    int sockfd;
    char buffer[MAX];

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Server Running...\n");

    recvfrom(sockfd, buffer, MAX, 0,
             (struct sockaddr *)&client, &len);

    printf("Received: %s\n", buffer);

    translate(buffer);

    sendto(sockfd, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr *)&client, len);

    printf("Translated message sent.\n");

    close(sockfd);

    return 0;
}

