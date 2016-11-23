/*
    Name: Matthew Ta
    Date: 14/9/2015
    Description: Implementation fo the BST ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"

#define TRUE 1
#define FALSE 0

typedef struct _treeRep{
    TreeNode rootnode; // first node in the tree
} treeRep;

typedef struct _treenode{
	int value; // key value
	int nnodes; // stores the number of nodes
    TreeNode leftnode;
    TreeNode rightnode;
} treenode;

static int minimalValue(TreeNode n);
static TreeNode newNode(int value); // creates a new tree node
static int numNodes(TreeNode n);
TreeNode partition(TreeNode n, int i);

Tree newTree(void)
{
    Tree t = malloc(sizeof(treeRep));
    if (t != NULL){
        t->rootnode = NULL;
    }
    return t;
}

// inserts at the leaf
void insertValue(TreeNode *n, int value)
{
    if (*n == NULL){ // create a leaf node
        *n = malloc(sizeof(treenode));
        (*n)->leftnode = NULL;
        (*n)->rightnode = NULL;
        (*n)->value = value;
		(*n)->nnodes = 1;
    }

    else{ // search the tree to insert the value
        if (value < (*n)->value){ // insert in left sub tree
            insertValue(&((*n)->leftnode), value);
        }

        else if (value > (*n)->value){ // insert in right subtree
            insertValue(&((*n)->rightnode), value);
        }
    }
}

/*
	* inserts a node at the root
	* ignores the case where n->value == value
*/
TreeNode insertRoot(TreeNode n, int value)
{
	if (n == NULL){
		n = newNode(value);
	}

	else{
		n->nnodes = numNodes(n); // count the nodes
	}

	if (value < n->value){
		n->leftnode = insertRoot(n->leftnode, value);
		n = rotateRight(n);
	}

	if (value > n->value){
		n->rightnode = insertRoot(n->rightnode, value);
		n = rotateLeft(n);
	}
	return n;
}

/*
TreeNode deleteNode(TreeNode n, int value)
{
	TreeNode leftSubTree = NULL;
	TreeNode rightSubTree = NULL;
	TreeNode joinNode = NULL;
	int minValue = 0;

	
		* deals with deleting a leaf node
		* deals with deleting root node from a one node tree
	
	
	if (n != NULL){
		leftSubTree = n->leftnode;
		rightSubTree = n->rightnode;
		if (n->value == value){ // found value
			if (leftSubTree == NULL && rightSubTree == NULL){ // n is just a leaf node
				free(n);
				return NULL;
			}

			else if (leftSubTree != NULL && rightSubTree == NULL){ // n contains a left subtree
				free(n);
				return leftSubTree;
			}

			else if (rightSubTree != NULL && leftSubTree == NULL){ // n contains a right subtree
				free(n);
				return rightSubTree;
			}

			else{
				if (leftSubTree != NULL && rightSubTree != NULL){ // n contains both a left and right subtree
					minValue = minimalValue(rightSubTree);
					n->value = minValue;
					joinNode = deleteNode(rightSubTree, minValue);
					n->rightnode = joinNode;
					return n;
				}
			}
		}

		joinNode = deleteNode(leftSubTree, value);
		n->leftnode = joinNode;
		joinNode = deleteNode(rightSubTree, value);
		n->rightnode = joinNode;
	}

	return n; // return same node passed in if couldn't find node with value
}
*/

TreeNode deleteNode(TreeNode n, int value)
{
	int min = 0;
	if (n == NULL) { return NULL; }

	if (value == n->value){
		if (n->leftnode == NULL && n->rightnode == NULL){ // leaf node
			return NULL;
		}

		else if (n->leftnode != NULL && n->rightnode == NULL){ // n contains a left subtree
			return n->leftnode;
		}

		else if (n->rightnode != NULL && n->leftnode == NULL){ // n contains a right subtree
			return n->rightnode;
		}

		else{ // n contains two children
			min = minimalValue(n->rightnode);
			n->value = min;
			n->rightnode = deleteNode(n->rightnode, min);
		} 
	}

	else if (value < n->value){
		n->leftnode = deleteNode(n->leftnode, value);
	}

	else{
		n->rightnode = deleteNode(n->rightnode, value);
	}
	return n;
}

// finds the minimal value in a tree
int minimalValue(TreeNode n)
{
	int value = 0;
	if (n->leftnode == NULL){
		return n->value;
	}

	value = minimalValue(n->leftnode);
	return value;
}

void inorder(TreeNode n)
{
    if (n != NULL){
        inorder(n->leftnode);
        printf("%2d ", n->value);
        inorder(n->rightnode);
    }
}

void preorder(TreeNode n)
{
    if (n != NULL){
        printf("%2d ", n->value);
        preorder(n->leftnode);
        preorder(n->rightnode);
    }  
}

void postorder(TreeNode n)
{
    if (n != NULL){
        postorder(n->leftnode);
        postorder(n->rightnode);
        printf("%2d ", n->value);
    }
}

void deleteTree(TreeNode node)
{
    if (node != NULL){
        deleteTree(node->leftnode);
        deleteTree(node->rightnode);
        free(node);
    }
}

TreeNode rotateRight(TreeNode t)
{
	TreeNode n1 = NULL, n2 = NULL;

	if (t == NULL) { return NULL; }
	n1 = t;
	n2 = n1->leftnode;
	if (n2 == NULL) { return t; }
	n1->leftnode = n2->rightnode;
	n2->rightnode = n1;
	return n2;
}

TreeNode rotateLeft(TreeNode t)
{
	TreeNode n1 = NULL, n2 = NULL;

	if (t == NULL) { return NULL; }
	n2 = t;
	n1 = t->rightnode;
	if (n1 == NULL) { return n2; }
	n2->rightnode = n1->leftnode;
	n1->leftnode = n2;
	return n1;
}

// works better if you have key values that are unique for each node
TreeNode rebalanceTree(TreeNode t)
{
	if (t == NULL){
		return NULL;
	}	

	if (numNodes(t) < 2){ // no need to rebalance
		return t;
	}

	t = partition(t, numNodes(t)/2); // place the median node as root
	t->leftnode = rebalanceTree(t->leftnode);
	t->rightnode = rebalanceTree(t->rightnode);
	return t;
}

// places the median node of a tree as root
TreeNode partition(TreeNode t, int i)
{
	if (t == NULL) { return NULL; }
	int size = getNumNodes(t->leftnode);
	
	if (i < size){
		t->leftnode = partition(t->leftnode, i);
		t = rotateRight(t);
	}

	if (i > size){
		t->rightnode = partition(t->rightnode, (i - size - 1));
		t = rotateLeft(t);
	}
	
	return t;
}

// joins two trees, works only for max(t1) < min(t2)
TreeNode joinTrees(TreeNode t1, TreeNode t2)
{
	TreeNode cur = t2, parentNode = NULL;

	if (t1 == NULL) { return t2; } // if one of the trees is NULL, return the other one
	if (t2 == NULL) { return t1; }
	
	while (cur->leftnode != NULL){ // find the smallest value in t2
		parentNode = cur;
		cur = cur->leftnode;
	}

	if (parentNode != NULL){ // could be a tree with 1 node
		parentNode->leftnode = cur->leftnode; // cur->left at this point should be NULL
		cur->rightnode = t2;
	}
	
	cur->leftnode = t1;
	return cur;
}

TreeNode deleteWithJoin(TreeNode t, int value)
{
	TreeNode n;
	if (t == NULL) { return NULL; }

	if (value < t->value){
		t = deleteWithJoin(t->leftnode, value);
	}

	else if (value > t->value){
		t = deleteWithJoin(t->rightnode, value);
	}

	else{ // t->value == value
		if (t->leftnode == NULL){
			n = t->rightnode;
		}

		else if (t->rightnode == NULL){
			n = t->leftnode;
		}

		else{
			n = joinTrees(t->leftnode, t->rightnode);
		}

		free(t);
		t = n;
	}

	return t;
}

int numNodes(TreeNode n)
{
	int nnodes = 0;
	if (n == NULL){
		nnodes = 0;
	}

	else{
		int lnnodes = numNodes(n->leftnode);
		int rnnodes = numNodes(n->rightnode);
		nnodes = 1 + lnnodes + rnnodes;
	}

	return nnodes;
}

int getNumNodes(TreeNode n)
{
	return n->nnodes;
}

int treeDepth(TreeNode n)
{
	if (n == NULL){
		return 0;
	}

	else{
		int ldepth = treeDepth(n->leftnode);
		int rdepth = treeDepth(n->rightnode);
		return 1 + ( (ldepth > rdepth) ? ldepth : rdepth );
	}
}

int treeFindValue(TreeNode n, int value) // recursively
{
	if (n == NULL){
		return FALSE; // didn't find value
	}

	else if (n->value == value){
		return TRUE;
	}

	else if (n->value > value){
		return treeFindValue(n->leftnode, value);
	}

	else{
		return treeFindValue(n->rightnode, value);
	}

}

int treeFindValueI(TreeNode n, int value) // iterative
{
	TreeNode cur = n;
	while ( cur != NULL ){
		if (cur->value == value){
			return TRUE;
		}

		else if (cur->value > value){
			cur = cur->leftnode;
		}

		else{
			cur = cur->rightnode;
		}

	}

	return FALSE;
}

int numLeafs(TreeNode n)
{
	int leftLeafs = 0, rightLeafs = 0;
	if (n == NULL){
		return 0;
	}

	else{
		leftLeafs = numLeafs(n->leftnode);
		rightLeafs = numLeafs(n->rightnode);
		if (leftLeafs == 0 && rightLeafs == 0) { return 1; }
		else { return leftLeafs + rightLeafs; }
	}
}

static TreeNode newNode(int value)
{
	TreeNode newNode = malloc(sizeof(treenode));
	assert(newNode != NULL);
	newNode->value = value;
	newNode->nnodes = 1;
	return newNode;
}

TreeNode getRootNode(Tree t)
{
    return t->rootnode;
}


