/*************************************************************************
	> File Name: bin_tree.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Wed 24 Oct 2012 11:50:50 PM CST
    > Describition: "Binary Tree" 
	> 在创建二叉树时应保证每个非叶节点有两个子树，只有一个子树的另一子树用空树（即0）表示，
	> 叶节点的两子树都为空, root节点的右子树为空（即0）
	>
	> Example: 1 2 4 7 0 0 8 0 0 0 3 5 0 9 0 0 6 10 0 0 0 0
	>
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX	100
typedef char	element_type;

typedef struct node {
	element_type	data;
	struct node		*lchild, *rchild;
} bin_node;

int creat_bin_tree(bin_node **root)
{
	char	c;

	scanf("%c", &c);
	if (c == '0')
		*root = NULL;
	else {
		if (!(*root = (bin_node *)malloc(sizeof **root)))
				exit(EXIT_FAILURE);
		(*root) -> data = c;
		creat_bin_tree(&((*root) -> lchild));
		creat_bin_tree(&((*root) -> rchild));
	}
	return EXIT_SUCCESS;
}

int pre_order_trverse(bin_node *root, int visit(bin_node *))
{
	if (root == NULL)
		return EXIT_SUCCESS;

	visit(root);
	pre_order_trverse(root -> lchild, visit);
	pre_order_trverse(root -> rchild, visit);
	return EXIT_SUCCESS;
}

int inter_order_trverse(bin_node *root, int visit(bin_node *))
{
	if (root == NULL)
		return EXIT_SUCCESS;
	else {
		inter_order_trverse(root -> lchild, visit);
		visit(root);
		inter_order_trverse(root -> rchild, visit);
	}
	return EXIT_SUCCESS;
}

int post_order_trverse(bin_node *root, int visit(bin_node *))
{
	if (root == NULL)
		return EXIT_SUCCESS;
	else {
		post_order_trverse(root -> lchild, visit);
		post_order_trverse(root -> rchild, visit);
		visit(root);
	}
	return EXIT_SUCCESS;
}

int	lay_order_trverse(bin_node *root, int visit(bin_node *))
{
	int	rear, front;
	bin_node	*queue[MAX];

	rear = 0;
	front = 0;
	queue[rear ++] = root;
	while (rear != front) {
		if (rear >= MAX)
			rear %= MAX;
		if (front >= MAX)
			front %= MAX;
		visit(queue[front]);
		if (queue[front] -> lchild)
			queue[rear ++] = queue[front] -> lchild;
		if (queue[front] -> rchild)
			queue[rear ++] = queue[front] -> rchild;
		front ++;
	}
	return EXIT_SUCCESS;
}

int distance(bin_node *root, char term)
{
		int	tmp;

		if (root == NULL)
			return -1;
		if (root -> data != term) {
			if ((tmp = distance(root -> lchild, term)) != -1)
				return tmp + 1;
			if ((tmp = distance(root -> rchild, term)) != -1)
				return tmp + 1;
			else return -1;
		}
		else return 0;
}

int print(bin_node *pnode)
{
	printf("%c\t", pnode -> data);
	return EXIT_SUCCESS;
}

int	height(bin_node *root)
{
	int	tmp1, tmp2;

	if (root == NULL)
		return 0;
	return (tmp1 = height(root -> lchild)) > (tmp2 = height(root -> rchild)) ? tmp1 + 1 : tmp2 +1;
}


/*	Test of order trverse functions */

int main(void)
{
	char	test;
	int	i;	
	bin_node	*root;

	creat_bin_tree(&root);
	lay_order_trverse(root, print);
	printf("\n");
	for (i = 0, test = 'A'; i < 10; test ++, i ++){
		printf("%c:\t", test);
		printf("from root to distance:%d\n", distance(root, test));
	}
	printf("\n");
/*	printf("Pre order trverse:\t");
	pre_order_trverse(root, print);
	printf("\nInter order trverse:\t");
	inter_order_trverse(root, print);
	printf("\nPost order trverse:\t");
	post_order_trverse(root, print);
	printf("\n");
*/	return EXIT_SUCCESS;
}
