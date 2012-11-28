#ifndef _BIN_TREE_
#define _BIN_TREE_

#define MAX	100
#define TABLE	50
#define MEDIA	20
typedef char	element_type;

typedef struct node {
	element_type data;
	struct node	*lchild, *rchild;
} bin_node;

extern recursion_creat_bin_tree(bin_node **, int);	// Random creat
extern creat_bin_tree(bin_node **, int, char *);		// Creat with input
extern recursion_pre_order_trverse(bin_node *, int visit(bin_node *));
extern pre_order_trverse(bin_node *, int visit(bin_node *));
extern recursion_inter_order_trverse(bin_node *, int visit(bin_node *));
extern inter_order_trverse(bin_node *, int visit(bin_node *));
extern recursion_post_order_trverse(bin_node *, int visit(bin_node *));
extern post_order_trverse(bin_node *, int visit(bin_node *));
extern int lay_order_trverse(bin_node *root, int visit(bin_node *));
extern distance(bin_node *, element_type term);
extern height(bin_node *);
extern recursion_bin_tree_copy(bin_node *, bin_node **);
extern bin_tree_copy(bin_node *, bin_node **);
extern recursion_exchange_bin_node(bin_node *);
extern exchange_bin_tree_node(bin_node *);
extern pre_get_value(bin_node *, int ,element_type *);
extern leaf(bin_node *);
extern recursion_leaf(bin_node *);
extern void recursion_del_subtree(bin_node *, element_type);
extern void print(bin_node *);
extern void find_path(bin_node *, element_type, bin_node *[], int);
extern bin_node *find_near_ancestor(bin_node *, element_type, element_type);
extern void show(bin_node *, int);

#endif	// _BIN_TREE_
