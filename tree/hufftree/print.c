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
#include "./huff.h"

int main(int argc, char *argv[])
{
	FILE	*fp;
	char	buf[FLAG_BIT + 1];
	huff_node	*root;
	int		nsyb, i;
	int		piled_bit;

	if (argc != 2)
		return 0;

	buf[FLAG_BIT] = '\0';
	fp = fopen(argv[1], "r");
	fscanf(fp, "%d", &piled_bit);
	printf("piled_bit = %d\n", piled_bit);
	fread(buf, sizeof(char), FLAG_BIT, fp);
	fscanf(fp, "%d", &nsyb);
	printf("FILE_FLAG = %s, nsyb = %d\n", buf, nsyb);
	root = malloc(sizeof(huff_node) * 2 * nsyb);
	fread(&root[1], sizeof(huff_node), 2 * nsyb - 1, fp);
	for (i = 1; i < 2 * nsyb; i ++)
		printf("data = %d\n", root[i].data);
	while (!feof(fp)) {
		printf("%c\n", fgetc(fp));
	}
	fclose(fp);
	return 0;
}
