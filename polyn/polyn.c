#include <stdio.h>
#include <stdlib.h>
#define OK	1
#define ERROR	0


typedef struct link_list {
	struct link_list	*next;
	float	coef;
	int	expn;
}list, list_node;
typedef list	polyn, *polyn_ptr;

static error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
/*
int creat_linklist(list *plinklist)
{
	if ((plinklist = (list *)malloc(sizeof(list_node))) == NULL)
		error("Malloc error!");
	
	plinklist -> next = NULL;
	return OK;
}
*/
/*
status get_elem(list *plinklist, int n, list_node_ptr *plistnode)
{
	list_node_ptr	ptmp;
	int	i = 0;

	ptmp = plinklist;
	while (i < n && ptmp != NULL) {
		ptmp = ptmp -> next;
		i ++;
	}
	
	if (ptmp == NULL)
		error("Get element error!");
	plistnode = ptmp;
	return EXIT_SUCCESS;
}


status list_insert(list plinklist, int n, list_node_ptr pnode)
{
	list_node_ptr	ptmp;
	
	ptmp = plinklist;
	for (i = 0;i < n - 1 && (ptmp != NULL);i ++) {
		ptmp = ptmp -> next;
	}
	if (ptmp == NULL)
		error("List insert error!");
	pnode -> next = ptmp -> next;
	ptmp -> next = pnode;
	
	return OK;
}
*/
static void print_polyn(polyn_ptr);

void creat_polyn(polyn *ppolyn, int m)
{
	int	i;
	polyn	*ptmp;

	ptmp = ppolyn;
	printf("Enter coef expn arrays:\n");

	for (i = 0;i < m;i ++) {
		if ((ptmp -> next = (polyn_ptr)malloc(sizeof(polyn))) == NULL)
			error("Creat polyn error");

		scanf("%f%d", &ptmp -> next -> coef, &ptmp -> next -> expn);
		ptmp = ptmp -> next;
		ptmp -> next = NULL;
	}
}

void print_polyn(polyn_ptr pployn)
{
	polyn_ptr	ptmp;
	
	ptmp = pployn -> next;

	if (ptmp == NULL) {
			printf("0\n");
			return;
	}
	while (ptmp && ptmp -> next != NULL) {
		printf("%0.1f * x ^ %d + ", ptmp -> coef, ptmp -> expn);
		ptmp = ptmp -> next;
	}
	if (ptmp)
		printf("%.1f * x ^ %d\n", ptmp -> coef, ptmp -> expn);
}

void add_polyn(polyn_ptr polyn_a, polyn_ptr polyn_b)
{
	polyn_ptr	polyn_c, pa, pb, polyn_tmp1, polyn_tmp2;
	float	sum;
	int	flag;

	polyn_c = polyn_a;
	polyn_tmp1 = polyn_a;
	polyn_tmp2 = polyn_b;
	pa = polyn_a -> next;
	pb = polyn_b -> next;

	while (pa && pb) {
		flag = pa -> expn - pb -> expn;
		if (flag > 0) {
			polyn_c -> next = pb;
			polyn_c = pb;
			polyn_tmp2 = pb;
			pb = pb -> next;
		}
		else if (flag < 0) {
			polyn_c -> next = pa;
			polyn_c = pa;
			polyn_tmp1 = pa;
			pa = pa -> next;
		}
		else {
			sum = pa -> coef + pb -> coef;
			if ((sum - 0.0) < 0.00001) {
				polyn_tmp1 -> next = pa -> next;
				polyn_tmp2 -> next = pb -> next;
				free(pa);
				free(pb);
				pa = polyn_tmp1 -> next;
				pb = polyn_tmp2 -> next;
			}
			else {
				polyn_c -> next = pa;
				pa -> coef = sum;
				polyn_c = pa;
				pa = pa -> next;
				polyn_tmp2 -> next = pb -> next;
				free(pb);
				pb = polyn_tmp2 -> next;
			}
		}
	}
	if (pa != NULL)
		polyn_c -> next = pa;
	if (pb != NULL)
		polyn_c -> next = pb;
}

/* Test add_polyn */
/*
int main(void)
{
	polyn	pa,pb;
	
	creat_polyn(&pa, 4);
	creat_polyn(&pb, 4);

	add_polyn(&pa, &pb);
	printf("F(x1) + F(x2) is:\n");
	print_polyn(&pa);
	
	return OK;
}	

*/
void reverse(polyn *ppolyn)
{
	polyn_ptr	ptmp;
	
	ptmp = ppolyn -> next;

	while (ptmp != NULL) {
		ptmp -> coef = -ptmp -> coef;
		ptmp = ptmp -> next;
	}
}

void sub_polyn(polyn_ptr pa, polyn_ptr pb)
{
	reverse(pb);
	add_polyn(pa, pb);
}


/* Test of sub_polyn */
/*
int main(void)
{
	polyn	pa, pb;
	creat_polyn(&pa, 4);
	creat_polyn(&pb, 4);
	
	sub_polyn(&pa, &pb);
	printf("F(x1) - F(x2) is :\n");
	print_polyn(&pa);
	return 0;
}
*/

void mul_polyn(polyn_ptr polyn_a, polyn_ptr polyn_b, polyn_ptr polyn_mul)
{
	polyn_ptr	pa, pb, pc;
	polyn	polyn_c;

	pb = polyn_b -> next;

	while (pb) {
		pc = &polyn_c;
		if ((pb -> coef - 0.0) > 0.00001 || (pb -> coef - 0.0) < -0.00001) {
			for (pa = polyn_a -> next; pa != NULL; pa = pa -> next) {
				if ((pa -> coef - 0.0) < 0.00001)
					continue;
				pc -> next = (polyn *)malloc(sizeof(polyn));
				if (pc -> next == NULL)
					error("Malloc error");
				pc = pc -> next;
				pc -> coef = pa -> coef * pb -> coef;
				pc -> expn = pa -> expn + pb -> expn;
				pc -> next = NULL;
			}
			print_polyn(&polyn_c);
			add_polyn(polyn_mul, &polyn_c);
		}
		pb = pb -> next;
	}
}

/* Test mul_polyn() */
/*
int main(void)
{
	polyn	pa, pb, mul;

	creat_polyn(&pa, 4);
	creat_polyn(&pb, 4);
	
	mul.next = (polyn_ptr)malloc(sizeof(polyn));
	mul.next -> next = NULL;
	mul.next -> coef = 0.0;
	mul.next -> expn = 1;
	
	mul_polyn(&pa, &pb, &mul);
	printf("F(x1) * F(x2) = :\n");
	print_polyn(mul.next);

	return 0;
}
*/
void list_choice(void)
{
	int	choice;

	printf("***************Cope with Polyn function***************\n");
	printf("1.Add two polyns\n");
	printf("2.Mul two polyns\n");
	printf("3.Sub two polyns\n");
	printf("4.Quit\n");
	printf("******************************************************\n");
}

void add(void)
{
	int	nterms;
	polyn	pa, pb;

	printf("Please enter polyn 1's term number\n");
	scanf("%d", &nterms);
	creat_polyn(&pa, nterms);
	printf("F(x1) = ");
	print_polyn(&pa);
	printf("Please enter polyn2's term number\n");
	scanf("%d", &nterms);
	creat_polyn(&pb, nterms);
	printf("F(x2) = ");
	print_polyn(&pb);
	
	add_polyn(&pa, &pb);
	printf("F(x1) + F(x2) = ");
	print_polyn(&pa);
}

void sub(void)
{
	int	nterms;
	polyn	pa, pb;
	
	printf("Please enter polyn 1's term number\n");
        scanf("%d", &nterms);
        creat_polyn(&pa, nterms);
	printf("F(x1) = ");
	print_polyn(&pa);
        printf("Please enter polyn2's term number\n");
        scanf("%d", &nterms);
        creat_polyn(&pb, nterms);
	printf("F(x2) = ");
	print_polyn(&pb);

	sub_polyn(&pa, &pb);
	printf("F(x1) - F(x2) = ");
	print_polyn(&pa);
}

void mul(void)
{
	int     nterms;
        polyn   pa, pb, pmul;

	pmul.next = (polyn *)malloc(sizeof(list_node));
	pmul.next -> next = NULL;
	pmul.next -> coef = 0.0;
	pmul.next -> expn = 0;

        printf("Please enter polyn 1's term number\n");
        scanf("%d", &nterms);
        creat_polyn(&pa, nterms);
	printf("F(x1) = ");
	print_polyn(&pa);
        printf("Please enter polyn2's term number\n");
        scanf("%d", &nterms);
        creat_polyn(&pb, nterms);
	printf("F(x2) = ");
	print_polyn(&pb);

	mul_polyn(&pa, &pb, &pmul);
	printf("F(x1) * F(x2) = ");
	print_polyn(&pmul);
}

int main(void)
{
	int	choice;

	list_choice();	
	printf("Please enter your choice:\n");
	scanf("%d", &choice);	
	while((choice != 4) && choice < 4 && choice > 0) {
		if (choice == 1) {
			add();
		}
		else if (choice == 2)
			mul();
		else {
			sub();
		}
		list_choice();
		printf("Please enter your choice:\n");
		scanf("%d", &choice);
	}
//	printf("Error choice has receieved!\n");
//	printf("Quit abnormally!\n");
	printf("*********************************************\n");
	printf("Thank you for your using!\n");
	printf("*********************************************\n");
	return 0;
}
/*
			case 2:
				mul();
				break;
			case 3:
				sub();
				break;
		}
		choice = list_choice();
	}
	return 0;
}
*/	
