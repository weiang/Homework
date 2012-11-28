/*************************************************************************
	> File Name: test.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月03日 星期六 00时32分05秒
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef char	element_type;

typedef struct node {
	element_type	data;
	struct node		*lchild, *rchild;
} bin_node;

/*
 * 创建二叉树
 */
static int	in = 0;
int creat_bin_tree(bin_node **root, int n, char *str)
{
	char	c;

	if (in == n)
		return 0;
	if (str[in] == '0') {
		*root = NULL;
		in ++;
		return 0;
	}
	else {
		if (!(*root = (bin_node *)malloc(sizeof **root)))
				exit(EXIT_FAILURE);
		(*root) -> data = str[in ++];
		(*root) -> lchild = NULL;
		(*root) -> rchild = NULL;
		creat_bin_tree(&((*root) -> lchild), n, str);
		creat_bin_tree(&((*root) -> rchild), n, str);
	}
	return EXIT_SUCCESS;
}

static void static_lay_order_trverse(bin_node *root)
{
	bin_node	*queue[MAX];
	int			rear, front;
	int			flag;
	int			i = 1;

	rear = front = flag = 0;
	queue[rear ++] = root;

	printf("第 1th 层: ");
	while (rear != front) {
		if (rear >= MAX)
			rear %= MAX;
		if (front >= MAX)
			front %= MAX;
		printf("%c ", queue[front] -> data);
		if (queue[front] -> lchild)
			queue[rear ++] = queue[front] -> lchild;
		if (queue[front] -> rchild)
			queue[rear ++] = queue[front] -> rchild;
		if (flag == front && flag != rear - 1) { 
			printf("\n第 %dth 层: ", ++ i);
			flag = rear - 1;
		}
		front ++;
	}
}

	
int main()
{
	bin_node *root;
	bin_node	*path[MAX];
	int	i;
	char		buf[MAX];
	
	gets(buf);
	creat_bin_tree(&root, strlen(buf), buf);
	static_lay_order_trverse(root);
	printf("\n");

	return 0;
}
