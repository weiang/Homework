/*************************************************************************
  > File Name: zip.c
  > Author: Weiang
  > Mail: weiang@mail.ustc.edu.cn 
  > Created Time: 2012年11月05日 星期一 23时45分54秒
  > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./huff.h"

// 统计字符在文件中出现的频率 
static void get_occurence(int *occur, element_type *word, int *len, const char*filename)
{
	unsigned char	buf[BUFSIZE];
	int		tmp[ASIIC];
	FILE	*fp;
	int	i, n, k = 0;
	
	memset(tmp, 0, sizeof(tmp));
	fp = fopen(filename, "r");
	while (!feof(fp)) {
		n = fread(buf, sizeof(char), sizeof(buf), fp);
		for (i = 0; i < n; i ++) {
			tmp[buf[i]] ++;
		}
	}
	for (i = 0; i < ASIIC;i ++) {
		if (tmp[i] != 0) {
			word[k] = i;
			occur[k ++] = tmp[i];
			//			printf("%d %d %c\n", k - 1, occur[k - 1], word[k - 1]);
		}
	}
	*len = k;
	//	printf("%d", k);
	//	for (i = 0; i < k; i ++)
	//		printf("%d\n", occur[i]);
	fclose(fp);
}

static void zip(char *filename);

int	main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 0;
	}
	else {
		zip(argv[1]);
		return 0;
	}
}



// 压缩文件filename生成filename.zip
static void zip(char *filename)
{
	int occur[ASIIC], nsyb;	// nsyb表示实际需要编码的符号数
	// occur存储各被编码字符的频率
	element_type	word[ASIIC];
	char	**encoding_table, zipped[BUFSIZE];
	char	buf[BUFSIZE];	// 被编码文件的缓存
	FILE	*from, *to;
	huff_node	*root;
	int	n, j, i, k, l, limit = BUFSIZE * BYTE_SIZE;
	int len, index_, bit, mask, rear;
	char	bit_queue[BUFSIZE];

	strcpy(zipped, filename);
	strcat(zipped, ".zip");
	memset(bit_queue, 0, sizeof(bit_queue));
	memset(occur, 0, sizeof(occur));
	get_occurence(occur, word, &nsyb, filename);
	//	for (i = 0; i < nsyb; i ++)
	//		printf("%d\n", occur[i]);
	root = creat_huff_tree(occur, nsyb, word);
	encoding_table = huff_encoding(root, nsyb);
	from = fopen(filename, "r");
	to = fopen(zipped, "w");

	/*
	 * 文件格式
	 */
	/* piled_bit	多填充的位
	 *AW			文件标志
	 * nsyb			叶节点的个数
	 * 编码文件
	 */
	fprintf(to, "%d", 0);		// 存储piled_bit
	fprintf(to, FILE_FLAG);
	fprintf(to, "%d", nsyb);
	fwrite(&root[1], sizeof(*root), 2 * nsyb - 1, to);	// 将huffman树的各个节点的信息以结构体存储到压缩文件中

	rear = 0;
	while (!feof(from)) {
		n = fread(buf, sizeof(char), BUFSIZE, from);
		for (j = 0; j < n; j ++) {
			for (k = 1; k <= nsyb; k ++)
				if (buf[j] == root[k].data)
					break;
			len = strlen(encoding_table[k]);
// 将字符串encode以位模式存进编码缓存队列
			for (i = 0; i < len; i ++) {
				if (rear == BYTE_SIZE * BUFSIZE) {
					fwrite(bit_queue, sizeof(char), BUFSIZE, to);
					memset(bit_queue, 0, sizeof(bit_queue));
					rear = 0;
					}
				if (encoding_table[k][i] == '0')
					rear ++;
				else {
					index_ = rear / BYTE_SIZE;
					bit = rear % BYTE_SIZE;
					mask = 0x1 << bit;
					bit_queue[index_] |= mask;
					rear ++;
				}
			}
		}
	}
	if (rear != 0){
		if (rear % BYTE_SIZE == 0) {
			fwrite(bit_queue, sizeof(char), rear / BYTE_SIZE, to);
			//			for (i = 0; i < rear / BYTE_SIZE; i ++){
			//				fprintf(to, "%c", bit_queue[i]);
			//				printf("%c\n", bit_queue[i]);
			//			}
			rewind(to);
			fprintf(to, "%d", 0);
		}
		else {
			fwrite(bit_queue, sizeof(char), rear / BYTE_SIZE + 1, to);
			//	fprintf(to, "%c", bit_queue[0]);
			//			for (i = 0; i < rear / BYTE_SIZE + 1; i ++){
			//				fprintf(to, "%c", bit_queue[i]);
			//				printf("%c\n", bit_queue[i]);
			//			}
			rewind(to);
			fprintf(to, "%d", BYTE_SIZE - rear % BYTE_SIZE);
		}
	}
	fclose(from);
	fclose(to);
	return;
}
