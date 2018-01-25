#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>

/* ref
 * http://blog.csdn.net/superbfly/article/details/21541117
 * http://blog.chinaunix.net/uid-29818151-id-5728506.html
 * http://blog.csdn.net/astrotycoon/article/details/8679676
 * http://blog.csdn.net/louobaichu/article/details/42744037
 * http://blog.csdn.net/lee244868149/article/details/38702367
 * http://stackoverflow.com/questions/10376056/sys-stat-s-isdirm-with-struct-dirent
 */


void rmdir_test(char *path)
{
	if(rmdir(path) != 0) {
		printf("Unable to rmdir %s, code: %d, errstring: %s\n", path, errno, strerror(errno));
	} else
		printf("rmdir %s\n", path);
}
void unlink_test(char *path)
{
	if(unlink(path) != 0) {
		printf("Unable to unlink %s, code: %d, errstring: %s\n", path, errno, strerror(errno));
		rmdir_test(path);
	} else
		printf("unlink %s\n", path);
}
void remove_test(char *path)
{
	if(remove(path) != 0) {
		printf("Unable to remove %s, code: %d, errstring: %s\n", path, errno, strerror(errno));
	}
}
void symlink_test(char *src_path, char *dst_path)
{
	if(symlink(src_path, dst_path) != 0) {
		printf("Unable to create link %s -> %s, code: %d, errstring: %s\n",
				src_path, dst_path, errno, strerror(errno));
	} else
		printf("Create link %s -> %s\n", src_path, dst_path);
	
}
static int get_file_size_time(const char *filename) {
	struct stat statbuf;
	if (stat(filename, &statbuf) == -1) {
		printf("Get stat on %s Error：%s\n",
				filename, strerror(errno));
		return (-1);
	}
	if (S_ISDIR(statbuf.st_mode)) return (1);
	if (S_ISREG(statbuf.st_mode))
		printf("%s size：%ld bytes\tmodified at %s",
			filename, statbuf.st_size, ctime(&statbuf.st_mtime));
	return (0);
}
int listDir(char *path)  //main函数的argv[1] char * 作为 所需要遍历的路径 传参数给listDir
{
	DIR		 *pDir ;  //定义一个DIR类的指针
	struct dirent	 *ent  ;   //定义一个结构体 dirent的指针，dirent结构体见上
	int		  i=0  ;
	char		  childpath[512];  //定义一个字符数组，用来存放读取的路径

// 	printf("Entering Directory :%s\n", path);
	pDir = opendir(path); //	opendir方法打开path目录，并将地址付给pDir指针
	if(!pDir) {
		printf("Open directory %s error: %s\n",
			path, strerror(errno));
		return -1;
	}
	memset(childpath, 0, sizeof(childpath)); //将字符数组childpath的数组元素全部置零

	while((ent = readdir(pDir)) != NULL) //读取pDir打开的目录，并赋值给ent, 同时判断是否目录为空，不为空则执行循环体
	{
		sprintf(childpath,"%s/%s", path,ent->d_name);
		if(ent->d_type == DT_DIR)  //d_type类型为DT_DIR (=4 表示读取的为目录)
		{
			if(!strcmp(ent->d_name,".") || !strcmp(ent->d_name,"..")) // ignore . and ..
				continue;
			listDir(childpath);  //递归读取下层的字目录内容， 因为是递归，所以从外往里逐次输出所有目录（路径+目录名），
		}
		else //如果读取的d_type类型不是 DT_DIR, 即读取的不是目录，而是文件，则直接输出 d_name, 即输出文件名
		{
			get_file_size_time(childpath);
		}
	}
// 	printf("Leaving Directory :%s\n", path);
}

int main(int argc,char *argv[])
{
	listDir(argv[1]);
	printf("\nTest symlink:\n");
	symlink_test("nonempty-dir", "lnk2_nonempty-dir");

	printf("\nTest unlink:\n");
	unlink_test("nonempty-dir");
	unlink_test("empty-dir");
	unlink_test("lnk_nonempty-dir");
	unlink_test("lnk_empty-dir");

	//
// 	if (S_ISLNK("link2")) {
// 		printf("it is a link\n");
// 		unlink("link2");
// 	}
	return 0;
}
