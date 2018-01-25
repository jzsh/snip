#include <stdio.h>
int main(int argc,char **argv)
{
    char *str1 = NULL;
    char *str2 = (char *)0;

    printf("content of address 0 is %s\n",(char *)0);//打印结果：content of address 0 is（null）
    printf("%s\n", (char *)NULL);                                              //段错误,为什么？

    printf("str1 is %s\n",str1);//打印结果：str1 is （null）
    fprintf(stderr, "%s\n",str1);                                                        //段错误

    printf("str2 is %s\n",str2);                                               //打印结果：str2 is （null）
    //printf("%s\n",str2);                                                        //段错误

    if(str1 == str2)
    printf("NULL address is 0\n");                                         //打印结果：NULL adress is 0
    return 0;
}
