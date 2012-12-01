#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " sorted_num choice(0, 1)" << endl;
		return -1;
	}

	int	n = atoi(argv[1]);
	int	sw = atoi(argv[2]);
	
	int i;
	int	*a = new int[n];
	int *b = new int[n];
	if (sw)
		for (i = 0; i < n; i ++)
			a[i] = 1000 * (1.0 * rand() / RAND_MAX);
	else {
		for (i = 0; i < n; i ++) {
			cin >> a[i];
		}
	}
	
	cp(b, a, n);
	insert_sort(b, 0, n - 1);
	print(b, n - 1);
	cp(b, a, n);
	select_sort(b, 0, n - 1);
	print(b, n - 1);
	cp(b, a, n);
	bubble_sort(b, 0, n - 1);
	print(b, n - 1);
	cp(b, a, n);
	shell_sort(b, 0, n - 1);
	print(b, n - 1);
	return 0;
}


