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

using namespace std;

int main(void)
{
	graph	g;
	int		*p;

	g_creat(g);
//	cout << is_acyclic(g) << endl;
//	print_topsort(g);
	graph_dfs(g);
	graph_show(g, 0);
	graph_show(g, 1);
	graph_bfs(g, 0);
	graph_show(g, 2);
	return 0;
}
