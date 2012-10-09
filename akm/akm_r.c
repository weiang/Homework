#include <stdio.h>

int akm(int m, int n)
{
	printf("Akm(%d, %d)\n", m, n);
	if (n == 0)
		return akm(m - 1, 1);
	else if (m == 0)
		return n + 1;
	else return akm(m - 1, akm(m, n - 1));
}


int main(void)
{
	printf("%d\n", akm(2,1));
	return 0;
}
