/*************************************************************************
	> File Name: car_stopping.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: Sat 13 Oct 2012 04:53:39 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define N		2	
#define PRICE	5
/* 
 * Date Structures 
 */

typedef struct lnode {
	int	event_type;	// 0: car arrive
					//   1: car depart
	int	car_num;
	int	occur_time;
	struct lnode	*next;
} event_node;

typedef struct {
	int	length;
	event_node	*head;
} link_list;

typedef struct qnode {
	int	car_num;
	int	arrive_time;
	struct qnode	*next;
} queue_node, car_node;

typedef struct {
	queue_node	*front, *rear;
	int	length;
} link_queue;

typedef struct {
	int	length;
	car_node	*head;
} car_list;

void error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/* 
 * Operations
 */

/*
 * Cope with event list 
 */
/* initilization of event list */
void init_event_list(link_list	*plinklist)
{
	if ((plinklist -> head = malloc(sizeof(event_node))) == NULL)
		error("Malloc error");
	plinklist -> head -> next = NULL;
	plinklist -> length = 0;
}
/* Insert event node into event list orderly */
void order_insert(link_list *plinklist, event_node *pnode)
{
	event_node	*preptmp, *ptmp;

	if (plinklist -> length == 0) {
		plinklist -> head -> next = pnode;
		plinklist -> length ++;
		return;
	}

	preptmp = plinklist -> head;
	ptmp = plinklist -> head -> next;

	while (ptmp -> next) {
		if (ptmp -> occur_time < pnode -> occur_time) {
			preptmp = ptmp;
			ptmp = ptmp -> next;
		}
		else if (ptmp -> occur_time == pnode -> occur_time) {
			if (ptmp -> event_type < pnode -> event_type) {	/* Deal with depart event first */
				pnode -> next =ptmp;
				preptmp -> next = pnode;
				plinklist -> length ++;
			}
			else {
				preptmp = ptmp;
				ptmp = ptmp -> next;
			}
		}
		else {
			pnode -> next =ptmp;
			preptmp -> next = pnode;
			plinklist -> length ++;
			return;
		}
	}

	if (ptmp -> occur_time < pnode -> occur_time)
		ptmp -> next = pnode;
	else if (ptmp -> occur_time == pnode -> occur_time) {
		if (ptmp -> event_type > pnode -> event_type) 
			ptmp -> next = pnode;
		else {
			preptmp -> next = pnode;
			pnode -> next = ptmp;
		}
	}
	else {
		preptmp -> next = pnode;
		pnode -> next = ptmp;
	}
	plinklist -> length ++;
	return;
}
/* Delete the first node of event list */
void del_first_node(link_list *plinklist, event_node *pnode)
{
	event_node	*ptmp;

	if (plinklist -> length == 0)
		error("Linklist delete error");
	
	ptmp = plinklist -> head -> next;
	pnode -> event_type = ptmp -> event_type;
	pnode -> car_num = ptmp -> car_num;
	pnode -> occur_time = ptmp -> occur_time;
	plinklist -> head -> next = ptmp -> next;
	free(ptmp);
	plinklist -> length --;
}

/*
 * Cope with queue and queue node 
 */

/* initilization of link queue */
void init_queue(link_queue *plinkqueue)
{
	if ((plinkqueue -> front = (queue_node *)malloc(sizeof(queue_node))) == NULL)
		error("Queue malloc error");
	plinkqueue -> rear = plinkqueue -> front;
	plinkqueue -> front -> next = NULL;
	plinkqueue -> length = 0;
}
/* Enter queue */
void en_queue(link_queue *plinkqueue, queue_node *pnode)
{
	plinkqueue -> rear -> next = pnode;
	plinkqueue -> rear = pnode;
	plinkqueue -> length ++;
}
/* Depart from queue */
void de_queue(link_queue *plinkqueue, queue_node *pnode)
{
	queue_node	*ptmp;

	if (plinkqueue -> length == 0)
		error("Depart queue error");

	ptmp = plinkqueue -> front;
	plinkqueue -> front = ptmp -> next;
	pnode -> car_num = ptmp -> car_num;
	pnode -> arrive_time = ptmp -> arrive_time;
	free(ptmp);
	plinkqueue -> length --;
	
	if (plinkqueue -> length == 0)
		plinkqueue -> rear = plinkqueue -> front;
}
/* Delete queue node which is needed */
int locate_and_del_queue_node(link_queue *plinkqueue, int n, queue_node *pnode)
{	
		queue_node	*ptmp, *preptmp;

		preptmp = plinkqueue -> front;
		ptmp = plinkqueue -> front -> next;

		while (ptmp) {
			if (ptmp -> car_num == n) {
				pnode -> car_num;
				pnode -> arrive_time = ptmp -> arrive_time;
				pnode = ptmp; 
				preptmp -> next = ptmp -> next;
				free(pnode);
				plinkqueue -> length --;
				if (plinkqueue -> length == 0)
					plinkqueue -> rear = plinkqueue -> front;
				return 1;
			}
			preptmp = ptmp;
			ptmp = ptmp -> next;
		}

		return 0;
}

/* Tell if queue is empty */
int empty_queue(link_queue *plinkqueue)
{
	if (plinkqueue -> length == 0)
		return 1;
	else
		return 0;
}

/*
 *Cope with car link list and car node 
 */

/* Initilization of car link list */
void init_car_list(car_list *pcarlist)
{
	if ((pcarlist -> head = (car_node *)malloc(sizeof(car_node))) == NULL)
		error("Car list malloc error");
	pcarlist -> length = 0;
	pcarlist -> head -> next = NULL;
}

/* Delete car node in car list */
int locate_and_del_list(car_list *pcarlist, int n, car_node *pnode) 
{
	car_node	*preptmp, *ptmp;

	preptmp = pcarlist -> head;
	ptmp = preptmp -> next;

	while(ptmp != NULL) {
		if (ptmp -> car_num == n) {
			pnode -> car_num = n;
			pnode -> arrive_time = ptmp -> arrive_time;
			pnode = ptmp;
			preptmp -> next = ptmp -> next;
			free(ptmp);
			pcarlist -> length --;
			return 1;
		}
		preptmp = ptmp;
		ptmp = ptmp -> next;
	}

	return 0;
}
/* Insert car node from the head of car list */
void insert_car_list(car_list *pcarlist, car_node *pnode)
{
	pnode -> next = pcarlist -> head -> next;
	pcarlist -> head -> next = pnode;
	pcarlist -> length ++;
}

/* Tell if stop list is full */
int is_full_stop(car_list *pcarlist)
{
	if (pcarlist -> length == N)
		return 1;
	else 
		return 0;
}

/* Variables */
link_list	el;
event_node	en;
link_queue	wait_queue;
car_list	stop_list;
float	total_money = .0;
int	num = 0;

/* When car arrive */
void arrive(event_node *pnode)
{
	car_node	*ptmp;

	if (!is_full_stop(&stop_list)) {
		if ((ptmp = (car_node *)malloc(sizeof(car_node))) == NULL)
			error("Car node malloc error");
		ptmp -> car_num = pnode -> car_num;
		ptmp -> arrive_time = pnode -> occur_time;
		ptmp -> next = NULL;
		insert_car_list(&stop_list, ptmp);
	}
	else {
		if ((ptmp = (queue_node *)malloc(sizeof(queue_node))) == NULL)
			error("Queue node malloc error");
		ptmp -> car_num = pnode -> car_num;
		ptmp -> arrive_time = pnode -> occur_time;
		ptmp -> next = NULL;
		en_queue(&wait_queue, ptmp);
	}
}

/* When car depart from the stopping area */
void depart(event_node *pnode)
{
	car_node	tmpnode;
	queue_node	*ptmp;
	int	total_time;
	float	money;

	if (locate_and_del_list(&stop_list, pnode -> car_num, &tmpnode) == 1) {
		total_time = pnode -> occur_time - tmpnode.arrive_time;
		money = total_time * PRICE;
		printf("Car %d\n", pnode -> car_num);
		printf("The %dth car to leave:\n", ++ num);
		printf("Stop car into stopping area!\n");
		printf("Total time stopped in stopping area: %d\n", total_time);
		printf("Total money needed: %f\n", money);
		printf("\n");
		total_money += money;
		if (!empty_queue(&wait_queue)) {
			if ((ptmp = (queue_node *)malloc(sizeof(queue_node))) == NULL)
				error("Queue node malloc error");
			de_queue(&wait_queue, ptmp);
			ptmp -> arrive_time = pnode -> occur_time;
			insert_car_list(&stop_list, ptmp);
		}
	}
	else {
		locate_and_del_queue_node(&wait_queue, pnode -> car_num, (queue_node *)&tmpnode);
		printf("The %dth car to leave:\n", ++ num);
		printf("Stop car outside the stopping area!\n");
		printf("No money needed!\n");
		printf("\n");
	}
}

void init_stop_area(void)
{
	FILE *in;
	int	a;
	event_node	*pnode;

	init_event_list(&el);
	if ((in = fopen("input", "r")) == NULL)
		error("Open file error");
/*	while(!feof(in)) {
		if ((pnode = (event_node *)malloc(sizeof(event_node))) == NULL)
			error("Event list node malloc error");
		fscanf(in, "%c%d%d", &a, &(pnode -> car_num), &(pnode -> occur_time));
		if (a != '\0')
			printf("%c %d %d\n", a, pnode -> car_num, pnode -> occur_time);
		if (a = 'A')
			pnode -> event_type = 0;
		else if (a = 'D')
			pnode -> event_type = 1;
		else 
			break;
		pnode -> next = NULL;
		order_insert(&el, pnode);
	}
*/
	while (1) {
		if ((pnode = (event_node *)malloc(sizeof(event_node))) == NULL)
			error("Event node malloc error");
		scanf("%d%d%d", &(pnode -> event_type), &(pnode -> car_num), &(pnode -> occur_time));
		pnode -> next = NULL;
		printf("%d %d %d\n", pnode -> event_type , pnode -> car_num, pnode -> occur_time);
		if (pnode -> event_type == 2)
			break;
		order_insert(&el, pnode);
	}
	init_queue(&wait_queue);
	init_car_list(&stop_list);
}

int main(void)
{
	init_stop_area();

	while (el.length > 0) {
		del_first_node(&el, &en);
		fprintf(stderr, "%d %d %d\n", en.event_type, en.car_num, en.occur_time);
		if (en.event_type == 0)
			arrive(&en);
		else 
			depart(&en);
	}

	return 0;
}
	
	
