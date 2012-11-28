#ifndef _HUFF_H_
#define	_HUFF_H_

#define ASIIC	256	
#define BUFSIZE	1024
#define	FLAG_BIT	6
#define FILE_FLAG	"WEIANG"
#define	BYTE_SIZE	8
/*
 *  Data structure
 */
typedef char	element_type;
typedef struct node {
	int	weight;
	int	parent, lc, rc;
	element_type	data;
} huff_node;

extern huff_node *creat_huff_tree(int *, int, element_type *);
extern char **huff_encoding(huff_node *, int);
extern void huff_decoding(huff_node *, char *, char *);

#endif	// _HUFF_H_
