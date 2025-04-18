#include <stdio.h>
#include <stdlib.h>
#include <string.h
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pid, p[2];
    char buffer2[] = "hello";
    char buffer1[100];
    ssize_t N = 6; 

    if (pipe(p) < 0) {
        perror("pipe error");
        exit(1);
    }

    if ((pid = fork()) == 0) {
        
        close(p[1]); 
        read(p[0], buffer1, N);
        printf("child received: %s\n", buffer1);
        close(p[0]); 
    } else if (pid > 0) {
        
        int status;
        close(p[0]); 
        printf("parent sending: %s\n", buffer2);
        write(p[1], buffer2, N);
        close(p[1]); 
        wait(&status);
    } else {
        perror("fork error");
        exit(1);
    }

    return 0;
}