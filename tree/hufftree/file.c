/*************************************************************************
	> File Name: file.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int	i;
	char	c;
	int		max;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <filename> <fileiscale>\n", argv[0]);
		return 0;
	}
	max = atoi(argv[2]);
	fp = fopen(argv[1], "w");
	i = 0;
	srand(time(NULL));
	while (i < max) {
		c = rand() % 65 + 32;
		if (c == 91)
			i ++;
		fprintf(fp, "%c", c);
	}
	fclose(fp);
	return 0;
}
