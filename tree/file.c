/*************************************************************************
	> File Name: file.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define	MAX	1000

int main(int argc, char *argv[])
{
	FILE *fp;
	int	i;
	char	c;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 0;
	}
	fp = fopen(argv[1], "w");
	i = 0;
	srand(time(NULL));
	while (i < MAX) {
		c = rand() % 65 + 32;
		if (c == 91)
			i ++;
		fprintf(fp, "%c", c);
	}
	fclose(fp);
	return 0;
}
