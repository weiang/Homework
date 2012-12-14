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

void visit(elem_type & a)
{
	printf("%c ", a);
}

int main(void)
{
	graph	g;
	int *q;
	void (*p)(elem_type &);
	p = visit;
	int choice;

	graph_creat(g);
 	graph_show(g);
	cout << "Please enter the source vertices: " << endl;
	scanf("%d ", &choice);
	printf("%d\n", choice);
	sp_dij(g, choice);
	sp_show(g, choice);
	return 0;
}
