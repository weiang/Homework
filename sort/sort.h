#ifndef _SORT_H_
#define	_SORT_H_

typedef int item;

#define key(A)	(A)
#define less(A, B)	(key(A) < key(B))
#define exch(A, B)	{ item t = A; A = B; B = t; }
#define	compexch(A, B)	if (less(A, B)) exch(A, B)

extern void insert_sort(item *, int, int);
extern void select_sort(item *, int, int);
extern void bubble_sort(item *, int, int);
extern void shell_sort(item *, int, int);
extern void cp(item *, item *, int);
extern void print(item *, int);
#endif	// _SORT_H_
