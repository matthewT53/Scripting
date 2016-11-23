/*
	Name: Matthew Ta
	Date: 2/11/2015
	Description: ADT for red and black trees
*/

/*
	Notes:
	* red black trees are isometric to 2-3-4 trees, i.e they are the same thing
	* a red node represents a sibling of the parent
	* black node represents a child of the parent
	* no two red nodes appear consecutively down the same path
	* searching is the same as for a BST
*/

#define PREORDER 0
#define POSTORDER 1
#define INORDER 2

typedef struct _node *Node; // ptr to a tree node
typedef struct _rbRep *Tree; // ptr to a rb tree

Tree newTree(void); // create a new tree
void disposeTree(Tree rb); // free an existing tree

void insertValue(Tree rb, int value); // insert a value into the tree
void removeValue(Tree rb, int value); // remove a value from the tree
int searchValue(Tree rb, int value); // searches for a particular value

void printTree(Tree rb, int order); // prints a tree in a particular order e.g inorder, preorder, postorder, levelorder
