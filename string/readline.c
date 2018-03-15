#include <string.h>
#include <stdio.h>

int parseStr()
{
	char status[64] = "  abd-efg - ijk--abci\n";
	int len = strlen(status);
	char *buf = status;
	char *cp = NULL, *tmp = NULL, *sep = " -";

	printf("source string: |%s|\n"
	       "sep          : |-\\n|"
		   "\n", status);

	cp = strtok_r(buf, sep, &tmp);
	printf("cp=%s|, tmp=%s|\n", cp, tmp);

	cp = strtok_r(NULL, sep, &tmp);
	printf("cp=%s|, tmp=%s|\n", cp, tmp);

	cp = strtok_r(NULL, sep, &tmp);
	printf("cp=%s|, tmp=%s|\n", cp, tmp);

	cp = strtok_r(NULL, sep, &tmp);
	printf("cp=%s|, tmp=%s|\n", cp, tmp);

	cp = strtok_r(NULL, sep, &tmp);
	printf("cp=%s|, tmp=%s|\n", cp, tmp);

	cp = strtok_r(NULL, sep, &tmp);
	printf("cp=%s|, tmp=%s|\n", cp, tmp);

	cp = strtok_r(NULL, sep, &tmp);
	printf("cp=%s|, tmp=%s|\n", cp, tmp);

	printf("last char=%c\n", *(buf+len-1));
	printf("------End of parseStr --------\n");
	return 0;
}

int main(void)
{
	FILE *fp = fopen("log", "r");
	char line[512];
	char *buf = NULL;
	int len;
	char *cp = NULL;
	char *sep = " :()\n";
	int read;
	char *tmp = NULL;
	int n = 0;
	parseStr();
	/* fgets()
	 * contain line end '\n' and add a '\0'
	 */
	memset(line, 8, sizeof(line));
	while((fgets(line, 512, fp)) != NULL) {
		printf("n = %d\n------------\n", n);n++;
		printf("line=%s", line);
		buf = line;
		printf("%d\n", line[0]);
		printf("%d\n", line[1]);
		printf("%d\n", line[29]);
		printf("%d\n", line[30]);
		printf("%d\n", line[31]);
		if(line[0] == '\0') printf("\\0\n");
		/* use strtok_r instead! */
// 		cp = strtok_r(NULL, sep, &tmp);
		cp = strtok_r(buf, sep, &tmp);
		{
			printf("|%d", *(cp+5));
			printf("%d|", *(cp+6));
		}
		printf("cp=%s|buf=%s\n", cp, buf);
		cp = strtok_r(NULL, sep, &tmp);
		printf("cp=%s|buf=%s\n", cp, buf);
		cp = strtok_r(NULL, sep, &tmp);
		printf("cp=%s|buf=%s\n", cp, buf);
		if(cp != NULL)printf("%c%c%c%C", *cp, *(cp+1), *(cp+2), *(cp+3));
		if(cp) printf("|%d|\n", *(cp+3));
		if(cp) printf("|%d|\n", *(cp+4));
		if(cp) printf("|%d|\n", *(cp+5));
// 		cp = strtok_r(NULL, sep, &tmp);
// 		printf("cp=%s|buf=%s\n", cp, buf);
	}
	printf("\n-----------------------------\n");
	/* getline() */
}
