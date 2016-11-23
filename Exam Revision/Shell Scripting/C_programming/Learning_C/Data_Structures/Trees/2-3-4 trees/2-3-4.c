/*
	Name: Matthew Ta
	Date: 25/10/2015
	Description: Implementation of the ADT for 2-3-4 trees
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "2-3-4.h"

// tree constants
#define MAX_CHILDREN 4
#define MAX_VALUES 3

// boolean constants
#define TRUE 1
#define FALSE 0

// tree output constants
#define LEVEL_ORDER 1
#define PREORDER 2

#define DEBUG // remove comment to see debugging output

// macros for detecting a split and promote
#define SPLIT_PROMOTE(x, y) (x > y)

typedef struct _treeRep{
	Node root;
} treeRep;

typedef struct _node{
	int order; // how many values the node has
	int values[MAX_VALUES]; // max of 3 values each node
	Node child[MAX_CHILDREN]; // max of 4 children
} node;

static Node newNode(int value); // creates a new nodes

// tree functions
Node insertNode(Node n, int value); // insert a value into the tree
void shiftArray(int *a, const int startIndex, const int max); // shifts the array up one position
void shiftNodes(Node *nodes, const int startIndex, const int max); // shifts the nodes up one position
Node mergeNodes(Node n1, Node n2, const int link1, const int link2); // merges two nodes

void deleteTree(Node n); // frees the tree

Node deleteNode(Node n, int value); // deletes a node in the tree with a specific value
int findMaximal(Node n); // finds the max element
int findMinimal(Node n); // finds the min element
Node mergeThreeNodes(Node parent, Node child1, Node child2);
void shiftDown(int *a, const int startIndex, const int size);
void shiftNodesDown(Node *nArray, const int startIndex, const int max);
Node mergeTwoNodes(Node n1, Node n2);
Node fusion(Node parent, Node childLeft, Node childRight, int valueIndex); // performs a fusion operation on the three nodes
Node rotateRight(Node parent, Node c1, int valueIndex); // rotates the tree right
Node rotateLeft(Node parent, Node c2, int valueIndex); // rotates the tree left

Node searchNode(Node n, int value); // searches for a node with a value
void levelOrder(Node n); // prints tree in level order
void preOrder(Node n); // prints the tree in pre-order

#ifdef DEBUG
// debugging helper functions
static void printArray(int *a, const int max);
#endif

/* ==================== create a new tree ==================== */
Tree newTree(void)
{
	Tree t = malloc(sizeof(treeRep));
	t->root = NULL;
	return t;
}

/* ================= dispose an existing tree ================= */
void disposeTree(Tree t)
{
	if (t->root != NULL){
		deleteTree(t->root);
	}
}

void deleteTree(Node n)
{
	int i = 0; 
	if (n == NULL) { return; }
	for (i = 0; i < n->order; i++){
		deleteTree(n->child[i]);
	}
	free(n);
}

/* ========================= insert a node ======================== */
void insertValue(Tree t, int value)
{
	if (t->root == NULL) { t->root = newNode(value); }
	else{ t->root = insertNode(t->root, value); }
}

/*
	Insertion algorithm:
	* Loop through the values array
	* check if there is space in the current node for the value, need to shift the children as well (only when insert new value before or inbetween values)
	* if not then create a link to a new child and assign this child the value
	* if the value belongs between two values in a full node then split and promote
	* Question: is the algorithm top down or bottom up? Looks like its top down approach
	* Split and promote when encountering an order 4 node

	Bottom up vs Top down
	* Top down trees split order 4 nodes whenver they are able to whereas bottom up trees only split the order 4 node when they have to
	
	Top down tree advantgaes:
	* More time efficient since they are single pass trees.
		worst case better, dont have to go all the way down and then splits all the way up 
		however top down trees tend to be a bit deeper
	* More memory efficient 
	* better for multi-threads
	* merge might not need to be called than once since...
	* TOP DOWN: not possible to have an order 4 node under an order 4 node

	Errors:
	* 86 11 84 38 40 27 17 50 40 9 (error occurs when isnerting 27)
	* 61 1 51 5 30 47 43 27 77 39 (works fine just splits the root so it looks weird)

*/
Node insertNode(Node n, int value)
{
	Node retNode = NULL;
	Node leftNode = NULL, rightNode = NULL;
	int i = 0, prevOrder = 0;

	for (i = 0; i < n->order - 1; i++){
		if (value < n->values[i]){
			break;
		}
	}

	if (n->order < MAX_CHILDREN){
		#ifdef DEBUG
		printf("Not a order 4 node.\n");
		printf("i = %d.\n", i);
		#endif
		if (n->child[i] == NULL){
			#ifdef DEBUG
				printf("Has no children.\n");
			#endif
			if (i == 0){ // add before first node
				shiftArray(n->values, i, MAX_VALUES);
				n->values[i] = value;
				shiftNodes(n->child, 1, MAX_CHILDREN);
			}

			else if (i == 1){
				if (n->order == 2){ // add after the single node
					n->values[i] = value;
				}

				if (n->order == 3){ // insert inbetween two values
					// change the links appropriately
					shiftArray(n->values, i, MAX_VALUES);
					n->values[i] = value;
				}
			}

			else{ // insert after last value in order 3
				n->values[i] = value;
				n->child[i + 1] = NULL;
			}
			n->order++;
		}

		else{
			#ifdef DEBUG
			printf("Has children.\n");
			#endif
			prevOrder = n->child[i]->order;
			retNode = insertNode(n->child[i], value);
			if (SPLIT_PROMOTE(prevOrder, retNode->order)){ // n->child[i] was split
				#ifdef DEBUG
					printf("Merging the two nodes.\n");
					printf("retNode->values[0] = %d.\n", retNode->values[0]);
				#endif
				n = mergeNodes(n, retNode, i, i + 1);
			}
		}
	}

	else{ // split and promote
		// create the left and right nodes
		#ifdef DEBUG
			printf("Splitting and promoting order 4 node.\n");
		#endif
		leftNode = newNode(n->values[0]);
		rightNode = newNode(n->values[2]);
		assert(leftNode != NULL && rightNode != NULL);

		// assign the left node
		leftNode->child[0] = n->child[0];
		leftNode->child[1] = n->child[1];

		// assign the right node
		rightNode->child[0] = n->child[2];
		rightNode->child[1] = n->child[3];
	
		// n is the middle node being split and promoted
		n->values[0] = n->values[1];
		n->child[0] = leftNode;
		n->child[1] = rightNode;
		n->order = 2; // reset back to order 2

		n->values[1] = n->values[2] = 0;
		n->child[2] = n->child[3] = NULL;

		#ifdef DEBUG
			printf("l->value = %d and r->value = %d\n", leftNode->values[0], rightNode->values[0]);
		#endif
		if (value == n->values[0]){
			n->values[0] = value;
		}

		else if (value < n->values[0]){ // add to the left child
			#ifdef DEBUG
				printf("Joining with leftnode.\n");
			#endif
			prevOrder = n->child[0]->order;
			n->child[0] = insertNode(n->child[0], value);
			/* TOP DOWN: don't need this
			if (SPLIT_PROMOTE(prevOrder, retNode->order)){ // the node called split as well
				#ifdef DEBUG
					printf("Merge function's fault.\n");
				#endif
				n = mergeNodes(n, retNode, 0, 1); 
			}
			*/
		}

		else{ // add to the right child
			#ifdef DEBUG
				printf("Joining with rightnode.\n");
			#endif
			prevOrder = n->child[1]->order;
			n->child[1] = insertNode(n->child[1], value);
			/*
			if (SPLIT_PROMOTE(prevOrder, retNode->order)){ // the node called split as well
				#ifdef DEBUG
					printf("Merge function's fault.\n");
				#endif
				n = mergeNodes(n, retNode, 1, 2);
			}
			*/
		}
	}
	return n;
}

/*
	Merges two nodes: (used for split and promote)
	* n1 is node used for the insert call and n2 is node being returned after an insert call
	* n1 is given the links of n2 as well as the value of n2 (merging)
	* note n1 can be any order and n2 must be strictly order 2
	* Implemented only for use with the insert function
*/
Node mergeNodes(Node n1, Node n2, const int link1, const int link2)
{
	#ifdef DEBUG
		printf("[BEFORE SHIFTING]: \n");
		printArray(n1->values, MAX_VALUES);
	#endif
	shiftArray(n1->values, link1, MAX_VALUES); // shift the array and the nodes
	shiftNodes(n1->child, link1, MAX_CHILDREN); // depending on the value if link1, shifting may not occur
	#ifdef DEBUG
		printf("[AFTER SHIFTING]: \n");
		printArray(n1->values, MAX_VALUES);
	#endif
	n1->values[link1] = n2->values[0];

	// give n1 the links of n2
	n1->child[link1] = n2->child[0];
	n1->child[link2] = n2->child[1];
	n1->order++;
	return n1;
}

// shifts the elements in the array up by one position
void shiftArray(int *a, const int startIndex, const int max)
{
	int i = 0;
	for (i = max - 1; i > startIndex; i--){
		a[i] = a[i - 1];
	}
	a[startIndex] = 0;
}

// shift the nodes up
void shiftNodes(Node *nodes, const int startIndex, const int max)
{
	int i = 0;
	for (i = max - 1; i > startIndex; i--){
		nodes[i] = nodes[i - 1];
	}
	nodes[startIndex] = NULL;
}

/* ================================ search the tree =================== */
// searches the 2-3-4 tree for a value
int search(Tree t, int value)
{
	int found = FALSE;
	Node n = searchNode(t->root, value);
	if (n != NULL) { found = TRUE; }
	return found;
}

Node searchNode(Node n, int value)
{
	if (n == NULL) { return NULL; }

	int i = 0, foundNode = FALSE;
	Node retNode = NULL;
	for (i = 0; i < n->order - 1; i++){ // try to find the value in the current node
		if (n->values[i] == value){
			retNode = n;
			foundNode = TRUE;
			break;
		}
	}

	if (!foundNode){ // didnt find value in current node
		for (i = 0; i < n->order; i++){ // look in n's child nodes
			retNode = searchNode(n->child[i], value);
			if (retNode != NULL){
				break;
			}
		}
	}

	return retNode;
}

/* ======================== remove a node from the tree ===================== */

/*
	Notes:
	Algorithm:
	1) find element to be deleted, if element is not in a order 2 node then find its successor and replace the value to be deleted with the successor. Delete the successor.
	2) If the ndoe is not an order 2 node, and has no children, simply shift array of vlaues and array of nodes down removing the target value.
	3) Encountering an order 2 node when searching for value:
		If sibling is a 3 or 4 node then do rotation, transforms the order 2 node into an order 3 node
			Rotation:
			* Value closest to the order 2 node from the sibling is rotated up into the parent
			* the parent's value overlooking the order 2 node is moved down into the order 2 node creating an order 3 node.
			* the sibling that has its key rotated, is now this newly order 3 node's additional child.
		
		If parent is a 2 node and siblings are two nodes, combine all nodes to form an order 4 node (only works if the parent node is root? )
		
		If the parent is an order 3 or order 4 node and all other siblings are order 2 nodes then do a FUSION:
			Fusion:
			* Pick an apropriate adjacent sibling and get the parent key overlooking the two siblings (1 adjacent sib + the order 2 node) and combine these values to form an order 4 node.
			* transfer the sibling's children to this node

		Function should never lead to an order 2 leaf unless that leaf contains the value to be deleted

	Note:
		Predecessor -> largest item smaller than the current element
		Successor -> smallest element larger than the current element 
	
	Still need to do:
	* make deleting a node more efficient
*/

void removeValue(Tree t, int value)
{
	if (t != NULL){
		Node n = searchNode(t->root, value); // extra precaution
		if (n != NULL){
			if (t->root != NULL){ 
				t->root = deleteNode(t->root, value);
			}
		}
	}
}

Node deleteNode(Node n, int value)
{
	int indexTraverse = 0, found = FALSE;
	int successor = 0, predecessor = 0;
	Node leftSibling = NULL, rightSibling = NULL;
	Node leftChild = NULL, rightChild = NULL;
	Node nodeToTraverse = NULL;

	if (n == NULL) { return NULL; }

	// search for the value in the current node
	for (indexTraverse = 0; indexTraverse < n->order - 1; indexTraverse++){
		if (value < n->values[indexTraverse]){ break; }
		if (value == n->values[indexTraverse]){ found = TRUE; break; }
	}
	
	#ifdef DEBUG
		printf("inverseTraverse = %d.\n", indexTraverse);
	#endif
	
	// found 0 <= indexTraverse <= 2 and indexTraverse == 3 when not found
	if (n->order >= 3 && found){ // always delete from a order 3 or order 4 node
		leftChild = n->child[indexTraverse];
		rightChild = n->child[indexTraverse + 1]; // right sibling of the node to traverse
	
		#ifdef DEBUG
			printf("Deleting from order >= 3 node.\n");
		#endif

		if ((leftChild != NULL && rightChild != NULL) && (leftChild->order == 2 && rightChild->order == 2)){ // no spare leafs to find a successor or predecessor
			#ifdef DEBUG
				printf("Fusion in a 3-4 node.\n");
			#endif
			n->child[indexTraverse] = fusion(n, leftChild, rightChild, indexTraverse); // do a fusion to form an order 4 node which includes the target value to delete
			free(rightChild); // safe? Yes since all the nodes of the right child have been mvoed over to the left
			n->child[indexTraverse + 1] = NULL; // remove the link to the right child
		
			// shift the values and nodes down appropriately	
			shiftDown(n->values, indexTraverse, n->order);
			shiftNodesDown(n->child, indexTraverse + 1, n->order);
			n->order--;
			
			n->child[indexTraverse] = deleteNode(leftChild, value); // now delete the target value from the order 4 node
		}
		
		else if (rightChild != NULL && rightChild->order >= 3){ // finding smallest successor
			#ifdef DEBUG
				printf("Finding smallest number in right branch.\n");
			#endif
			successor = findMinimal(rightChild); // find minimal in right branch
			n->values[indexTraverse] = successor;
			n->child[indexTraverse + 1] = deleteNode(rightChild, successor);
		}

		else if (leftChild != NULL && leftChild->order >= 3){ // find predecessor
			#ifdef DEBUG
				printf("Finding largest number to use as replacement.\n");
			#endif
			predecessor = findMaximal(leftChild); // find maximal in left branch
			n->values[indexTraverse] = predecessor;
			n->child[indexTraverse] = deleteNode(leftChild, predecessor); // delete the succesor value
		}

		else{ // remove the value from the array of values
			#ifdef DEBUG
				printf("Simply removing.\n");
			#endif
			if (indexTraverse != n->order - 2){
				shiftDown(n->values, indexTraverse, n->order); // shifts the values down, removing the target value
				shiftNodesDown(n->child, indexTraverse, n->order); // shift the nodes down
			}
			n->order--; // reduce the order of the node since we removed a value
		}
	}

	else if (n->order == 2 && found){ // found value in an order 2 node
		#ifdef DEBUG
			printf("Found value in an order 2 node.\n");
		#endif

		leftChild = n->child[0];
		rightChild = n->child[1];
		if (leftChild != NULL && leftChild->order >= 3){ // find a predecessor
			predecessor = findMaximal(leftChild);
			n->values[0] = predecessor; // replace the value to be deleted with the successor
			n->child[0] = deleteNode(leftChild, predecessor); // delete the successor
		}

		else if (rightChild != NULL && rightChild->order >= 3){ // find a successor
			successor = findMinimal(rightChild);
			n->values[0] = successor;
			n->child[1] = deleteNode(rightChild, successor);
		}

		// no left or right child, i.e deleting last node from tree
		else if (leftChild == NULL && rightChild == NULL){ // only free order-2 leaves
			free(n); // free the node
			n = NULL;
		}

		else{
			if (leftChild != NULL && rightChild != NULL && leftChild->order == 2 && rightChild->order == 2){ // n's childs are order 2 nodes
				n = mergeThreeNodes(n, leftChild, rightChild);
				n = deleteNode(n, value);
			}
		}
		
	}

	else{ // inside an order - 2,3,4 node and value not found
		if (indexTraverse < n->order - 1) { rightSibling = n->child[indexTraverse + 1]; } // right sib of node we want to traverse
		leftSibling = n->child[indexTraverse - 1]; // left sib of node we want to traverse
		
		// reference the left child and right child
		nodeToTraverse = n->child[indexTraverse]; // this is the node we want to traverse
		
		#ifdef DEBUG
			printf("!found or child to traverse is order 2.\n");
		#endif 
		
		if (nodeToTraverse != NULL && nodeToTraverse->order == 2){ // the node we want to go to is order 2
			// merge to form an order 4 node
			if (n->order == 2 && rightSibling != NULL && rightSibling->order == 2){ // parent is order 2 and right sib is order 2
				#ifdef DEBUG
					printf("Merging to form order-4 node with right child.\n");
				#endif

				// merge all three nodes to form an order 4 node
				n = mergeThreeNodes(n, nodeToTraverse, rightSibling);
				// printf("n->order = %d\n", n->order);
				n = deleteNode(n, value);
				// free(nodeToTraverse);
				// free(rightSibling);
			}

			else if (n->order == 2 && leftSibling != NULL && leftSibling->order == 2){ // left sib is order 2 and parent is order 2
				#ifdef DEBUG
					printf("Merging to form order-4 node with left child.\n");
				#endif
		
				// merge all the nodes to form an order 4 node
				n = mergeThreeNodes(n, leftSibling, nodeToTraverse);
				n = deleteNode(n, value);
				// free(nodeToTraverse);
				// free(leftSibling);
			}

			else{ // parent is not order 2
				#ifdef DEBUG
					printf("Node we want to traverse is order 2.\n");
				#endif
				if (indexTraverse >= 0 && indexTraverse < n->order - 1){ // simply check right
					if (rightSibling != NULL){
						#ifdef DEBUG
							printf("Checking if right sibling has spare leaves.\n");
						#endif
						if (rightSibling->order >= 3){ // steal from right sibling
							#ifdef DEBUG
								printf("Stealing from right sibling.\n");
							#endif
							n = rotateLeft(n, rightSibling, indexTraverse);
						}

						else{ // do fusion since right sib is an order 2 node
							#ifdef DEBUG
								printf("Fusing.\n");
							#endif
							nodeToTraverse = fusion(n, nodeToTraverse, rightSibling, indexTraverse);
	 						free(rightSibling);
							n->child[indexTraverse + 1] = NULL;
							// shift the values down
							shiftDown(n->values, indexTraverse, n->order);
							shiftNodesDown(n->child, indexTraverse + 1, n->order);
							n->order--; // we stole a value from the parent so decrease it's order
						}
						n->child[indexTraverse] = deleteNode(nodeToTraverse, value);
					}
				}

				else if (indexTraverse == n->order - 1){ // check left for any spare leaves
					if (leftSibling != NULL){
						#ifdef DEBUG
							printf("Checking if left sibling has spare leaves.\n");
						#endif
						if (leftSibling->order >= 3){ // steal from left sibling
							#ifdef DEBUG
								printf("Stealing from left sibling.\n");
							#endif
							n = rotateRight(n, leftSibling, indexTraverse - 1); // indexTraverse is used to lookup a value and indexTraverse >= 3 does not exist
							n->child[indexTraverse] = deleteNode(nodeToTraverse, value);
						}

						else{ // do a fusion operation since left sibling is an order 2 node
							#ifdef DEBUG
								printf("Fusing.\n");
							#endif
							leftSibling = fusion(n, leftSibling, nodeToTraverse, indexTraverse - 1);
							free(nodeToTraverse);
							n->child[indexTraverse] = NULL;
	
							shiftDown(n->values, indexTraverse - 1, n->order);
							shiftNodesDown(n->child, indexTraverse, n->order);	
							n->order--;
							n->child[indexTraverse - 1] = deleteNode(leftSibling, value);
						}
					}
				}
			}
		}

		else{ // if the node we want to traverse to is not NULL and is not order 2
			#ifdef DEBUG
				printf("Going to the next 3-4 node.\n");
			#endif
			n->child[indexTraverse] = deleteNode(nodeToTraverse, value);
		}

	}
	
	return n;
}

// rotates the tree right
Node rotateRight(Node parent, Node c1, int valueIndex)
{
	int valueStolen = 0, valuePassedDown = 0, leftOrder = c1->order, nodeIndex = valueIndex + 1;
	valueStolen = c1->values[leftOrder - 2]; // steal a value from the left sibling that is closest to our target node
	c1->order--; // stole a node from c1 so decrease its order
	valuePassedDown = parent->values[valueIndex]; // bring down a value from the parent
	parent->values[valueIndex] = valueStolen; // bring the value stolen up into the parent
	if (c1->child[leftOrder - 1] != NULL && c1->child[leftOrder - 2] != NULL){
		c1->child[leftOrder - 2] = mergeTwoNodes(c1->child[leftOrder - 1], c1->child[leftOrder - 2]);
	}
	shiftArray(parent->child[nodeIndex]->values, 0, MAX_VALUES); // shift the valeus in c2 up to make room for the passed down value
	shiftNodes(parent->child[nodeIndex]->child, 0, MAX_CHILDREN); // assuming it has any nodes
	parent->child[nodeIndex]->values[0] = valuePassedDown; // pass the vlaue down to the right child
	parent->child[nodeIndex]->order++; // there are now two values in the right child
	return parent;
}

// rotates a tree left
Node rotateLeft(Node parent, Node c2, int valueIndex)
{
	int valueStolen = 0, valuePassedDown = 0;
	valueStolen = c2->values[0]; // steal a value from the right sibling closest to the target node
	if (c2->child[0] != NULL && c2->child[1] != NULL){ // the value being stolen has left and right nodes, so merge the nodes
		c2->child[0] = mergeTwoNodes(c2->child[0], c2->child[1]);
	}

	shiftDown(c2->values, 0, c2->order); // shift the values down
	shiftNodesDown(c2->child, 1, c2->order); // shift c2's nodes down
	c2->order--; // reduce the order since we stole a value from it
	valuePassedDown = parent->values[valueIndex]; // take the appropriate value from the parent
	parent->values[valueIndex] = valueStolen; // assign the parent the value that was stolen from the right child
	parent->child[valueIndex]->values[1] = valuePassedDown; // pass down a value from the parent into the left child
	parent->child[valueIndex]->order++; // increase the order of the left child
	return parent; // return the modified parent
}

// does a fusion operation. i.e node from parent goes down and combines with the two order-2 nodes
Node fusion(Node parent, Node childLeft, Node childRight, int indexValue)
{
	int values[MAX_VALUES] = {0}; // array to hold the values of the other nodes
	Node nArray[MAX_CHILDREN] = {NULL}; // store the ptrs of the other nodes
	int i = 0;
	
	values[0] = childLeft->values[0]; // fill the values array
	values[1] = parent->values[indexValue];
	values[2] = childRight->values[0];

	nArray[0] = childLeft->child[0]; // fill the array of nodes
	nArray[1] = childLeft->child[1];
	nArray[2] = childRight->child[0];
	nArray[3] = childRight->child[1];

	// copy into the left child
	for (i = 0; i < MAX_VALUES; i++){
		childLeft->values[i] = values[i];
	} 

	for (i = 0; i < MAX_CHILDREN; i++){
		childLeft->child[i] = nArray[i];
	}

	childLeft->order = 4; // left child is now an order 4 node
	return childLeft;
}

// merges two nodes into one or creates a new subtree
Node mergeTwoNodes(Node n1, Node n2)
{
	// Node leftNode = NULL, rightNode = NULL; // creating a new subtree if we have to
	int i = 0, insertCount = 0;

	if ((n1->order <= 3 && n2->order == 2) || (n1->order == 2 && n2->order <= 3)){
		#ifdef DEBUG
		printf("Merging nodes.\n");
		#endif
		insertCount = n1->order - 1;
		for (i = 0; i < n2->order - 1; i++){
			n1->values[insertCount++] = n2->values[i];
		}
		
		n1->order += i;
		insertCount = n1->order - 1;
		if (n1->child[insertCount] != NULL && n2->child[0] != NULL){
			n1->child[insertCount] = mergeTwoNodes(n1->child[insertCount], n2->child[0]);
			insertCount++;
		}

		for (i = 0; i < n2->order; i++){
			n1->child[insertCount++] = n2->child[i];
		}
	}

	else{ // merging two very large nodes
		// use n1 as the middle node
		// leftNode = malloc(sizeof(node));
		// rightNode = malloc(sizeof(node));
		printf("Need to account for the children of these nodes.\n"); // this case is extremely unlikely to occur
		printf("When they both are 3 or 4 nodes.\n");
		exit(1);
	}
	return n1;
}

/*
	Merges 3 order 2 nodes into one to create an order 4 node
	* assumes that child1 and child2 are not NULL
	* also value in child2 is greater than value in child1
*/

Node mergeThreeNodes(Node parent, Node child1, Node child2)
{
	int i = 0;
	Node nArray[MAX_CHILDREN] = {NULL}; // temp node array to store children of the children
	int values[MAX_VALUES] = {0};

	values[0] = child1->values[0]; // construct the array of values
	values[1] = parent->values[0];
	values[2] = child2->values[0];

	for (i = 0; i < MAX_VALUES; i++){
		parent->values[i] = values[i]; // overwrite the current array in the parent
	}

	#ifdef DEBUG
		printArray(parent->values, 4);
	#endif

	nArray[0] = child1->child[0]; // construct the array of children
	nArray[1] = child1->child[1];
	nArray[2] = child2->child[0];
	nArray[3] = child2->child[1];

	for (i = 0; i < MAX_CHILDREN; i++){
		parent->child[i] = nArray[i]; // overwrite the children array in the parent
	}
	
	parent->order = 4; // parent is not an order 4 node
	return parent; // return the merged parent
}

// shifts the values in an array down by one
void shiftDown(int *a, const int startIndex, const int size)
{
	int i = 0;
	for (i = startIndex; i < size - 2; i++){
		a[i] = a[i + 1];
	}
}

// shifts the nodes in the children array down by one
void shiftNodesDown(Node *nArray, const int startIndex, const int max)
{
	int i = 0;
	for (i = startIndex; i < max - 1; i++){
		nArray[i] = nArray[i + 1];
	}
}

// finds the max value element in a tree
int findMaximal(Node n)
{
	int largestNumber = 0; 
	if (n->order == 2){
		if (n->child[1] == NULL){ // base case
			largestNumber = n->values[0];
		}
		
		else{
			largestNumber = findMaximal(n->child[1]);
		}
	}

	else if (n->order == 3){
		if (n->child[2] == NULL){
			largestNumber = n->values[1];
		}

		else{
			largestNumber = findMaximal(n->child[2]);
		}
	}

	else{
		if (n->child[3] == NULL){
			largestNumber = n->values[2];
		}

		else{
			largestNumber = findMaximal(n->child[3]);
		}
	}

	return largestNumber; 
}

// finds the min value element in a tree
int findMinimal(Node n)
{
	int smallestNumber = 0;

	if (n != NULL){
		if (n->child[0] == NULL) { smallestNumber = n->values[0]; } // base case
		else{
			smallestNumber = findMinimal(n->child[0]);
		}
	}
	return smallestNumber;
}

/* ======================= show the tree ================================= */
// prints the tree
void printTree(Tree t, int order)
{
	if (order == PREORDER){
		preOrder(t->root);
	}
}

// preorder traversal of tree
void preOrder(Node n)
{
	int i = 0;
	// print each node
	if (n != NULL){
		printf("[");
		for (i = 0; i < n->order - 1; i++){
			printf("%d ", n->values[i]);
		}
		printf("]\n");
	
		for (i = 0; i < n->order; i++){
			preOrder(n->child[i]);
		}
	}
}

// creates a new node
static Node newNode(int value)
{
	Node n = malloc(sizeof(node));
	n->order = 2; // always start with a order 2 node
	n->values[0] = value;
	n->child[0] = n->child[1] = n->child[2] = n->child[3] = NULL;
	return n;
}

#ifdef DEBUG
// debugging functions
static void printArray(int *a, const int max)
{
	int i = 0; 
	for (i = 0; i < max - 1; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}
#endif




