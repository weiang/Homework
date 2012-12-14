/*************************************************************************
	> File Name: test.cc
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年12月03日 星期一 00时33分18秒
    > Describition: 
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "item.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <sorted number> <choice(0, 1)>" << endl;
		return -1;
	}

	int n, choice;
	n = atoi(argv[1]);
	choice = atoi(argv[2]);

	item	*a = new item[n];
	if (choice == 0)
		rand_init(a, n);
	else 
		scan_init(a, n);
	select_sort(a, 0, n - 1);
	show(a, 0, n - 1);
	return 0;
}
