#ifndef	_GRAPH_H_
#define	_GRAPH_H_

#define MAX	20
#define NIL	1000

/*
 * Data Structures 
 */
/* 图的种类：{有向图，有向网，无向图，无向网} */
typedef enum {DG, DN, UDG, UDN} graph_kind;	
// 邻接表的弧节点
typedef struct node {
	int		adj_vex;
	struct node	*next_arc;
} arc_node;
// 顶节点	
typedef struct {
	int	info;
	arc_node	*first_arc;	// 当为无向图时指向邻接表
					// 当为有向图时指向出度邻接表
	arc_node	*in_arc;	// 当为无向图时为NULL
					// 当为有向图时指向入度邻接表
	int		visited;	
	int		parent;		// 顶点遍历过程中该顶点的前驱顶点
	int		dis;
} vex_node;
// 图
typedef struct graph {
	int			vex_num, arc_num;	// 图的当前顶点数和弧数
	graph_kind	kind;				// 图种类标志
	vex_node	vextices[MAX];		// 顶点向量
} graph;

/*
 * 函数声明
 */
extern void g_creat(graph &);
extern void print_path(graph, int, int);
extern void g_bfs(graph &, int);
extern void g_dfs(graph &, int);
extern int  topsort(graph, int **);
extern int	is_acyclic(graph);
extern int  print_topsort(graph);
extern void g_delete(graph);

#endif	// _GRAPH_H_



