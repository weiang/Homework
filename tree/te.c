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
	int		n;
	char	c;
	FILE *fp;
	int	i;

	if (argc != 2) {		
		fprintf(stderr, "Usage %s <filescale> \n", argv[1]);
	}

	n = atoi(argv[1]);
	fp = fopen(argv[1], "w");
	c = 'A'; 
	for (i = 0; i < n; i ++) {
		if (c - 'A' >= 26)
			c = 'A';
		fprintf(fp, "%c", c);
		c ++;
	}
	fclose(fp);
	return 0;
}
