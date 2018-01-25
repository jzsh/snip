#include<unistd.h>
main()
{
	char *argv[]={"update.sh", "license", NULL};
// 	char *envp[]={"PATH=/home/gjz/git_home/c/update.sh", NULL};
	execve("/home/gjz/git_home/c/update.sh", argv, NULL);
}
