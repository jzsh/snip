#include <stdio.h>
int main(void)
{
       int i = 1;
       unsigned char *pointer;
       pointer = (unsigned char *)&i;
       if(*pointer)
       {
              printf("little_endian\n");
       }
       else
       {
              printf("big endian\n");
       }
       return 0;
}
