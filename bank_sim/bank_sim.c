#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLOSE_TIME	9 * 60 * 60

/*
 * Data structure
 */
/* Node of event link list */
typedef struct list_node {
	int	occur_time;	// Time event happend
	int	event_type;	/* 0: customer depart
				   1 ~ 4: customer go to queue 1 ~ 4
				 */
	struct	list_node	*next;
} event_list_node;

/* Event link list */
typedef struct {
	int	length;	// The length of event link list
	event_list_node	*head;
} event_list;

/* Node of link queue */
typedef struct queue_node {
	int	arrive_time;	// Customer arrive time 
	int	duration;	// Time needed for deal with things 
	struct queue_node	*next;
} event_queue_node;

/* Event link queue */
typedef struct {
	event_queue_node	*front, *rear;
	int	length;
} event_queue;

/*
 * Operations
 */
/* Error handling */
void error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/* Operations for link list */
void init_event_list(event_list *peventlist)
{
	peventlist -> head = (event_list_node *)malloc(sizeof(event_list_node));
	if (peventlist -> head == NULL)
		error("Malloc error");
	peventlist -> length = 0;
	peventlist -> head -> next = NULL;
}

/* Decide which of the two events happend first */
int cmp(event_list_node *ea, event_list_node *eb)
{
	int	result;
	result = ea -> occur_time - eb -> occur_time;

	if (result > 0)
		return 1;
	else if (result == 0)
		return 0;
	else
		return -1;

}

void order_insert(event_list *peventlist, event_list_node *pnode)
{
	int	result;
	event_list_node	*ptmp, *preptmp;

	preptmp = peventlist -> head;
	if (peventlist -> length == 0) {
		preptmp -> next = pnode;
		peventlist -> length ++;
		return;
	}
	ptmp = preptmp -> next;
	
	while (ptmp -> next) {
		result = cmp(ptmp, pnode);
		switch (result) {
			case -1:
				ptmp = ptmp -> next;
				preptmp = preptmp -> next;
				break;
			case 0: 
				pnode -> occur_time ++;
				break;
			case 1:
				pnode -> next = ptmp;
				preptmp -> next = pnode;
				peventlist -> length ++;
				return;
		}
	}
	result = cmp(ptmp, pnode);
	if (result == -1) {
		ptmp -> next = pnode;
	}
	else if (result == 0) {
		pnode -> occur_time ++;
		ptmp -> next = pnode;
	}
	else {
		pnode -> next = ptmp;
		preptmp -> next = pnode;
	}
	peventlist -> length ++;
}
	

void del_first_list_node(event_list *peventlist, event_list_node *pnode)
{
	event_list_node	*ptmp, *p;
	
	if (peventlist -> length == 0)
		error("Event link list error");

	ptmp = peventlist -> head;
	(pnode) -> occur_time = ptmp -> next -> occur_time;
	(pnode) -> event_type = ptmp -> next -> event_type;
	p = ptmp -> next;
	ptmp -> next = ptmp -> next -> next;
	(pnode) -> next = NULL;
	peventlist -> length --;
	free(p);
}

/* Operation for link queue */
void init_queue(event_queue *peventqueue)
{
	peventqueue -> front = (event_queue_node *)malloc(sizeof(event_queue_node));
	if (!peventqueue -> front)
		error("Malloc error");
	peventqueue -> rear = peventqueue -> front;
	peventqueue -> front -> next = NULL;
	peventqueue -> length = 0;
}

void en_queue(event_queue *peventqueue, event_queue_node *pnode)
{
	peventqueue -> length ++;
	peventqueue -> rear -> next = pnode;
	peventqueue -> rear = pnode;
}

void de_queue(event_queue *peventqueue, event_queue_node *pnode)
{
	event_queue_node	*ptmp;

	if (peventqueue -> length == 0)
		error("Queue delete error");
	pnode -> arrive_time = peventqueue -> front -> next -> arrive_time;
	pnode -> duration = peventqueue -> front -> next -> duration;
	ptmp = peventqueue -> front -> next;
	peventqueue -> front -> next = peventqueue -> front -> next -> next;
	peventqueue -> length --;
	free(ptmp);
	if (peventqueue -> length == 0)
		peventqueue -> rear = peventqueue -> front;
}
FILE	*out;
static  seed = 0;
void random_time(int minute, int *durtime,  int *intertime)
{
	seed ++;
	srand(time(NULL) + seed);
	*durtime = rand() % 30 + 1;	// Time needed for deal with things 1 ~ 30
	*intertime = rand() % minute + 1;	// later customer's arrive time related to event occur time 1 ~ 5

	fprintf(out, "%d\t%d\n", *durtime, *intertime);
}

int minnum(event_queue q[])
{
	int	min = q[1].length;
	int	i, k = 1;

	for (i = 1;i < 5;i ++) {
		if (q[i].length == 0)
			return i;
		if (min > q[i].length)
			k = i;
	}
	return k;
}

/* 
 * Variables
 */
event_list	ev;	// Event link list
event_list_node	en;	// Event get from event link list to be dealt with
event_queue	queue[5];	// Queue[0]: customer arrive queue
				// Queue[1 ~ 4]: customers leave from windows 1 ~ 4
event_queue_node	customer;	// Customer that will be insert into queues
long	total_time;	// Time all customers spent in bank
int	total_customers;	// The number of costomers 

void open_for_day(void)
{
	int	i;
	event_list_node	*ptmp;

	total_time = 0;
	total_customers = 0;
	init_event_list(&ev);
	
	if ((ptmp = (event_list_node *)malloc(sizeof(event_list_node))) == NULL)
		error("Malloc error");
	ptmp -> occur_time = 0;
	ptmp -> event_type = 0;
	ptmp -> next = NULL;

	order_insert(&ev, ptmp);
	for (i = 1;i < 5;i ++)
		init_queue(&queue[i]);
}

void customer_arrived(void)
{
	int	duratime, intertime;
	int	i,t;
	event_list_node	*ptmp;
	event_queue_node *pnode;

	++ total_customers;
	/* Time 8:00 ~ 10:00 */
	if (0 < en.occur_time && en.occur_time < 7200)
		random_time(5, &duratime, &intertime);
	/* Time 10:00 ~ 14:30 */
	else if (7200 <= en.occur_time && en.occur_time < 23400)
		random_time(10, &duratime, &intertime);
	/* Time 14:30 ~ 17:00 */
//	if (23400 <= en.occur_time && en.occur_time < 32400)
	else
		random_time(6, &duratime, &intertime);

	t = (en.occur_time + intertime);	// Next customer's arrive time
	if (t < CLOSE_TIME) {	// If bank not close door, insert event node to event list 
		ptmp = (event_list_node *)malloc(sizeof(event_list_node));
		if (ptmp == NULL)
			error("Malloc error");
		ptmp -> occur_time = t;
		ptmp -> event_type = 0;
		ptmp -> next = NULL;
		order_insert(&ev, ptmp);
	}

	if ((pnode = (event_queue_node *)malloc(sizeof(event_queue_node))) == NULL)
		error("Malloc error");
	pnode -> arrive_time = en.occur_time;
	pnode -> duration = duratime;
	i = minnum(queue);	// Get the shortest queue
	en_queue(&queue[i], pnode);	// Get the arrived customer enter the shortest queue
	if (queue[i].length == 1) {	// Drive queue[i]'s header leave event insert into the event list
		ptmp = (event_list_node *)malloc(sizeof(event_list_node));
		if (ptmp == NULL)
			error("Malloc error");
		ptmp -> occur_time = en.occur_time + duratime;
		ptmp -> event_type = i;
		ptmp -> next = NULL;
		order_insert(&ev, ptmp);
		}
}

void customer_departure(void)
{
	int	i;
	event_list_node	*pnode;

	i = en.event_type;
	de_queue(&queue[i],&customer);
       	total_time += (en.occur_time - customer.arrive_time);
//	printf("%ld	%d	%d\n", total_time, en.occur_time, customer.arrive_time);	
	if (queue[i].length != 0) {
		if ((pnode = (event_list_node *)malloc(sizeof(event_list_node))) == NULL)
			error("Malloc error");
		pnode -> occur_time = queue[i].front -> next -> duration + en.occur_time;
		pnode -> event_type = i;
		pnode -> next = NULL;
		order_insert(&ev, pnode);
	}
}

void bank_simulation(void)
{
	open_for_day();
	while (ev.length != 0) {
		del_first_list_node(&ev, &en);
		if (en.event_type == 0){
				customer_arrived();
		}
		else
			customer_departure();
	}

	printf("The Total time: %ld\n", total_time);
	printf("The Total customers: %d\n", total_customers);
	printf("The average time is %f\n", (float)total_time / total_customers);
}

int main(void)
{
	out = fopen("output", "w");
	bank_simulation();
	fclose(out);
	return EXIT_SUCCESS;
}
