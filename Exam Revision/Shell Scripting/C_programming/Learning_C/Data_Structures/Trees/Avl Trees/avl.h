/*
	Name: Matthew Ta
	Date: 24/10/2015
	Description: ADT for Avl trees
*/

typedef struct _tnode *Link;
typedef struct _treeRep *Tree;

Tree newTree(void); // creates a new tree 
void disposeTree(Tree t); // deletes the tree

void insertValue(Tree t, int value); // inserts a value into the tree using AVL method
int search(Tree t, int value); // AVL search for a value
void removeValue(Tree t, int value); // removes a value from the tree

void join(Tree t, Tree s); // joins tree s and t, all vlaues ins must be < t

int getTreeDepth(Tree t); // returns the depth of the tree
void printTree(Tree t); // prints the tree in level order

