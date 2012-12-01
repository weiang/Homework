/*************************************************************************
	> File Name: sort.cc
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年12月01日 星期六 16时35分19秒
    > Describition: Sorting Algorthms
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

using namespace std;

void cp(item a[], item b[], int n)
{
	for (int i = 0; i < n; i ++)
		a[i] = b[i];
}

void print(item a[], int n)
{
	printf("Sorted:\n");
	for (int i = 0; i < n; i ++)
		printf("%3d ", a[i]);
	cout << endl;
}
/* 
 * Inseration Sorting 
 */
void insert_sort(item a[], int l, int r)
{
	int	i, j;

	for (i = l + 1; i <= r; i ++)
		for (j = i; j > l; j --)
			compexch(a[j], a[j - 1]);
}

/*
 * Selection Sorting
 */
void select_sort(item a[], int l, int r)
{
	for (int i = l; i < r; i ++) {
		int min = i;
		for (int j = i + 1; j <= r; j ++) {
			if (less(a[j], a[min])) 
				min = j;
			}
		exch(a[i], a[min]);
	}
}

/*
 * Bubble Sorting
 */
void bubble_sort(item a[], int l, int r)
{
	for (int i = l; i < r; i ++)
		for (int j = r; j > i; j --) 
			compexch(a[j], a[j - 1]);
}

/* 
 * Shell Sorting
 */
// Using the increment sequece 1, 4, 13, 40, 121..., which was discovered by Knuth
void shell_sort(item a[], int l, int r)
{
	int	h;
	for (h = 1; h <= (r - l) / 9; h = 3 * h + 1)
		;
	for (; h > 0; h /= 3) 
		for (int i = l + h; i <= r; i ++) {
			int j = i;
			item v = a[i];
			while (j >= l + h && less(v, a[j - h])) {
				a[j] = a[j - h];
				j -= h;
			}
			a[j] = v;
		}
}


