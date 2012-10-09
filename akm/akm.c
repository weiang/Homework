#include <stdio.h>

static count = 0;

int akm(int m, int n)
{
	int	m1[50], n1[50];
	int	cp;

	cp = 0;
	m1[0] = m;
	n1[0] = n;

	do {
		while (m1[cp] > 0) {	// Push (m, n) array into stack until m1[cp] = 0 
			while (n1[cp] > 0) {	// Push (m, n) array into stack until n1[cp] = 0
				cp ++;
				m1[cp] = m1[cp - 1];
				n1[cp] = n1[cp - 1] - 1;
				printf("Akm(%d, %d)\n", m1[cp], n1[cp]);
			}
		/* Compute akm(m - 1, 1) */
			m1[cp] = m1[cp] - 1;
			n1[cp] = 1;
			printf("Akm(%d, %d)\n", m1[cp], n1[cp]);
		}
		cp --;

		/* Compute akm(m - 1, n + 1) */
		m1[cp] = m1[cp] - 1;
		n1[cp] = n1[cp + 1] + 1;
		printf("Akm(%d, %d)\n", m1[cp], n1[cp]);
	} while(cp > 0 || m1[cp] > 0);
	
	return n1[0] + 1;
}

int main(void)
{
	printf("%d\n",  akm(2, 1));
	return 0;
}

