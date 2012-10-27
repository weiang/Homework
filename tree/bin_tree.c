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

/*
 * 创建二叉树
 */
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

/*
 *  先序遍历
 */
// 递归算法
int recursion_pre_order_trverse(bin_node *root, int visit(bin_node *))
{
	if (root == NULL) {
		printf("%c\t", '0');
		return EXIT_SUCCESS;
	}

	visit(root);
	pre_order_trverse(root -> lchild, visit);
	pre_order_trverse(root -> rchild, visit);
	return EXIT_SUCCESS;
}

// 非递归算法
int pre_order_trverse(bin_node *root, int visit(bin_node *))
{
	int	top = 0;
	bin_node	*stack[MAX];
	bin_node	*ptmp;

	ptmp = root;

	if (ptmp == NULL)
		return EXIT_FAILURE;

	else {
		visit(ptmp);
		while (top > 0) {
			if (ptmp -> rchild != NULL) {
			stack[top ++] = ptmp -> rchild;
		else {
			ptmp = ptmp -> lchild;

/* 
 * 中序遍历
 */
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

/*
 * 后序遍历
 */
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

/*
 * 层序遍历
 */
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

/* 
 * 求树上任一节点到树根的距离
 */
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

/*
 * 求树的深度
 */
int	height(bin_node *root)
{
	int	tmp1, tmp2;

	if (root == NULL)
		return 0;
	return (tmp1 = height(root -> lchild)) > (tmp2 = height(root -> rchild)) ? tmp1 + 1 : tmp2 +1;
}

/*
 * 二叉树复制的递归和非递归算法
 */
// 递归
void recursion_bin_tree_copy(bin_node *t_from, bin_node **pt_to)
{
	if (t_from == NULL) {
		*pt_to = NULL;
	}
	else {
		*pt_to = (bin_node *)malloc(sizeof *pt_to);
		(*pt_to) -> data = t_from -> data;
		recursion_bin_tree_copy(t_from -> lchild, &((*pt_to) -> lchild));
		recursion_bin_tree_copy(t_from -> rchild, &((*pt_to) -> rchild));
	}
}
// 非递归
void bin_tree_copy(bin_node *t_from, bin_node **pt_to)
{
	bin_node	*stack_from[MAX];
	bin_node	*stack_to[MAX];
	int			status[MAX];
	int			top;
	bin_node	*p_from, *p_to;

	// Initilization
	(*pt_to) = (bin_node *)malloc(sizeof(bin_node));
	(*pt_to) -> data = t_from -> data;
	top = 0;
	status[top] = 0;
	stack_from[top] = t_from;
	stack_to[top] = *pt_to;
	top ++;

	while (top >= 0) {
		p_from = stack_from[top - 1];
		p_to = stack_to[top - 1];
		if (status[top - 1] == 0) {
			status[top - 1] = 1;
			if (p_from -> lchild) {
				p_to -> lchild = (bin_node *)malloc(sizeof(bin_node));
				p_to -> lchild -> data = p_from -> lchild -> data;
				stack_from[top] = p_from -> lchild;
				stack_to[top] = p_to -> lchild;
				status[top] = 0;
				top ++;
			}
			else {
				p_to -> lchild = NULL;
			}
		}
		else if (status[top - 1] == 1) {
			status[top - 1] = 2;
			if (p_from -> rchild) {
				p_to -> rchild = (bin_node *)malloc(sizeof(bin_node));
				p_to -> rchild -> data = p_from -> rchild -> data;
				stack_from[top] = p_from -> rchild;
				stack_to[top] = p_to -> rchild;
				status[top] = 0;
				top ++;
			}
			else {
				p_to -> rchild = NULL;
			}
		}
		else {
			top --;
		}
		}	
	}

/* 
 * 调换树的左右子树
 */
// 递归算法
void recursion_exchange_bin_tree_node(bin_node *root)
{
	bin_node	*ptmp;

	if (root == NULL)
		return;
	else {
		ptmp = root -> lchild;
		root -> lchild = root -> rchild;
		root -> rchild = ptmp;
		recursion_exchange_bin_tree_node(root -> lchild);
		recursion_exchange_bin_tree_node(root -> rchild);
	}
}

//  非递归算法
void exchange_bin_tree_node(bin_node *root)
{
	bin_node	*stack[MAX];
	bin_node	*ptmp, *p;
	int	top = 0;
	stack[top ++] = root;

	while (top > 0) {
		ptmp = stack[top - 1];
		top --;
		if (ptmp -> lchild && ptmp -> rchild) {
			p = ptmp -> rchild;
			ptmp -> rchild = ptmp -> lchild;
			ptmp -> lchild = p;
			stack[top ++] = ptmp -> rchild;
			stack[top ++] = ptmp -> lchild;
		}
		else if (ptmp -> lchild == NULL && ptmp -> rchild == NULL) {
		}
		else if (ptmp -> lchild) {
			stack[top ++] = ptmp -> lchild;
			ptmp -> rchild = ptmp -> lchild;
			ptmp -> lchild = NULL;
		}
		else {
			stack[top ++] = ptmp -> rchild;
			ptmp -> lchild = ptmp -> rchild;
			ptmp -> rchild = NULL;
		}
	}
}

		
		
/*	Test of order trverse functions */

int main(void)
{
	char	test;
	int	i;	
	bin_node	*root;
	bin_node	*copynode;

	creat_bin_tree(&root);
	pre_order_trverse(root, print);
	printf("\n");
//	bin_tree_copy(root, &copynode);
//	pre_order_trverse(copynode, print);
//	printf("\n");
	exchange_bin_tree_node(root);
//	exchange_bin_tree_node(copynode);
	pre_order_trverse(root, print);
	printf("\n");
	exchange_bin_tree_node(root);
	recursion_exchange_bin_tree_node(root);
	pre_order_trverse(root, print);
	printf("\n");
//	pre_order_trverse(copynode, print);
//	printf("\n");
// test for distace 
/*	for (i = 0, test = 'A'; i < 10; test ++, i ++){
		printf("%c:\t", test);
		printf("from root to distance:%d\n", distance(root, test));
	}
	printf("\n");
*/
// test for trverse
/*	printf("Pre order trverse:\t");
	pre_order_trverse(root, print);
	printf("\n");
	pre_order_trverse(copynode, print);
	printf("\nInter order trverse:\t");
	inter_order_trverse(root, print);
	printf("\n");
	inter_order_trverse(copynode, print);
	printf("\nPost order trverse:\t");
	post_order_trverse(copynode, print);
	printf("\n");
	post_order_trverse(copynode, print);
*/	printf("\n");
	return EXIT_SUCCESS;
}
