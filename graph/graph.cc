/*************************************************************************
	> File Name: graph.cc 
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2012年11月26日 星期一 23时41分40秒
    > Describition: 
 ************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./graph.h"

using namespace std;

static void dn_creat(graph &g);
static void udn_creat(graph &g);
static void udg_creat(graph &g);
static void dg_creat(graph &g);


/* 
 * 创建无向图 
 */
static void udg_creat(graph &g)
{
	int		i, j;
	int		vi, vj, w;
	arc_node	*ptmp;

	cout << "Enter vertices and arc number: " << endl;
	scanf("%d%d", &g.vex_num, &g.arc_num);

	// Initl=ilize vertices information
	for (i = 0; i < g.vex_num; i ++) {
		g.vextices[i].info = i + 1;
		g.vextices[i].first_arc = NULL;
		g.vextices[i].in_arc = NULL;
	}
	
	cout << "Enter vertices relations:(vi vj weight) " << endl;
	// Creat arc from the information inputed
	for (i = 0; i < g.arc_num; i ++) {
		cin >> vi >> vj >> w;
		vi --;
		vj --;
		ptmp = new arc_node;
		ptmp -> adj_vex = vj;
		ptmp -> w = w;
		ptmp -> next_arc = g.vextices[vi].first_arc;
		g.vextices[vi].first_arc = ptmp;
		ptmp = new arc_node;
		ptmp -> adj_vex = vi;
		ptmp -> w = w;
		ptmp -> next_arc = g.vextices[vj].first_arc;
		g.vextices[vj].first_arc = ptmp;
	}
}

/* 
 * 创建有向图 
 */
static void dg_creat(graph &g)
{
	int		vi, vj, w;
	cout << "Enter vertices and arc number: " << endl;
	cin >> g.vex_num >> g.arc_num;

	// 初始化顶点节点
	for (int i = 0; i < g.vex_num; i ++) {
		g.vextices[i].info = i + 1;
		g.vextices[i].first_arc = NULL;
		g.vextices[i].in_arc = NULL;
	}
	
	// 获取弧信息
	cout << "Enter vertices relations:(vi vj weight) " << endl;
	for (int i = 0; i < g.arc_num; i ++) {
		cin >> vi >> vj >> w;
		vi --;
		vj --;
		arc_node	*tmp = new arc_node;
		tmp -> adj_vex = vj;
		tmp -> w = w;
		tmp -> next_arc = g.vextices[vi].first_arc;
		g.vextices[vi].first_arc = tmp;
	
		tmp = new arc_node;
		tmp -> adj_vex = vi;
		tmp -> w = w;
		tmp -> next_arc = g.vextices[vj].in_arc;
		g.vextices[vj].in_arc = tmp;
	}
}

/*
 * 创建有向网
 */
static void dn_creat(graph &g)
{
	cout << "Enter vertices and arc number: " << endl;
	cin >> g.vex_num >> g.arc_num;

	for (int i = 0; i < g.vex_num; i ++) {
		g.vextices[i].info = i + 1;
		g.vextices[i].first_arc = NULL;
		g.vextices[i].in_arc = NULL;
	}

	cout << "Enter vertices relation:(vi vj weight) " << endl;
	for (int i = 0; i < g.arc_num; i ++) {
		int	rlt[3];
		cin >> rlt[0] >> rlt[1] >> rlt[2];
		rlt[0] --;
		rlt[1] --;
	
		// Insert <rlt[0], rlt[1]> into rlt[0]'s out-adj list
		arc_node	*tmp = new arc_node;
		tmp -> adj_vex = rlt[1];
		tmp -> w = rlt[2];
		tmp -> next_arc = g.vextices[rlt[0]].first_arc;
		g.vextices[rlt[0]].first_arc = tmp;
		
		// Insert <rlt[0], rlt[1]> into rlt[1]'s in-adj list
		tmp = new arc_node;
		tmp -> adj_vex = rlt[0];
		tmp -> w = rlt[2];
		tmp -> next_arc = g.vextices[rlt[1]].in_arc;
		g.vextices[rlt[1]].in_arc = tmp;
	}
}

/* 
 * 创建无向网
 */
static void udn_creat(graph &g)
{
	cout << "Enter vertices and arc number: " << endl;
	cin >> g.vex_num >> g.arc_num;

	for (int i = 0; i < g.vex_num; i ++) {
		g.vextices[i].info = i + 1;
		g.vextices[i].first_arc = NULL;
		g.vextices[i].in_arc = NULL;
	}
	cout << "Enter vertices relations:(vj vj weight) " << endl;
	for (int i = 0; i < g.arc_num; i ++) {
		int vi, vj, w;
		cin >> vi >> vj >> w;
		vi --;
		vj --;
		arc_node	*tmp = new arc_node;
		tmp -> adj_vex = vj;
		tmp -> w = w;
		tmp -> next_arc = g.vextices[vi].first_arc;
		g.vextices[vi].first_arc = tmp;

		tmp = new arc_node;
		tmp -> adj_vex = vi;
		tmp -> w = w;
		tmp -> next_arc = g.vextices[vj].first_arc;
		g.vextices[vj].first_arc = tmp;
	}
}

	
// 构建图
void g_creat(graph &g)
{
	cout << "Enter Graph kind: " << endl;
	scanf("%d", (int *)&(g.kind));
//	cout << g.kind << endl;
	switch (g.kind) {
		case	DG:	
			dg_creat(g);
			break;
		case	DN:	
			dn_creat(g);
			break;
		case	UDG:
			udg_creat(g);
			break;
		case	UDN:
			udn_creat(g);
			break;
	}
}

/* 广度优先遍历 */
void g_bfs(graph &g, int vex)
{
	int		leave;
	arc_node	*tmp;
	int		rear, front;
	int		queue[MAX];

	vex --;
	rear = front = 0;
	g.vextices[vex].dis = 0;
	g.vextices[vex].parent= NIL;
	g.vextices[vex].visited = 1;
	printf("%d ", g.vextices[vex].info);
	queue[rear ++] = vex;
	while (front != rear) {
		leave = queue[front ++];
		tmp = g.vextices[leave].first_arc;
		while (tmp != NULL) {
			if (!g.vextices[tmp -> adj_vex].visited) {
				printf("%d ", g.vextices[tmp -> adj_vex].info);
				g.vextices[tmp -> adj_vex].visited = 1;
				g.vextices[tmp -> adj_vex].dis = g.vextices[leave].dis + 1;
				g.vextices[tmp -> adj_vex].parent = leave;
				queue[rear ++] = tmp -> adj_vex;
			}
			tmp = tmp -> next_arc;
		}
	}
	printf("\n");
}

// 打印从s到t的一条简单路径
static int flag = 0;		// 标志是否已找到一条简单路径
void print_path(graph g, int s, int t)
{
	if (s == t) 
		cout << g.vextices[s].info << " ";
	else {
		if (g.vextices[t].parent == NIL) { 
			cerr << "No path found!" << endl;
			flag = 1;
		}
		else {
			print_path(g, s, g.vextices[t].parent);
			if (flag == 0)
				cout << g.vextices[t].info <<  " ";
		}
	}
}

// 深度优先搜索
static int	time_ = 0;	// 事件发生时间
int		f[MAX];
static void dfs(graph g, int s)
{
	time_ ++;
	g.vextices[s].visited = 1;
	g.vextices[s].dis = time_;
	arc_node	*tmp = g.vextices[s].first_arc;
	while (tmp) {
		if (!g.vextices[tmp -> adj_vex].visited) {
			g.vextices[tmp -> adj_vex].parent = s;
			dfs(g, tmp -> adj_vex);
		}
	}
	time_ ++;
	f[s] = time_;
}

void g_dfs(graph &g)
{
	time_ = 0;
	memset(f, 0, sizeof(f));
	// 初始化顶点节点
	for (int i = 0; i < g.vex_num; i ++ ) {
		g.vextices[i].visited = 0;
		g.vextices[i].parent = NIL;
		g.vextices[i].dis = 0;
	}

	for (int i = 0; i < g.vex_num; i ++) {
		if (!g.vextices[i].visited) {
			dfs(g, i);
		}
	}
}

/* 
 * Topological Sorting 
 */
// Return the pointer to the sorted vertices if normal
// Return NULL if the graph is not a DGA
int topsort(graph g, int **t)
{
	if (g.kind != DN && g.kind != DG) {
		cerr << "Error: Graph inputed is not allowed!" << endl;
		return -1;
	}
	int	*st = new int[g.vex_num];
	*t = st;
	memset(st, 0, sizeof(st) * g.vex_num);
	int		degree[MAX];
	memset(degree, 0, sizeof(degree));
	int	top = -1;	// 栈顶指针

	int	cnt = 0;	// 已经拓扑排序过的顶数
	for (int i = 0; i < g.vex_num; i ++) {
		arc_node	*tmp;
		tmp = g.vextices[i].in_arc;
		while (tmp != NULL) {
			degree[i] ++;
			tmp = tmp -> next_arc;
		}			// 获取各顶的入度
		if (degree[i] == 0) {	// 入度为0的顶入栈
			degree[i] = top;
			top = i;
		}
	}

	while (top != -1) {
		int		i;
		i = top;
		top = degree[top];		// 栈顶指针出栈
		st[cnt ++] = i;
		arc_node	*tmp = g.vextices[i].first_arc;
		while (tmp != NULL) {
			if (-- degree[tmp -> adj_vex] == 0) {
				degree[tmp -> adj_vex] = top;
				top = tmp -> adj_vex;
			}					//	入度为0的顶入栈
			tmp = tmp -> next_arc;
		}
	}
	if (cnt != g.vex_num)
		return -1;
	return 0;
}

int	is_acyclic(graph g)
{
	int	*p;
	return topsort(g, &p);
}

int print_topsort(graph g)
{
	int	*p;
	if (topsort(g, &p) == -1) {
		cerr << "Network has a cycle." << endl;
		return -1;
	}
	for (int i = 0; i < g.vex_num; i ++)
			cout << p[i] << " ";
	cout << endl;
	return 0;
}

/* 删除图 */
void g_delete(graph g)
{
	int	i;

	for (i = 0; i < g.vex_num; i ++) {
		arc_node *tmp = g.vextices[i].first_arc;
		while (tmp) {
			arc_node	*p = tmp;
			tmp = tmp -> next_arc;
			delete p;
		}
		g.vextices[i].in_arc;
		while (tmp) {
			arc_node	*p = tmp;
			tmp = tmp -> next_arc;
			delete p;
		}
		g.vextices[i].first_arc = NULL;
		g.vextices[i].in_arc = NULL;
	}
	return;
}

/* 
 * The improved version of DFS 
 */
static int	t;	// Record the time of the DFS process
static void i_dfs(graph &g, int s)
{
	t ++;
//	cout << s << " " << t << endl;
	g.vextices[s].dis = t;
	g.vextices[s].status = GRAY;
//	cout <<  g.vextices[s].status << endl;
	arc_node *tmp = g.vextices[s].first_arc;
	while (tmp) {
		int k = tmp -> adj_vex;
		if (g.vextices[k].status == WHT) {
			g.vextices[k].parent = s;
	//		g.vextices[k].dis = g.vextices[s].dis + 1;
			i_dfs(g, k);
		}
		tmp = tmp -> next_arc;
	}
	t ++;
//	cout << s << " " << t << endl;
	g.vextices[s].f = t;
	g.vextices[s].status = BLK;
}

void graph_dfs(graph &g) 
{
	t = 0;
	// Initilization
	for (int i = 0; i < g.vex_num; i ++) {
			g.vextices[i].parent = NIL;
			g.vextices[i].dis = INF;
			g.vextices[i].f = INF;
			g.vextices[i].status = WHT;
	}
	for (int i = 0; i < g.vex_num; i ++) {
//		cout << "Node " << i << " status: " 
//			 << g.vextices[i].status << endl;
		if (g.vextices[i].status == WHT) {
			i_dfs(g, i);
		}
	}
}

/* 
 * Improved version of print_path
 */
void graph_show(graph g, int choice)
{

	if (choice == 0) {
		for (int i = 0; i < g.vex_num; i ++) {
			vex_node	*tmp = &(g.vextices[i]);
			cout << "Node " << tmp -> info
				 << ":(out adj_vex) ";
			arc_node	*k = tmp -> first_arc;
			while (k != NULL) {
				cout << g.vextices[k -> adj_vex].info << "(w="
					 << k -> w << ") ";
				k = k -> next_arc;
			}
			cout << endl;
			k = tmp -> in_arc;
			if (k) {
				cout << "\t(in adj_vex) ";
				while (k != NULL) {
					cout << g.vextices[k -> adj_vex].info << "(w="
						 << k -> w << ") ";
					k = k -> next_arc;
				}
			}
			cout << endl;
		}
	}
	// Print DFS tree
	if (choice == 1) {
		for (int i = 0; i < g.vex_num; i ++) {
			vex_node	*tmp = &(g.vextices[i]);
			int t;
			t = i;
			cout << "Node " << tmp -> info << ": discovered time "
				 << tmp -> dis << " finished time " << tmp -> f << endl;
			cout << "Path: ";
			while (t != NIL) {
				cout << g.vextices[t].info << "-->";
				t = g.vextices[t].parent;
			}
			cout << "NIL" << endl;
		}
	}
	// Print BFS tree
	if (choice == 2) {
		for (int i = 0; i < g.vex_num; i ++) {
			vex_node	*tmp = &(g.vextices[i]);
			int t = i;
			cout << "Node " << tmp -> info << ": distace " 
				 << tmp -> dis << endl;
			while (t != NIL) {
				cout << g.vextices[t].info << "-->";
				t = g.vextices[t].parent;
			}
			cout << "NIL" << endl;
		}
	}
}
/*
 * Impooved version of BFS
 */
void graph_bfs(graph &g, int s)
{
	// Initilization
	for (int i = 0; i < g.vex_num; i ++) {
		g.vextices[i].parent = NIL;
		g.vextices[i].dis = INF;
		g.vextices[i].status = WHT;
	}

	g.vextices[s].parent = NIL;
	g.vextices[s].dis = 0;
	g.vextices[s].status = GRAY;
	int	queue[MAX];
	int	rear, front;

	rear = front = 0;
	queue[rear ++] = s;

	while (rear != front) {
		int	u = queue[front ++];
		arc_node	*tmp = g.vextices[u].first_arc;
		while (tmp) {
			if (g.vextices[tmp -> adj_vex].status == WHT) {
				g.vextices[tmp -> adj_vex].status = GRAY;
				g.vextices[tmp -> adj_vex].parent = u;
				g.vextices[tmp -> adj_vex].dis = g.vextices[u].dis + 1;
				queue[rear ++] = tmp -> adj_vex;
			}
			tmp = tmp -> next_arc; } g.vextices[s].status = BLK;
	}
}


/****************************
 *  Shortest path problem   *
 ****************************/

/*
 * Dijkstra's algorithom
 */

/* Initilizatize the vertices in graph */
static void init_single_source(graph &g, int s)
{
	for (int i = 0; i < g.vex_num; i ++ ) {
		g.vextices[i].parent = NIL;
		g.vextices[i].dis = INF;
		g.vextices[i].status = WHT;
	}
	g.vextices[s].dis = 0;
	g.vextices[s].status = BLK;	// Add s to S
	arc_node	*tmp = g.vextices[s].first_arc;
	while(tmp) {
		g.vextices[tmp -> adj_vex].dis = tmp -> w;
		g.vextices[tmp -> adj_vex].parent = s;
		tmp = tmp -> next_arc;
	}
}

/* Relax the arc <u,v> with weight w */
static void relax(graph &g, int u, int v, int w)
{
	if (g.vextices[u].dis + w < g.vextices[v].dis) {
		g.vextices[v].dis = g.vextices[u].dis + w;
		g.vextices[v].parent = u;
	}
}

/* Return the v whose g.vextices[v].dis is minimum among the vertices adj to u */
   static int extract_min(graph &g)
{	
	int	min = INF;
	int v = -1;
	for (int i = 0; i < g.vex_num; i ++) {
		if (g.vextices[i].status == WHT) {
			if (g.vextices[i].dis < min) {
				min = g.vextices[i].dis;
				v = i;
			}
		}
	}
	if (v != -1)
		g.vextices[v].status = BLK;
	return v;
}

void sp_dij(graph &g, int s)
{
	init_single_source(g, s); 

	while (1) {
/*		flag = 1;
		for (int i = 0; i < g.vex_num; i ++)
			if (g.vextices[i].status == WHT)
				flag = 0;
		if (flag == 0)
			break;		// Have found the shortest path from s to any other vertices reachable to s
*/		s = extract_min(g);
		if (s < 0) {
			break;
		}	
		arc_node	*tmp = g.vextices[s].first_arc;
		while (tmp != NULL) {
			if (g.vextices[tmp -> adj_vex].status == WHT)
				relax(g, s, tmp -> adj_vex, tmp -> w);
			tmp = tmp -> next_arc;
		}
	}
}

static void result_show(graph g, int s, int v)
{
	if (s == v)
		cout << s << " ";
	else {
		if (g.vextices[v].parent == NIL) 
			cout << "No path!!!" << endl;
		else {
			result_show(g, s, g.vextices[v].parent);
			cout << v << " ";
		}
	}
}
/* Show the result of the Dijkstra's algorithm */
void sp_show(graph g, int s)
{
	for (int i = 0; i < g.vex_num; i ++) {
		if (i != s) {
			cout << "The shortest path from node " << s 
				 << " to " << i << " :(weight = " << g.vextices[i].dis
				 << ") ";
			result_show(g, s, i);
			cout << endl;
		}
	}
}

/*
 * The Bellman-Ford algorithm
 */
// Return 0 if bf course is normal
// Return -1 if g include cycline that can be reached from s
int sp_bf(graph &g, int s)
{
	init_single_source(g, s);

	for (int i = 0; i < g.vex_num - 1; i ++) {
		for (int j = 0; j < g.vex_num; j ++) {
			arc_node	*tmp = g.vextices[j].first_arc;
			while (tmp) {
				relax(g, j, tmp -> adj_vex, tmp -> w);
				tmp = tmp -> next_arc;
			}
		}
	}

	int flag = 0;
	for (int i = 0; i < g.vex_num; i ++) {
		arc_node	*tmp = g.vextices[i].first_arc;
		while (tmp) {
			if (g.vextices[tmp -> adj_vex].dis > g.vextices[i].dis + tmp -> w)
				flag = 1;
			tmp = tmp -> next_arc;
		}
	}
	if (flag) {
		cout << "Directed cycline in graph!!!" << endl;
		return -1;
	}
	return 0;
}

/* 
 * Single source shortest path in directed acyclie graphs (DAG)
 */
// Relaxing arcs in the order sorted by the topological sort technology
// It can only be used in DAG
int sp_topsort(graph &g, int s)
{	
	int	*p;
	if (topsort(g, &p) == -1) {
		cerr << "It's not a DGA!!!" << endl;
		return -1;
	}
	init_single_source(g, s);
	for (int i = 0; i < g.vex_num; i ++) {
		arc_node	*tmp = g.vextices[p[i]].first_arc;
		while (tmp) {
			relax(g, p[i], tmp -> adj_vex, tmp -> w);
			tmp = tmp -> next_arc;
		}
	}
	return 0;
}


/*************************
 * Minimum Spanning Tree *
 *************************/

/* 
 * Kruscal algorithm
 */
// Find the represent vertex of s
static int find(graph &g, int s)
{
	int	x;
	
	for (x = s; g.vextices[x].parent >= 0; x = g.vextices[x].parent)
		;
	while (x != s) {
		int tmp = g.vextices[s].parent;
		g.vextices[s].parent = x;
		s = tmp;
	}
	return x;
}

static void merge(graph &g, int s, int t)
{
	int	p1 = find(g, s);
	int p2 = find(g, t);

	if (g.vextices[p1].parent < g.vextices[p2].parent) {
		g.vextices[p1].parent += g.vextices[p2].parent;
		g.vextices[p2].parent = p1;
	}
	else {
		g.vextices[p2].parent += g.vextices[p1].parent;
		g.vextices[p1].parent = p2;
	}
}

static void init_umset(graph &g)
{
	for (int i = 0; i < g.vex_num; i ++) {
		g.vextices[i].parent = -1;
	}
}


static int cmp(const void *a, const void *b)
{
	arc_node	*m = (arc_node *)a;
	arc_node	*n = (arc_node *)b;
	return (m -> w - n -> w);
}

void _sort(arc_node	**parc, int n)
{
	for (int i = 0; i < n - 1; i ++)
		for (int j = i + 1; j < n; j ++) {
			if (parc[i] -> w > parc[j] -> w) {
				arc_node	*tmp = parc[i];
				parc[i] = parc[j];
				parc[j] = tmp;
			}
		}
}
/* Return the weight of the MST */
int kruscal(graph &g) 
{
	int	weight = 0;
	if (g.kind != UDN && g.kind != UDG) {
		cerr << "Graph input is not a UDN or UDG!!!" << endl;
		return -1;
	}
	init_umset(g);

	arc_node	**parc;
	parc = (arc_node **)malloc(sizeof(arc_node *) * g.arc_num);
	memset(parc, 0, sizeof(arc_node *) * g.arc_num);
	int cnt = 0;

	/* 
	 * 找出无向网所有的边，放在parc中，由于是无向网，所以每边都有两个节点
	 * 初始化每边的status为0（上面的memset的作用），在选边的时候，先找到对
	 * 应的该边的另一节点，如果这边（另一边）的status为0，则入选该边，并置
	 * status为1
	 */
	for (int i = 0; i < g.vex_num; i ++) {
		arc_node	*tmp = g.vextices[i].first_arc;
		while (tmp) {	// Attention: UDN
				arc_node	*p = g.vextices[tmp -> adj_vex].first_arc;
				while (p) {
					if (p -> adj_vex == i)
						break;
					p = p -> next_arc;
				}	// 找出该边对应的另一边
				if (p -> status == 0) {	// 该边还没入选，选进并置status为1
					parc[cnt ++] = tmp;
					tmp -> add = i;
					tmp -> status = 1;
				}
				tmp = tmp -> next_arc;
		}
	}

	for (int i = 0; i < g.arc_num; i ++)
		parc[i] -> status = 0;		// 重新置已选出的边的status为0，进行下面的操作
	cnt = 0;
	// sort the arcs with the non-reduced order
	//	qsort(parc, g.arc_num, sizeof(arc_node *), cmp);
	_sort(parc, g.arc_num);
	
	// Add arcs in weight order which connect two trees,
	// and union the two trees
	for(int j = 0; j < g.arc_num; j ++) {
		int p1 = find(g, parc[j] -> adj_vex);
		int	p2 = find(g, parc[j] -> add);	// The information of the other vertex
	// Union the two trees
		if (p1 != p2) {
			cnt ++;
			parc[j] -> status = 1;
			merge(g, parc[j] -> adj_vex, parc[j] -> add);
		}
		if (cnt == g.vex_num - 1)
			break;
	}
	for (int i = 0; i < g.arc_num; i ++) {
		if (parc[i] -> status == 1)
			printf("%d %d w = %d\n", parc[i] -> adj_vex, parc[i] -> add, parc[i] -> w);
	}
}

/*
 * Prim's Algorithm
 */
static void prim_init(graph &g, int s)
{
	for (int i = 0; i < g.vex_num; i ++) {
		g.vextices[i].dis = INF;
		g.vextices[i].parent = NIL;
		g.vextices[i].status = WHT;
	}

	int min = INF;
	g.vextices[s].status = BLK;
	arc_node	*tmp = g.vextices[s].first_arc;
	int k;
	while (tmp != NULL) {
		g.vextices[tmp -> adj_vex].dis = tmp -> w;
		g.vextices[tmp -> adj_vex].parent = s;
		if (tmp -> w < min) {
			min = tmp -> w;
			k = tmp -> adj_vex;
		}
		tmp = tmp -> next_arc;
	}
	g.vextices[s].parent = k;
	g.vextices[s].dis = min;
}

// Select the vertex whose dis is the smallest to the set S
// and return the number of it, if all of the vertices are in
// the set S, return -1
static int prim_extract_min(graph &g)
{
	int min = INF;

	int k = -1;
	for (int i = 0; i < g.vex_num; i ++) {
		if (g.vextices[i].status == WHT) {
			if (g.vextices[i].dis < min) {
				min = g.vextices[i].dis;
				k = i;
			}
		}
	}
	if (k != -1) {
		g.vextices[k].status = BLK;
	}
	return k;
}

static void prim_relax(graph &g, int s, int u, int w)
{
	if (g.vextices[u].dis > w) {
		g.vextices[u].dis = w;
		g.vextices[u].parent = s;
	}
}
/*
void prim_show(graph &g)
{
	for (int i = 0; i < g.vex_num; i ++)
		printf("%d\n", g.vextices[i].status);
	for (int i = 0; i < g.vex_num; i ++) {
		if (g.vextices[i].status == BLK) {
			cout << i << " " << g.vextices[i].parent 
				 << " w = " << g.vextices[i].dis << endl;
			if (g.vextices[g.vextices[i].parent].parent == i)
				g.vextices[g.vextices[i].parent].status = WHT;
		}
	}
	for (int i = 0; i < g.vex_num; i ++)
		printf("after %d\n", g.vextices[i].status);
}
*/
// I'm too lazy to cope with this problem,
// so I use "grobal var" to solve it!!!
// God Bless me!!!
int	_node1[MAX];
int	_node2[MAX];
int	_w[MAX];
void prim_show(graph &g) 
{
	for (int i = 0; i < g.vex_num - 1; i ++) {
	cout << _node1[i] << " " << _node2[i] 
		 << " w = " << _w[i] << endl;
	}
}

int prim(graph &g, int s)
{
	prim_init(g, s);
	int weight = 0;		// The weight of the MST

	int cnt = 0;
	while (1) {
		int u = prim_extract_min(g);
		if (u == -1)
			break;
		_node1[cnt] = u;
		_node2[cnt] = g.vextices[u].parent;
		_w[cnt ++] = g.vextices[u].dis;
		weight += g.vextices[u].dis;
		arc_node	*tmp = g.vextices[u].first_arc;
		while (tmp) {
			prim_relax(g, u, tmp -> adj_vex, tmp -> w);
			tmp = tmp -> next_arc;
		}
	}
	cout << "The weight of the MST: " << weight << endl;
	return weight;
}

