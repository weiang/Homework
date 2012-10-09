#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int	i;
	
	for (i = 0;i < 100;i ++){
		srand(i);
		printf("%d\t%d\n", rand() % 30 + 1, rand() % 5 + 1);
	}
	printf("%ud\n", sizeof(int));
	return 0;
}

