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

/* 创建无向图 */
static void udg_creat(graph &g)
{
	int		i, j;
	int		vi, vj;
	arc_node	*ptmp;

	scanf("%d%d", &g.vex_num, &g.arc_num);
	
	for (i = 0; i < g.vex_num; i ++) {
		g.vextices[i].first_arc = NULL;
		g.vextices[i].info = i + 1;
		g.vextices[i].parent = NIL;
		g.vextices[i].visited = 0;
		g.vextices[i].in_arc = NULL;
	}
	for (i = 0; i < g.arc_num; i ++) {
		scanf("%d%d", &vi, &vj);
		vi --;
		vj --;
		ptmp = new arc_node;
		ptmp -> adj_vex = vj;
		ptmp -> next_arc = g.vextices[vi].first_arc;
		g.vextices[vi].first_arc = ptmp;
		ptmp = new arc_node;
		ptmp -> adj_vex = vi;
		ptmp -> next_arc = g.vextices[vj].first_arc;
		g.vextices[vj].first_arc = ptmp;
	}
}

/* 创建有向图 */
static void dg_creat(graph &g)
{
	int		vi, vj;
	cin >> g.vex_num >> g.arc_num;

	// 初始化顶点节点
	for (int i = 0; i < g.vex_num; i ++) {
		g.vextices[i].info = i + 1;
		g.vextices[i].first_arc = NULL;
		g.vextices[i].in_arc = NULL;
		g.vextices[i].parent = NIL;
		g.vextices[i].visited = 0;
		g.vextices[i].dis = 0;
	}
	
	// 获取弧信息
	for (int i = 0; i < g.arc_num; i ++) {
		cin >> vi >> vj;
		vi --;
		vj --;
		arc_node	*tmp = new arc_node;
		tmp -> adj_vex = vj;
		tmp -> next_arc = g.vextices[vi].first_arc;
		g.vextices[vi].first_arc = tmp;
		tmp = new arc_node;
		tmp -> adj_vex = vi;
		tmp -> next_arc = g.vextices[vj].in_arc;
		g.vextices[vj].in_arc = tmp;
	}
}

// 构建图
void g_creat(graph &g)
{
	scanf("%d", (int *)&(g.kind));
//	cout << g.kind << endl;
	switch (g.kind) {
		case	DG:	
			dg_creat(g);
			break;
		case	DN:	
//			dn_creat(g);
			break;
		case	UDG:
			udg_creat(g);
			break;
		case	UDN:
//			udn_creat(g);
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

/* 拓扑排序 */
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

	int	cnt = 0;
	while (top != -1) {
		int		i;
		i = top;
		top = degree[top];		// 栈顶指针出栈
		st[cnt ++] = g.vextices[i].info;
		arc_node	*tmp = g.vextices[i].first_arc;
		while (tmp != NULL) {
			if (-- degree[tmp -> adj_vex] == 0) {
				degree[tmp -> adj_vex] = top;
				top = tmp -> adj_vex;
			}					//	入度为0的顶入栈
			tmp = tmp -> next_arc;
		}
	}
//	cout << endl;
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
				 << ": adj_vex ";
			arc_node	*k = tmp -> first_arc;
			while (k != NULL) {
				cout << g.vextices[k -> adj_vex].info << " ";
				k = k -> next_arc;
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
			tmp = tmp -> next_arc;
		}
		g.vextices[s].status = BLK;
	}
}



