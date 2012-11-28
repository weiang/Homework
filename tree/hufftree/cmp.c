/*************************************************************************
	> File Name: cmp.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月10日 星期六 19时35分55秒
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
	int	i, k;
	char	a, b;
	FILE	*fp1, *fp2;

	if (argc != 3)
		fprintf(stderr, "Usage : %s <cmp_file1> <cmp_file2>\n", argv[1]);
	else {
		fp1 = fopen(argv[1], "r");
		fp2 = fopen(argv[2], "r");

		i = 0;
		k = 0;
		while (!feof(fp1) && !feof(fp2)) {
			i ++;
			a = fgetc(fp1);
			b = fgetc(fp2);
			if (a != b) {
				k ++;
				printf("The %dth char(The %dth different char): %c from %s\n %c from %s\n", i, k, a, argv[1], b, argv[2]);
			}
		}
	
		if (!feof(fp1)) {
			printf("%s's char > %s' char\n", argv[1], argv[2]);
			while (!feof(fp1))
				printf("%c\n", fgetc(fp1));
			fclose(fp1);
			fclose(fp2);
			return;
		}
		if (!feof(fp2)) {
			printf("%s's char < %s' char\n", argv[1], argv[2]);
			while (!feof(fp2))
				printf("%c\n", fgetc(fp1));
			fclose(fp1);
			fclose(fp2);
			return;
		}
		printf("%s's char = %s's char\n", argv[1], argv[2]);
		fclose(fp1);
		fclose(fp2);
		return;
	}
}
