#include <stdio.h>
#include <stdlib.h>

#define MAX	100

static	num = 0;
struct argue {
	int	num;
	char	from;
	char	by;
	char	to;
};

typedef struct {
	int	pc;
	struct argue	arg;
} record;

record	rec[MAX];
int	index_ = 0;

void hannoi(int n, int a, int b, int c, int pc)
{																	// 1
	int	i;
	if (n == 1)	{													// 2
/*		index_ --;
		for (i = index_ - 1;i >= 0; i --) 
			printf("%d, %d, %c, %c, %c\n", rec[i].pc, rec[i].arg.num, rec[i].arg.from, rec[i].arg.by, rec[i].arg.to);
		printf("\n");
	//		printf("%4d: move %d from %c to %c\n", ++num, n, a, c);	// 3
*/		}
	else {															// 4	
		rec[index_].pc = 6;
		rec[index_].arg.num = n-1;
		rec[index_].arg.from = a;
		rec[index_].arg.by = c;
		rec[index_].arg.to = b;
		index_ ++;
		for (i = index_ - 1; i >= 0; i --)
			printf("%d, %d, %c, %c, %c\n", rec[i].pc, rec[i].arg.num, rec[i].arg.from, rec[i].arg.by, rec[i].arg.to);
		printf("--\n");			
		hannoi(n - 1, a, c, b, 6);
		for (i = index_ - 1; i >= 0; i --)
			printf("%d, %d, %c, %c, %c\n", rec[i].pc, rec[i].arg.num, rec[i].arg.from, rec[i].arg.by, rec[i].arg.to);	
		printf("--\n");								// 5
//		printf("%4d: move %d from %c to %c\n", ++num, n, a, c);		// 6
		rec[index_].pc = 8;
		rec[index_].arg.num = n-1;
		rec[index_].arg.from = b;
		rec[index_].arg.by = a;
		rec[index_].arg.to = c;
		index_ ++;
		for (i = index_ - 1; i >= 0; i --)
			printf("%d, %d, %c, %c, %c\n", rec[i].pc, rec[i].arg.num, rec[i].arg.from, rec[i].arg.by, rec[i].arg.to);
		printf("--\n");
		hannoi(n - 1, b, a, c, 8);
		for (i = index_ - 1; i >= 0; i --)
			printf("%d, %d, %c, %c, %c\n", rec[i].pc, rec[i].arg.num, rec[i].arg.from, rec[i].arg.by, rec[i].arg.to);
																	// 7
		printf("--\n");		
	}																// 8
	index_ --;
/*	for (i = index_ - 1; i >= 0; i --)
		printf("%d, %d, %c, %c, %c\n", rec[i].pc, rec[i].arg.num, rec[i].arg.from, rec[i].arg.by, rec[i].arg.to);
	printf("--\n");
*/
}																	// 9

int main(void)
{
	int	n;
	int i;

	printf("Enter n:\n");
	scanf("%d", &n);	
	rec[index_].pc = 0;
	rec[index_].arg.num = n;
	rec[index_].arg.from = 'A';
	rec[index_].arg.by = 'B';
	rec[index_].arg.to = 'C';
	index_ ++;
	for (i = index_ - 1; i >= 0; i --)
			printf("%d, %d, %c, %c, %c\n", rec[i].pc, rec[i].arg.num, rec[i].arg.from, rec[i].arg.by, rec[i].arg.to);
	printf("--\n");
	hannoi(n, 'A', 'B', 'C', 0);
//	printf("Total movements %d!\n", num);
}
