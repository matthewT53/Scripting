/*
	Name: Matthew Ta
	Date: 25/10/2015
	Description: ADT for 2-3-4 trees
*/

/* ======= Notes =========== */
/*
	* 2-3-4 trees have three kinds of nodes
	-> 2 nodes, 1 value with 2 children
	-> 3 nodes 2 values with 3 children
	-> 4 nodes 3 values with 4 children

	* In a balanced 2-3-4 tree, all leafs are same distance from the root
	* Tree grows up from the leaves
	* worst case, all nodes are 2-nodes which makes searching O(log2(n))
	* best case, all nodes are 4-nodes, which makes searching O(log4(n))
*/

typedef struct _treeRep *Tree;
typedef struct _node *Node;

Tree newTree(void); // create a new 2-3-4 tree
void disposeTree(Tree t); // free the 2-3-4 tree

void insertValue(Tree t, int value); // insert a value into the tree
void removeValue(Tree t, int value); // delete a value from the tree
int search(Tree t, int value); // searches for a value in the tree

void printTree(Tree t, int order); // prints the list 
