//file:fcntl
int main()
{
    pid_t pid;
    fd = open("test.txt",O_RDWR|O_APPEND);
    if (fd == -1)
    ##printf("open err/n");
    printf("fd = %d",fd);
    printf("fork!/n");
    fcntl(fd, F_SETFD, 1);
    char *s="ooooooooooooooooooo";
    pid = fork();
    if(pid == 0)
    execl("ass", "./ass", &fd, NULL);
    wait(NULL);
    write(fd,s,strlen(s));
    close(fd);
    return 0;
}
//ass 源代码
int main(int argc, char *argv[])
{
    int fd;
    printf("argc = %d ",argc);
    fd = *argv[1];
    printf("fd = %d",fd);
    char *s = "zzzzzzzzzzzzzzzzzzz";
    write(fd, (void *)s, strlen(s));
    close(fd);
    return 0;
}
