/*************************************************************************
	> File Name: print.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月09日 星期五 22时08分38秒
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE	1024

int main(int argc, char *argv[])
{
	FILE	*fp;
	char	buf[BUFSIZE];

	if (argc != 2)
		return 0;

	fp = fopen(argv[1], "r");
	while (!feof(fp)) {
		fread(buf, sizeof(char), BUFSIZE, fp);
		printf("%s\n", buf);
	}
	fclose(fp);
	return 0;
}
