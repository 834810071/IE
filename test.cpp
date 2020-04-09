#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc,char * argv[])
{
    struct timeval start,end;
    int times = argc > 1 ? atoi(argv[1]):10000;
    int stat;
    int fd;
    int childpid;
    int i;


    for(i=0 ;i<1; i++){
        if(childpid = fork())
            break;
    }

    if(childpid == -1){
        perror("failed to fork\n");
        return 1;
    }

    FILE *fp = NULL;
    fp = fopen("tmpfp.dat","ab");
    if(fp == NULL) {
        system("touch tmpfp.dat");
    }

    gettimeofday(&start,NULL);
    if(childpid > 0){
        char *buf = (char*)malloc(times);
        for(int i = 0;i < times;++i) {
            buf[i] = 'a';
        }
        strcat(buf,"\n");

        for(i=0; i<10; i++){
            usleep(1000);
            fwrite(buf,strlen(buf),1,fp);
        }
        wait(&stat);
    }else{
        char *buf = (char*)malloc(times);
        for(int i = 0;i < times;++i) {
            buf[i] = 'b';
        }
        strcat(buf,"\n");
        for(i=0; i<10; i++){
            usleep(1000);
            fwrite(buf,strlen(buf),1,fp);
        }
    }
    fclose(fp);

    gettimeofday(&end,NULL);
    int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("UseTime: MicroSeconds:%d us and Seconds:%d s\n",timeuse,end.tv_sec-start.tv_sec);
    return 0;
}


