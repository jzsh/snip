#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// Ref: https://blog.51cto.com/u_4241845/1048424

int main()
{
    int fd = open("hello.txt", O_CREAT|O_TRUNC|O_RDWR, 0666);
    if(fd < 0) { perror("open failed"); return 0; }

    char buf[] = "hello\n";
    int n = write(fd, buf, sizeof(buf));

    // dup 
    int dupFd = dup(fd);
    printf("dupFd=%d,fd=%d\n", dupFd, fd);
    n = write(dupFd, buf, sizeof(buf));

    // dup2
    int save_fd = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    printf("write to stdout\n");
    dup2(save_fd, STDOUT_FILENO);
    printf("write to stdout\n");
    close(save_fd);

    close(dupFd);
    close(fd);
}
