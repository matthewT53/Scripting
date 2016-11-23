/*
    Name: Matthew Ta
    Date: 14/9/2015
    Description: Interface for the BST ADT
*/

typedef struct _treeRep *Tree;
typedef struct _treenode *TreeNode;

Tree newTree(void); // create a new tree

void insertValue(TreeNode *n, int value); // insert an item at the leaf

TreeNode getRootNode(Tree t); // returns the root node of a tree

// traversing methods
void inorder(TreeNode n); // also a sorting method
void preorder(TreeNode n);
void postorder(TreeNode n);

// deletes a leaf
TreeNode deleteNode(TreeNode n, int value);

void deleteTree(TreeNode n); // frees the tree structure

int numberNodes(TreeNode n); // determine how many leafs there are in the tree including root node

int treeDepth(TreeNode n); // determine the depth of the tree

int numLeafs(TreeNode n); // counts the number of leaf nodes in a tree

int treeFindValue(TreeNode n, int value); // find a value in a tree (recursively)

int treeFindValueI(TreeNode n, int value); // find a value in a tree (iteratively)

int getNumNodes(TreeNode n); // returns the number of nodes in the tree

// rotations that try to rebalance trees
TreeNode rotateLeft(TreeNode n); // rotates the tree left
TreeNode rotateRight(TreeNode n); // rotates the tree right

// insert leaf at root
TreeNode insertRoot(TreeNode t, int value);

// rebalances a tree
TreeNode rebalanceTree(TreeNode t);

// join two trees
TreeNode joinTrees(TreeNode t1, TreeNode t2);

// delete a node using joinTrees()
TreeNode deleteWithJoin(TreeNode t, int value);

