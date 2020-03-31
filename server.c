//
// Created by subhayu_roy on 3/31/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Port number not provided\n");
        exit(1);
    }
    int sockfd, newsockfd, portno, n;
    char buffer[255];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening Socket.\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Binding Failed\n");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("Error on accepting\n");

    int num1, num2, ans, choice;

    S: n= write(newsockfd, "Enter a number 1: ",strlen("Enter a number 1"));
    if(n<0)
        error("Error writing to socket\n");
    read(newsockfd,&num1, sizeof(int));
    printf("Client- Number 1 is : %d\n",num1);

    n= write(newsockfd, "Enter a number 2: ",strlen("Enter a number 2"));
    if(n<0)
        error("Error writing to socket\n");
    read(newsockfd,&num2, sizeof(int));
    printf("Client- Number 2 is : %d\n",num2);

    n= write(newsockfd, "Enter your choice:\n 1. +\n 2.-\n 3. *\n 4./ \n 5.Exit\n: ",strlen("Enter your choice:\n 1. +\n 2.-\n 3. *\n 4./ \n 5.Exit\n"));
    if(n<0)
        error("Error writing to socket\n");
    read(newsockfd,&choice, sizeof(int));
    printf("Client- Choice is : %d\n",choice);

    switch (choice)
    {
        case 1:
            ans=num1+num2;
            break;
        case 2:
            ans=num1-num2;
            break;
        case 3:
            ans=num1*num2;
            break;
        case 4:
            ans=num1/num2;
            break;
        case 5:
            goto Q;
            break;
    }

    write(newsockfd,&ans, sizeof(int));
    if (choice != 5)
        goto S;

    Q: close(newsockfd);
    close(sockfd);
    return 0;
}