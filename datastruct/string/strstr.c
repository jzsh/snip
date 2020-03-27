#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strStr(char * haystack, char * needle){

    if(haystack == NULL || needle == NULL || needle[0] == '\0') {
        return 0;
    }

    char *p, *q, *m;
    int flag = 0;


    for(p = haystack; *p != '\0'; p++) {
        m = p;

        for(q = needle; *q != '\0'; q++, m++) {
            if(*m == '\0') {
                return -1; // haystack shorter
            }

            if(*m != *q) {
                flag = 1;
                break;
            }
        }

        if(flag == 0)
            return p - haystack;

        flag = 0;
    }
    return -1;
}

int strStr2(char * haystack, char * needle){

    if(haystack == NULL || needle == NULL || needle[0] == '\0') {
        return 0;
    }

    int hLen = strlen(haystack);
    int nLen = strlen(needle);
    int i = 0;
	int j = 0;

    while(i < hLen && j < nLen) {
        if(haystack[i] == needle[j]) { // 当两个字符相同，就比较下一个
            i++;
            j++;
        }
        else {
            i = i - j + 1; // 一旦不匹配，i后退并前进一步
            j = 0;
        }
    }
    if(j == nLen)
        return i - j;
    else
        return -1;
}

// https://www.cnblogs.com/dusf/p/kmp.html
// https://blog.csdn.net/v_july_v/article/details/7041827
int getNext(char *needle, int next[], int len)
{
	next[0] = -1;

	int j = 0;
	int k = -1;

	while(j < len -1) {
		if(k == -1 || needle[j] == needle[k]) {
			next[++j] = ++k;
		}
		else {
			k = next[k];
		}
	}
}

int strStr_KMP(char * haystack, char * needle){
    if(haystack == NULL || needle == NULL || needle[0] == '\0') {
        return 0;
    }

	int i = 0; // 主串的位置
	int j = 0; // 模式串的位置
    int hLen = strlen(haystack);
    int nLen = strlen(needle);

	// 计算next数组
	int next[nLen];
	getNext(needle, next, nLen);

    while(i < hLen && j < nLen) {
        if(j == -1 || haystack[i] == needle[j]) { // 当两个字符相同，就比较下一个
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if(j == nLen)
        return i - j;
    else
        return -1;
}

int main(int argc, char **argv)
{
    char *haystack = argv[1];
    char *needle = argv[2];

    printf("index of : %d\n", strStr(haystack, needle));
    printf("index of : %d\n", strStr2(haystack, needle));
    printf("index of : %d\n", strStr_KMP(haystack, needle));
}

