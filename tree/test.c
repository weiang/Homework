/*************************************************************************
	> File Name: test.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月03日 星期六 00时32分05秒
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include "./bintree.h"

int main()
{
	bin_node *root;
	bin_node	*path[MAX];
	int	i;

	creat_bin_tree(&root);
	show(root, 0);
	printf("\n");
//	lay_order_trverse(root, print);
//	inter_order_trverse(root, print);
//	printf("\n");
//	recursion_inter_order_trverse(root, print);
//	find_near_ancestor(root, 'B', 'D');
//	find_path(root, 'D', path, 0);
//	for (i = 0; path[i] != NULL; i ++)
//		print(path[i]);
//	printf("\n");	
	return 0;
}
