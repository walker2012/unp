
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>



int main(int argc, char **argv){

    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[1024];

    sockfd = socket(AF_INET, SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);

    inet_pton(AF_INET, argv[1],&servaddr.sin_addr);


    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    while(fgets(sendline, 1024,stdin) !=NULL){

        write(sockfd,sendline,strlen(sendline));
    
    }


    exit(0);
}
