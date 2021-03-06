#ifndef	_GRAPH_H_
#define	_GRAPH_H_

#define MAX	200
#define NIL	1000	
#define INF	100000

#define	EQ(A, B)	((A) == (B))
#define PRT(A)		printf("%c ", A)
/* The vertices' type */
typedef char	elem_type;

/*******************
 * Data Structures *
 *******************/

/* 图的种类：{有向图，有向网，无向图，无向网} */
typedef enum {DG, DN, UDG, UDN} graph_kind;	

/* 顶点的状态 */
typedef enum {WHT, GRAY, BLK} color;	// Record the status of the vertexs and arcs

/* 邻接表的弧节点 */
typedef struct node {
	int		adj_vex;
	int		w;				// The weight of the arc
	struct node	*next_arc;
	int		add;			// Reserved memory(for unpredicted use)
	color		status;
} arc_node;

/* 顶节点 */	
typedef struct {
	elem_type	info;
	arc_node	*first_arc;	// 当为无向图时指向邻接表
							// 当为有向图时指向出度邻接表
	arc_node	*in_arc;	// 当为无向图时为NULL
							// 当为有向图时指向入度邻接表
	int		parent;			// 顶点遍历过程中该顶点的前驱顶点
	int		dis;			// 该节点被访问的时间（status = GRAY）	
	color	status;	
	int		f;				// 访问该节点的结束时间（status = BLK）
	int		w;
} vex_node;

/* 图 */
typedef struct graph {
	int			vex_num, arc_num;	// 图的当前顶点数和弧数
	graph_kind	kind;				// 图种类标志
	vex_node	vextices[MAX];		// 顶点向量
} graph;


/*********************
 * Function prototype*
 *********************/

/* Elementary operations on graph */
extern void graph_creat(graph &);
extern void g_delete(graph &);
extern void graph_show(graph);

/* Graph Traverse */
extern void graph_dfs(graph &, int, void (*)(elem_type &));
extern void dfs_show(graph);
extern void graph_bfs(graph &, int, void (*)(elem_type &));
extern void bfs_show(graph &, int); 
extern void show_path(graph, int, int);

/* Topological sorting */
extern int  topsort(graph, int * &);
extern int	is_acyclic(graph);
extern int  topsort_show(graph);

/* Shortest path */
extern void sp_dij(graph &, int);
extern void sp_show(graph, int);
extern int	sp_bf(graph &, int);
extern int  sp_topsort(graph &, int);

/* Minumin Spanning Tree */
extern int	mst_kruscal(graph &);
extern int	mst_prim(graph &, int s);
extern void	mst_show(graph &);

#endif	// _GRAPH_H_



