/*=============================================================================
#     FileName: nonblocktcp.c
#         Desc: set the connetfd unblock
#       Author: licaibiao
#   LastChange: 2017-02-14
=============================================================================*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<signal.h>
#include <fcntl.h>

#define MAXLINE 256
#define PORT	6666


void process_out(int signo)
{
    exit(EXIT_SUCCESS);
}


void write_func(int pid, int fd)
{
    char* write = "I am server";

    printf("write id = %d\n",pid);

    signal(SIGUSR1,process_out);
    while(1)
    {
        sleep(1);
        send(fd,write,strlen(write)+1,0);
    }

}


void read_func(int pid, int fd)
{
    char readbuff[MAXLINE];
    int n = 0;

    printf("read id = %d \n",pid);

    memset(&readbuff,0,sizeof(readbuff));

    while(1)
    {
        n = recv(fd, readbuff, MAXLINE, 0);
        if(n > 0)
        {
            printf("server recv data: %s \n",readbuff);
        }
        else if(n == 0)
        {
            break;
        }
        sleep(1);
        //printf("===\n");
    };

    printf("exit read function\n");
    kill(pid, SIGUSR1);
    exit(EXIT_SUCCESS);
}


int main(void)
{
    int listenfd,connetfd;
    int on = 1;
    socklen_t addrlen = 0;
    int flags;
    pid_t pid, pid_child, pid_send;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;


    if ((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("create socket err \n");
    }

    addrlen = sizeof(struct sockaddr_in);
    memset(&server_addr, 0, addrlen);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }


    if( bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }


    if( listen(listenfd, 10) == -1)
    {
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    printf("wait client accpt \n");
    while(1)
    {

        if( (connetfd = accept(listenfd, (struct sockaddr*)&client_addr, &addrlen)) == -1)
        {
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }

        /* set NONBLOCK */
        flags = fcntl(connetfd, F_GETFL, 0);
        fcntl(connetfd, F_SETFL, flags | O_NONBLOCK);

        signal(SIGCHLD, SIG_IGN);
        pid = fork();
        if(pid == -1)
        {
            printf("fork err \n");
        }

        if(pid == 0)
        {
            pid_child = fork();
            if(pid_child == 0)
            {
                pid_send = getpid();
                read_func(pid_send, connetfd);
            }
            else
            {
                pid_send = getpid();
                write_func(pid_send,connetfd);
            }
        }

    }
}