/*************************************************************************
	> File Name: th_tree.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年10月31日 星期三 16时59分59秒
    > Describition: thread tree 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char	element_type;
typedef struct node {
	int	lf, rf;
	struct node	*lc, *rc;
	element_type	data;
} th_node;

static void visit(th_node *root)
{
	if (root == NULL)
		putchar('0');
	else
		putchar(root -> data);
}

void th_creat(th_node **root, int nnode)
{
	static char	c = 'A';

	if (nnode == 0)
		*root == NULL;
	else {
			(*root) = (th_node *)malloc(sizeof(th_node));
			(*root) -> data = c;
			c ++;
		if (nnode == 1) {
			(*root) -> lc = NULL;
			(*root) -> rc = NULL;
			(*root) -> lf = 0;
			(*root) -> rf = 0;
		}
		else {
			int lnode, rnode;
			lnode = rand() % nnode;
			rnode = nnode - lnode - 1;
			th_creat(&((*root) -> lc), lnode);
			th_creat((&((*root) -> rc)), rnode);
		}
	}
}


void pre_traverse(th_node *root) 
{
	if (root == 0) {
		printf("0\t");
	}
	else {
			putchar(root -> data);
			putchar('\t');
			pre_traverse(root -> lc);
			pre_traverse(root -> rc);
	}
}

th_node	*pre;
void threading(th_node *root)
{
	if (root == NULL)
		return;
	else {
		threading((root) -> lc);
		if ((root) -> lc == NULL) {
			(root) -> lf = 1;
			(root) -> lc = pre;
		}
		if ((pre) -> rc == NULL) {
			pre -> rf = 1;
			pre -> rc = (root);
		}
		pre = root;
	//	printf("%c %d %d\n", root -> data, root -> lf, root -> rf);
		threading((root) -> rc);
	}
}

void thread_tree(th_node *root, th_node **head)
{
	th_node	**ptmp;
	ptmp = head;

	(*ptmp) = (th_node *)malloc(sizeof(th_node));
	(*ptmp) -> lf = 0;
	(*ptmp) -> rf = 1;
	(*ptmp) -> rc = (*ptmp);
	if (!(root)) 
		(*ptmp) -> lc = (*ptmp);
	else {
		pre = *ptmp;
		(*ptmp) -> lc = (root);
		threading((root));
		pre -> rf = 1;
		pre -> rc = *ptmp;
		(*ptmp) -> rc = pre;
	}
}
void in_order_traverse(th_node *root)
{
	if (root == NULL)
		return;
	else { 
		in_order_traverse(root -> lc);
		visit(root);
		in_order_traverse(root -> rc);
	}
}

void in_th_traverse(th_node *head)
{
	th_node	*root;
	root = head -> lc;

	while (root != head) {
		while (root != NULL && root -> lf == 0) {
			root = root -> lc;
		}
		visit(root);
		while (root -> rf == 1 && root -> rc != head) {
			root = root -> rc;
			visit(root);
		}
		root = root -> rc;
	}
}

int main(void)
{
	th_node	*root;
	th_node	*head;
	
	srand(time(NULL));
	th_creat(&root, 7);
	pre_traverse(root);
	printf("\n");
	in_order_traverse(root);
	printf("\n");
	
	thread_tree(root, &head);
	in_th_traverse(head);
	printf("\n");
	return 0;
}
