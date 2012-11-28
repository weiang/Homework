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
	cout << is_acyclic(g) << endl;
	print_topsort(g);
	return 0;
}
