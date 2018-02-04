#include <string.h>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <error.h>
#include <stdio.h>

using namespace std;

void error(const char* msg){
    perror(msg);
    exit(0);
}

int main(int argc, char* argv[]){

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    if(argc < 2){
        cout << "ERROR, no port provided." << endl;
        exit(1);
    }


    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0){
        cout << "ERROR opening the socket." << endl;
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) error("ERROR ON BINDING.");

    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, 
            (struct sockaddr *) &cli_addr, 
            &clilen);
    if(newsockfd < 0) error("ERROR ON ACCEPT.");

    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if(n < 0) error("ERROR READING FROM SOCKET.");

    cout << "the message got is: " << buffer << endl;

    n = write(newsockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");

    close(newsockfd);
    close(sockfd);

    return 0;    


}

