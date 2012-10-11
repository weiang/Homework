#include <stdio.h>
#include <stdlib.h>

static	num = 0;
void hannoi(int n, int a, int b, int c)
{
	if (n == 1)
		printf("%4d: move %d from %c to %c\n", ++num, n, a, c);

	else {
		hannoi(n - 1, a, c, b);
		printf("%4d: move %d from %c to %c\n", ++num, n, a, c);
	       	hannoi(n - 1, b, a, c);
	}
}

int main(void)
{
	int	n;

	printf("Enter n:\n");
	scanf("%d", &n);
	hannoi(n, 'A', 'B', 'C');
	printf("Total movements %d!\n", num);
}
