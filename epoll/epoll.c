/*
 * =====================================================================================
 *
 *       Filename:  epoll.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月29日 17时39分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define MAXEPOLLSIZE    1000
#define MAXLINE 1000
#define SA const struct sockaddr
int main(int argc, char **argv){

    int listenfd,connfd,sockfd,efd,new_fd;
    int curfds,nfds,n,m;
    char buf[MAXLINE];
    socklen_t clilen;
    struct sockaddr_in cliaddr,servaddr;
    struct epoll_event ev;
    struct epoll_event events[MAXEPOLLSIZE];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket:%d\n",listenfd);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    bind(listenfd,(SA *) &servaddr,sizeof(servaddr));

    listen(listenfd,5);

    efd = epoll_create(MAXEPOLLSIZE);
    printf("created:%d\n",efd);
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = listenfd;
    epoll_ctl(efd,EPOLL_CTL_ADD, listenfd, &ev);


    curfds = 1;
    while(1){

        nfds = epoll_wait(efd, events,curfds,-1 ); 
        printf("waited: %d\n",nfds);
        for(n = 0;n<nfds;n++){

            if(events[n].data.fd == listenfd){
                printf("epoll_waited:new connetciotn:\n");
                clilen = sizeof(cliaddr);
                new_fd = accept(listenfd,NULL,0);
                printf("accpeted: %d\n",new_fd);
                if(new_fd < 0){
                    printf("error accept\n");
                    continue;
                } else{
                    printf("new accept\n");
                }
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = new_fd;
                epoll_ctl(efd,EPOLL_CTL_ADD, new_fd, &ev);
                curfds++;
            }else{
                m = read(events[n].data.fd, buf,MAXLINE);
                printf("readed: %d\n",m);
                //buf[m-1] = '\0';
                printf("%s\n",buf);

            }

        }
    }
    
    return 0;
}

