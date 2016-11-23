/*
    Name: Matthew Ta
    Date: 14/9/2015
    Description: User of the BST interface
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"

#define SENTINEL_VALUE 0

// tree operations
#define INSERT 1
#define SHOW 2
#define DELETE 3
#define DEPTH 4
#define LEAF 5
#define FIND 6
#define ROTATE_LEFT 7
#define ROTATE_RIGHT 8
#define INSERT_ROOT 9

int main(void)
{
    int choice = 0;
	int value = 0, bytesRead = 0;
    Tree t = newTree();
    TreeNode rootn = getRootNode(t);

    printf("Binary search tree:\n");
    printf(">: ");
    bytesRead = scanf("%d", &choice);
    assert(bytesRead != 0);
    while (choice != SENTINEL_VALUE){
        switch (choice){
            case INSERT:
                printf("Enter a value: ");
                bytesRead = scanf("%d", &value);
                assert(bytesRead != 0);
                insertValue(&rootn, value);
                break;
            case SHOW:
                printf("1 = Inorder, 2 = Preorder, 3 = Postorder\n");
                printf("(traverse) >: ");
                bytesRead = scanf("%d", &value);
                assert(bytesRead != 0);
                switch (value){
                    case 1:
                        inorder(rootn);
                        break;
                    case 2:
                        preorder(rootn);
                        break;
                    case 3:
                        postorder(rootn);
                        break;
                }
                printf("\n");
                break;
			case DELETE:
				printf("Enter value to delete: ");
				bytesRead = scanf("%d", &value);
				assert(bytesRead != 0);
				rootn = deleteNode(rootn, value);
				break;
			case DEPTH:
				printf("Depth of tree is %d.\n", treeDepth(rootn)); break;
			case LEAF:
				printf("Number of leaves is %d.\n", numLeafs(rootn)); break;
			case FIND:
				printf("Enter a value to find: ");
				bytesRead = scanf("%d", &value);
				printf("Value found = %s.\n", treeFindValue(rootn, value) ? "TRUE" : "FALSE");
				break;
			case ROTATE_LEFT:
				rootn = rotateLeft(rootn); break;
			case ROTATE_RIGHT: 
				rootn = rotateRight(rootn); break;
			case INSERT_ROOT:
				printf("Insert (root): ");
				bytesRead = scanf("%d", &value);
				assert(bytesRead != 0);
				rootn = insertRoot(rootn, value);
				break;
            default:
                printf("Unknown command.\n");
                break;
        }

        printf(">: ");
        bytesRead = scanf("%d", &choice);
        // rootn = getRootNode(t);
    }

    deleteTree(rootn);
    return EXIT_SUCCESS;
}
