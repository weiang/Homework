/*************************************************************************
	> File Name: huff.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Fri 26 Oct 2012 12:56:19 PM CST
    > Describition: "Huffman codes"
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define	MAX	100

typedef char	element_type;

typedef struct {
	unsigned int	weight;
	unsigned int	parent, lchild, rchild;
	element_type	data;
} huff_node, *huff_tree_ptr;

typedef char ** huffman_code;
/*
 * 从huff_tree_ptr 数组中选出两个weight最小的端点
 */
static void select_node(huff_tree_ptr ptree, int n, int *s1, int *s2)
{
	int	i;
	int	min_weight1 = 100, min_weight2 = 100;	// 假设min_weight1 <= min_weight2

	for (i = 1; i <= n; i++, ptree ++) {
		if (ptree -> parent == 0) {
			if (ptree -> weight < min_weight1) {
				min_weight2 = min_weight1;
				min_weight1 = ptree -> weight;
			}
			else if (ptree -> weight < min_weight2)
				min_weight2 = ptree -> weight;
		}
	}
	*s1 = min_weight1;
	*s2 = min_weight2;
	return;
}

/*void recursion_pre_order_trverse(huff_tree_ptr root)
{
	if (root -> rchild == 0 && root -> lchild == 0)
		return;
	else {
		printf("%d\t", root -> weight);
		recursion_pre_order(
*/

void huffman_codeing(huff_tree_ptr *ptree, huffman_code *pcode, int *w, int n, element_type *et)
{	// w存放n个字符的权值，构造huffman树，并求出n个字符的huffman编码
	
	huff_tree_ptr	ptmp;
	huff_tree_ptr	stack[MAX];
	int				top = 0;int	m;
	huff_tree_ptr	p;
	char	*cd;
	int	i, c, f, start;
	int	s1, s2;

	if (n <= 1)
		return;
	m = 2 * n - 1;
	(*ptree) = (huff_tree_ptr)malloc((m + 1) * sizeof (huff_node));
	for (p = *ptree + 1, i = 1; i <= n; ++ i, ++ p, ++ w, ++ et) {
		p -> weight = *w;
		p -> parent = 0;
		p -> lchild = 0;
		p -> rchild = 0;
		p -> data = *et;
	}
	for (; i <= m; ++ i, ++p) {
		p -> weight = 0;
		p -> parent = 0;
		p -> lchild = 0;
		p -> rchild = 0;
	}
	for ( i = n + 1; i <= m; i ++) {
		select_node(*ptree, i - 1, &s1, &s2);
		(*ptree)[s1].parent = i;
		(*ptree)[s2].parent = i;
		(*ptree)[i].lchild = s1;
		(*ptree)[i].rchild = s2;
		(*ptree)[i].weight = (*ptree)[s1].weight + (*ptree)[s2].weight;
	}
// 检查huffman树的生成状态
	
	ptmp = (*ptree)[m];
	
	while (top >= 0) {
		while (ptmp -> rchild != 0 || ptmp -> lchild != 0) {
			printf("%d\t", ptmp -> weight);
			if (ptmp -> rchild)
				stack[top ++] = (*ptree)[ptmp -> rchild];
			ptmp = (*ptree)[ptmp -> lchild];
		}
		if (top >= 0)
			ptmp = stack[-- top];
	}

/* 
 * 从叶子到根逆向求每个字符的huffman编码
 */
	(*pcode) = (huffman_code)malloc((n + 1) * sizeof(char *));
	cd = (char *)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i ++) {
		start = n - 1;
		for (c = i, f = (*ptree)[i].parent; f != 0; c = f, f = (*ptree)[f].parent)			if ((*ptree)[f].lchild == c)
					cd[-- start] = '0';
			else 
					cd[-- start] = '1';
		(*pcode)[i] = (char *)malloc((n - start) * sizeof(char));
		printf("%s\n", (*pcode)[i]);
		strcpy((*pcode)[i], &(cd[start]));
	}
	free(cd);
}


/*
 *  Test 
 */

int main(void)
{
	huff_tree_ptr	hufftree;
	huffman_code	huffcode;
	int	i;

	int	arr[6] = {1, 1, 2, 2, 3, 3};
	element_type s[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

	huffman_codeing(&hufftree, &huffcode, arr, 6, s);
	for (i = 1; i <= 6; i ++)
		printf("%s\n", huffcode[i]);
	return 0;
}
