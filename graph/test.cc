/*************************************************************************
	> File Name: test.cc
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月28日 星期三 00时20分35秒
    > Describition: 
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "./graph.h"
#include <stdio.h>

using namespace std;

int main(void)
{
	graph	g;
	int		*p;

	g_creat(g);
 	graph_show(g, 0);
//	dij(g, 0);
/*	for (int i = 0; i < g.vex_num; i ++) 
		printf("%d\n", g.vextices[i].parent);
*/	
//	dij_show(g, 0);
	sp_topsort(g, 0);
	sp_show(g, 0);
//	cout << is_acyclic(g) << endl;
//	topsort(g, &p);
//	print_topsort(g);
//	graph_dfs(g);
//	graph_show(g, 0);
//	graph_show(g, 1);
//	graph_bfs(g, 0);
//	graph_show(g, 2);
	return 0;
}
