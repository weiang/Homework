/*************************************************************************
	> File Name: te.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月06日 星期二 23时55分09秒
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char	buf[1024];
	int		n;
	FILE *fp;

	int	i;
	if (argc != 2) {		
		fprintf(stderr, "Usage %s <filename> \n", argv[1]);
	}
	fp = fopen(argv[1], "r");
	n = fread(buf, sizeof(char), 500, fp);
	for (i = 0; i  < strlen(buf); i ++)
		printf("%c\n", n, buf[i]);
	fclose(fp);
	return 0;
}
