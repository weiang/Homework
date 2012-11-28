/*************************************************************************
	> File Name: huff.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月05日 星期一 22时54分07秒
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./huff.h"

/* 创建huffman树 */
static void select_node(huff_node *root, int limit, int *s1, int *s2)
{
	int	i;

	*s1 = limit;
	for ( i = 1; i <= limit; i ++)
		if (root[i].parent == 0){
			*s2 = i;
			break;
		}
	for (i = i + 1; i < limit; i ++) {
		if (root[i].parent == 0) {
			if (root[i].weight < root[*s1].weight) {	// i节点的weight比s1节点的小
				if (root[i].weight < root[*s2].weight)		// 比较i节点的weight和s2节点的weight
					if (root[*s1].weight < root[*s2].weight)
						*s2 = i;
					else							
						*s1 = i;
				else {
					*s1 = i;
				}
			}
			else if (root[i].weight < root[*s2].weight)
				*s2 = i;
		}
	}
}


huff_node *creat_huff_tree(int occurence[], int num, element_type *word)
{
	int	m, i, s1, s2;
	huff_node	*root;

	if (num < 1)
		return NULL;
	m = 2 * num - 1;

	root = (huff_node *)malloc((m + 1) * sizeof(huff_node));

	for (i = 1; i <= num; i ++, occurence ++, word ++) {
		root[i].weight = *occurence;
		root[i].parent = 0;
		root[i].lc = 0;
		root[i].rc = 0;
		root[i].data = *word;
	}
	for (; i <= m; i ++) {
		root[i].weight = 0;
		root[i].parent = 0;
		root[i].lc = 0;
		root[i].rc = 0;
		root[i].data = 0;
	}

	for (i = num + 1; i <= m; i ++) {
		select_node(root, i - 1, &s1, &s2);
//		printf("%d %d\n", s1, s2);
		root[s1].parent = i;
		root[s2].parent = i;
		root[i].lc = s1;
		root[i].rc = s2;
		root[i].weight = root[s1].weight + root[s2].weight;
	}
//	for (i = 1; i <= m;i ++)
//		printf("%d data = %d, weight = %d, parent = %d, lc = %d, rc = %d\n", i, root[i].data, root[i].weight, root[i].parent, root[i].lc, root[i].rc);
	return root;
}

char **huff_encoding(huff_node *root, int num)
{
	int	i, start, c, f;
	char	*cd;
	char	**encode_table;

	encode_table = (char **)malloc(sizeof(char *) * (num + 1));
	cd = (char *)malloc(sizeof(char) * num);
	cd[num - 1] = '\0';
	for (i = 1; i <= num; i ++) {
		start = num - 1;
		for (c = i, f = root[i].parent; f != 0; c = f, f = root[f].parent) {
			if (root[f].lc == c)
				cd[-- start] = '0';
			else 
				cd[-- start] = '1';
		}
		encode_table[i] = (char *)malloc(sizeof(char) * (num - start));
		strcpy(encode_table[i], &cd[start]);
//		printf("%s\n", encode_table[i]);
	}
	free(cd);
	return encode_table;
}
