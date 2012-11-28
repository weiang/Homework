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
#include <time.h>
#include <math.h>

#define MAX		100
#define TABLE	50
#define	MEDIA	30
#define AD		4
typedef char	element_type;

typedef struct node {
	element_type	data;
	struct node		*lchild, *rchild;
} bin_node;

/* 
 * Random creat a binary tree 
 */
int	random_creat_bin_tree(bin_node **root, int node)
{
	static char	c = 'A';
	int	 flag;
	int	lnode, rnode;

	if (node == 0) {
		(*root) == NULL;
		return 0;
	}
	else {
		if (!((*root) = (bin_node *)malloc(sizeof(bin_node))))
			exit(EXIT_FAILURE);
		(*root) -> data = c;
		c ++;
		if (c > 'Z')
			c = c % 90 + 64;
		if (node == 1 ) {
			(*root) -> lchild = NULL;
			(*root) -> rchild = NULL;
		}
		else {
			lnode = rand() % node;
			rnode = node - lnode - 1;
			random_creat_bin_tree(&((*root) -> lchild), lnode);
			random_creat_bin_tree(&((*root) -> rchild), rnode);
		}	
	}
	return EXIT_SUCCESS;
}

static int	time_ceed = 0; 
int recursion_creat_bin_tree(bin_node **root, int node)
{
	srand(time(NULL) + time_ceed ++);
	random_creat_bin_tree(root, node);
	return EXIT_SUCCESS;
}

	

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

/*
 *  先序遍历
 */
// 递归算法
int recursion_pre_order_trverse(bin_node *root, int visit(bin_node *))
{
	if (root == NULL) {
		printf("0\t");
//		printf("%c\t", '0');
		return EXIT_SUCCESS;
	}

	visit(root);
	recursion_pre_order_trverse(root -> lchild, visit);
	recursion_pre_order_trverse(root -> rchild, visit);
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
		while (top >= 0) {
			while (ptmp != NULL) {
				visit(ptmp);
				if (ptmp -> rchild != NULL) 
					stack[top ++] = ptmp -> rchild;
				ptmp = ptmp -> lchild;
			}
		if (top >= 0) {
				top --;
				ptmp = stack[top];
			}
		}
	}
}

/* 
 * 中序遍历
 */
// 递归
int recursion_inter_order_trverse(bin_node *root, int visit(bin_node *))
{
	if (root == NULL) {
		return 0;
	}
	else {
		recursion_inter_order_trverse(root -> lchild, visit);
		visit(root);
		recursion_inter_order_trverse(root -> rchild, visit);
	}
	return EXIT_SUCCESS;
}

// 非递归
int inter_order_trverse(bin_node *root, int visit(bin_node *))
{
	bin_node	*ptmp;
	bin_node	*stack[MAX];
	int	top = 0;

	ptmp = root;
	while (top != 0 || ptmp != NULL) {
		if (ptmp) {
			stack[top ++] = ptmp;
			ptmp = ptmp -> lchild;
		}
		else {
			ptmp = stack[-- top];;
			visit(ptmp);
			ptmp = ptmp -> rchild;
		}
	}
	return 0;
}
/*
 * 后序遍历
 */
// 递归算法
int recursion_post_order_trverse(bin_node *root, int visit(bin_node *))
{
	if (root == NULL)
		return EXIT_SUCCESS;
	else {
		recursion_post_order_trverse(root -> lchild, visit);
		recursion_post_order_trverse(root -> rchild, visit);
		visit(root);
	}
	return EXIT_SUCCESS;
}

// 非递归算法
int	post_order_trverse(bin_node *root, int visit(bin_node *))
{
	bin_node	*ptmp;
	bin_node	*stack[MAX];
	int			flag[MAX], i;
	int	top = 0;
	
	stack[top ++] = root;
	for (i = 0; i < MAX; i ++)
		flag[i] = 0;
	if (root == 0)
		return 0;
	else {
		while (top != 0) {
			ptmp = stack[top - 1];
			if (flag[top - 1] == 0) {
				flag[top - 1] = 1;
				if (ptmp -> lchild != NULL)
					stack[top ++] = ptmp -> rchild;


				}
				visit(ptmp);
			}
			if (flag[top - 1] == 1) {
				flag[top - 1] = 2;

			}
	}
}

/*
 * 层序遍历
 */
static void show_ad(int n)
{
	int	i;
	for (i = 0; i < n; i ++)
		printf(" ");
}
int	lay_order_trverse(bin_node *root, int visit(bin_node *))
{
	int	rear, front;
	bin_node	*queue[MAX];
	int	f_flag, r_flag;
	int	lay = 1;
	int h;
	int	ad;

	rear = 0;
	front = 0;
	queue[rear ++] = root;
	r_flag = 0;
	printf("The 1th lay:");
	show_ad(MEDIA);
	while (rear != front) {
		if (rear >= MAX)
			rear %= MAX;
		if (front >= MAX)
			front %= MAX;
		if (queue[front] == NULL) {
			printf("0");
			show_ad(AD);
		}
		else {
			queue[rear ++] = queue[front] -> lchild;
			queue[rear ++] = queue[front] -> rchild;
			visit(queue[front]);
			show_ad(AD);
		}
		if (front == r_flag && r_flag != rear - 1) {
			printf("\nThe %dth lay:",  ++ lay);
			show_ad(MEDIA - (lay - 1) * AD + AD / 2);
			r_flag = rear - 1;
		}
		front ++;
	}
	printf("\n");
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

/* 
 * Using pre_order_trverse() to get value of k position 
 */
void pre_get_value(bin_node *root, int k, element_type *val)
{
	int		count = 0;
	bin_node	*stack[MAX];
	int		top;
	bin_node	*ptmp;
	ptmp = root;
	
	if (ptmp != NULL) {
		top = 0;
		stack[top ++] = ptmp;
		while (top != 0) {
			while (ptmp != NULL) {
				count ++;
				if (count == k) {
					*val = ptmp -> data;
					return;
				}
				if (ptmp -> rchild != NULL)
					stack[top ++] = ptmp -> rchild;
				ptmp = ptmp -> lchild;
			}
			ptmp = stack[--top];
		}
	}
}

/* 
 * Count the number of leaves of a binary tree
 */
// Nonrecursion Algorithm
int	 leaf(bin_node	*root)
{
	bin_node	*stack[MAX];
	bin_node	*ptmp;

	int	top = 0;
	int	count = 0;

	if (root == 0)
		return 0;
	else {
		stack[top ++] = root;
		while (top != 0) {
			ptmp = stack[-- top];
			if (ptmp -> rchild == NULL && ptmp -> lchild == NULL)
				count ++;
			else {
				if (ptmp -> lchild != NULL)
					stack[top ++] = ptmp -> lchild;
				if (ptmp -> rchild != NULL)
					stack[top ++] = ptmp -> rchild;
			}
		}
	}
	return count;
}

// Recursion Algorithm
int	recursion_leaf(bin_node *root)
{
	if (root == NULL)
		return 0;
	else if (root -> rchild == NULL && root -> lchild == NULL)
		return 1;
	else 
		return recursion_leaf(root -> lchild) + recursion_leaf(root -> rchild);
}

/*
 *  Delete the subtree 
 */
static void recursion_free_node(bin_node *root)
{
	if (root == NULL)
		return;
	else {
		recursion_free_node(root -> lchild);
		recursion_free_node(root -> rchild);
		root = NULL;
		free(root);
	}
}

void recursion_del_subtree(bin_node	*root, element_type	val)
{
	if (root == NULL)
		return;
	else {
		if (root -> data == val)
			recursion_free_node(root);
		else {
			recursion_del_subtree(root -> lchild, root -> lchild -> data);
			recursion_del_subtree(root -> rchild, root -> rchild -> data);
		}
	}
}

static int	find_flag = 0;
void find_path(bin_node *root, element_type p, bin_node *path[], int index)
{

	if (root -> data == p) {
		find_flag = 1;
		return;
	}

	else {
		path[index] = root;
		if (root -> lchild) 
			find_path(root -> lchild, p, path, index + 1);
		if (root -> rchild && find_flag == 0)
			find_path(root -> rchild, p, path, index + 1);
		if (find_flag == 0)
			path[index] = NULL;
	}
	return;
}

void find_near_ancestor(bin_node *root, element_type p, element_type q)
{
	bin_node	*path1[MAX], *path2[MAX];
	int i;

	find_path(root, p, path1, 0);
	for (i = 0; path1[i] != NULL; i ++)
		printf("%c\t", path1[i] -> data);
	printf("\n");
	find_flag = 0;
	find_path(root, p, path2, 0);
	for (i = 0; path2[i] != NULL; i ++)
		printf("%c\t", path2[i] -> data);

	for (i = 0; path1[i] == path2[i] && path1[i]; i ++) 
		;
	printf("\n");
	print(path1[i - 1]);
}

void show(bin_node *root, int n)
{
	int	i;
	if (root == NULL)
		return;
	for (i = 0; i < n; i ++)
		printf(" ");
	printf("%c\n", root -> data);
	show(root -> lchild, n + 1);
	show(root -> rchild, n);
}
