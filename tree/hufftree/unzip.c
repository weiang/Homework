/*************************************************************************
  > File Name: unzip.c
  > Author: Weiang
  > Mail: weiang@mail.ustc.edu.cn 
  > Created Time: 2012年11月10日 星期六 14时11分36秒
  > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "huff.h"
#include <string.h>

static void unzip(char *filename);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename> \n", argv[0]);
		return EXIT_FAILURE;
	}

	unzip(argv[1]);
	return EXIT_SUCCESS;
}

void unzip(char *filename)
{

	char	f_flag[FLAG_BIT + 1], decode_queue[BUFSIZE], buf[BUFSIZE];
	int		index_, mask, bit, rear, nsyb;
	int		i, k;
	FILE	*from, *to;
	char	*to_name;
	int		ptmp;
	huff_node	*root;
	int		limit, n;
	int		piled_bit;

	f_flag[FLAG_BIT] = '\0';
	to_name = (char *)malloc(sizeof(char) * (strlen(filename) + 1));
	strncpy(to_name, filename, strlen(filename) - 3);
	strcat(to_name, "uzip");			// 生成解压文件名
	from = fopen(filename, "rb");
	to = fopen(to_name, "wb");

	fscanf(from, "%d", &piled_bit);
	fread(f_flag, sizeof(char), FLAG_BIT, from);
	if (strcmp(f_flag, FILE_FLAG) != 0) {
		fprintf(stderr, "Can't identify the file %s\n", filename);
		return;
	}
	fscanf(from, "%d", &nsyb);
	root = (huff_node *)malloc(sizeof(huff_node) * 2 * nsyb);	
	fread(&root[1], sizeof(*root), 2 * nsyb - 1, from);		// 重建huffman树

	rear = 0;
	ptmp = 2 * nsyb - 1;								// 置当前节点为根节点
	while (!feof(from)) {
		n = fread(decode_queue, sizeof(char), BUFSIZE, from);
		if (n != BUFSIZE)
			limit = n * BYTE_SIZE - piled_bit;
		else 
			limit = n * BYTE_SIZE;
		for (i = 0; i < limit; i ++) {
			index_ = i / BYTE_SIZE;
			bit = i % BYTE_SIZE;
			mask = decode_queue[index_] >> bit;
			mask = mask & 0x01;
			if (mask == 0)				// 遍历huffman树直至叶节点
				ptmp = root[ptmp].lc;
			else 
				ptmp = root[ptmp].rc;
			if (root[ptmp].lc == 0 && root[ptmp].rc == 0) {
				buf[rear ++] = root[ptmp].data;		// 遇到叶节点将叶节点信息存进缓冲区
				if (rear == BUFSIZE) {				// 当缓冲区满时，将其写入解压文件，此时置当前节点为根节点 
					fwrite(buf, sizeof(char), BUFSIZE, to);
					rear = 0;
				}
				ptmp = 2 * nsyb - 1;
			}
		}
	}
	if (rear != 0) {
		fwrite(buf, sizeof(char), rear, to);
		//buf[rear] = '\0';
		//		fprintf(to, "%s", buf);
	}
	fclose(from);
	fclose(to);
}
