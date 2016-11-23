/*
	Name: Matthew Ta
	Date: 12/11/2015
	Description: Implementation of the tries ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tries.h"

#define TRUE 1
#define FALSE 0

#define NULL_CHAR '\0'

// #define DEBUG // debugging constant

typedef struct _node{
	char keyBit; // part of the key
	int finished; // does this key finish a word (might be multiple finishes in a path)
	Item data; // if not finished then no value
	Node child;
	Node sibling;
} node;

typedef struct _trieRep{
	Node root;
} trieRep;

static Node newTrieNode(Key k, int i, Item it); // create a new trie node

Node findNode(Trie t, Key k); // tries to find a node in the trie

// function helpers to disposing the trie
void deleteTrie(Node n); 
void deleteTrieDown(Node n);
void deleteTrieAcross(Node n);

void printTrie(Node n); // helper function of showTrie()

void printDown(Node n);
void printAcross(Node n);

// create a new trie
Trie newTrie(void)
{
	Trie t = malloc(sizeof(trieRep));
	assert(t != NULL);
	t->root = NULL;
	return t;
}

// dispose a trie
void disposeTrie(Trie t) // function for user to call
{
	if (t != NULL){
		deleteTrie(t->root);
	}
}

void deleteTrie(Node n) // this deletes the trie
{
	if (n != NULL){
		deleteTrieDown(n->child);
		deleteTrieAcross(n->sibling);
		#ifdef DEBUG
			printf("Freeing [%c]\n", n->keyBit);
		#endif
		free(n);
	}
}

void deleteTrieDown(Node n) // delete trie in the child direction
{
	if (n != NULL){
		deleteTrieDown(n->child);
		deleteTrieAcross(n->sibling);
		#ifdef DEBUG
			printf("Freeing [%c]\n", n->keyBit);
		#endif
		free(n);
	}

}

void deleteTrieAcross(Node n) // delete the trie in the sibling direction
{
	if (n != NULL){
		deleteTrieDown(n->child);
		deleteTrieAcross(n->sibling);
		#ifdef DEBUG
			printf("Freeing [%c]\n", n->keyBit);
		#endif
		free(n);
	}
}

// insert an item into a trie
void insertItem(Trie t, Item it)
{
	Key k; // key for the item
	char *c; // used to traverse chars in key
	int i = 0;
	Node foundNode, prev, cur;
	
	if (t != NULL){
		k = key(it); // convert item into a key
		c = k;
		
		// empty trie
		if (t->root == NULL){
			t->root = newTrieNode(k, 0, it);
		}
	
		foundNode = findNode(t, k); // check if k is already in trie
		if (foundNode != NULL){ // k is already in trie so just update with new data
			foundNode->finished = TRUE;
			foundNode->data = it;
		}

		else{ // need to insert the key
			cur = t->root;
			prev=  cur;
			for (i = 0; c[i] != NULL_CHAR; i++){	
				#ifdef DEBUG
					if (cur != NULL) printf("cur->keyBt = %c and c[%d] = %c\n", cur->keyBit, i, c[i]);
				#endif
				if (cur == NULL){ // create a child
					#ifdef DEBUG
						printf("Inserting below.\n");
					#endif
					cur = prev->child = newTrieNode(k, i, it);
				}

				else if (cur->keyBit != c[i]){ // create a sibling
					Node temp = prev, tempPrev = NULL;
					while (temp != NULL && temp->keyBit != c[i]){ // traverse the siblings
						tempPrev = temp;
						temp = temp->sibling;
					}

					if (temp == NULL){ // insert a sibling
						#ifdef DEBUG
							printf("Inserting across.\n");
						#endif
						prev = tempPrev->sibling = newTrieNode(k, i, it); 
						cur = prev;
					}

					else{ // found existing sibling
						#ifdef DEBUG
							printf("Found a sibling to join with.\n");
							printf("temp->k = %c.\n", temp->keyBit);
						#endif
						cur = temp; // traverse about this sibling
					}
				}

				if (c[i+1] == NULL_CHAR){ cur->finished = TRUE; cur->data = it; break; } // end of key
				
				prev = cur;
				cur = cur->child; // traverse down
			}
		}
	}
}

// searches for a particular item
Item *searchItem(Trie t, Key k)
{
	Item *it = NULL;
	Node foundNode = NULL;
	if (t != NULL){
		foundNode = findNode(t, k);
		if (foundNode != NULL){
			it = &foundNode->data;
		}
	}
	return it;
}

// remove an item from the trie
void removeItem(Trie t, Key k)
{
	Node foundNode = NULL;
	if (t != NULL){
		foundNode = findNode(t, k);
		if (foundNode->finished == TRUE){
			foundNode->finished = FALSE;
		}
	}
}

// attempts to find a node in the trie
Node findNode(Trie t, Key k)
{
	Node cur = NULL;
	char *c = NULL;
	int i = 0;
	if (t != NULL){
		cur = t->root;
		c = k; 
		while (c[i] != NULL_CHAR && cur != NULL){
			// search through the siblings
			#ifdef DEBUG
				printf("*c = %d and cur->kb = %c\n", c[i], cur->keyBit);
			#endif
			while (cur != NULL && cur->keyBit != c[i]){
				cur = cur->sibling;
			}	

			if (cur == NULL) { return NULL; } // no key bits in child or sibling direction		
			if (cur->finished == TRUE && c[i+1] == NULL_CHAR){ return cur; } // found the key (returns finished node)

			// determine whether we need to check sibling
			if (cur->child != NULL){
				if (cur->child->keyBit != c[i + 1]){
					cur = cur->sibling;
				}

				else{
					cur = cur->child;
				}
			}
			i++;
		}
	}

	return NULL;
}

// creates a new node for a trie
static Node newTrieNode(Key k, int i, Item it) // insert a letter in the key into a node
{
	assert(k != NULL); // make sure we havent been given a NULL key
	Node n = malloc(sizeof(node));
	assert(n != NULL);
	// determine if inserting last letter
	n->keyBit = k[i];
	if (*(k+(i+1)) == NULL_CHAR){
		n->finished = TRUE;
		n->data = it;
	}

	else{
		n->finished = FALSE;
		n->data = NULL;
	}
	n->child = NULL;
	n->sibling = NULL;
	return n;
}

// output the trie
void showTrie(Trie t)
{
	if (t != NULL){
		printTrie(t->root);
	}
}

void printTrie(Node n)
{
	if (n != NULL){
		printDown(n->child->sibling->sibling);
		// printDown(n->child->child->sibling);
		// printDown(n->sibling);
	}
}

void printDown(Node n)
{
	if (n != NULL){
		printf("[%c] and f = %d\n", n->keyBit, n->finished);
		printDown(n->child);
		//printAcross(n->sibling);
	}
}

void printAcross(Node n)
{
	if (n != NULL){
		// printDown(n->child);
		printf("%c\n", n->keyBit);
		printAcross(n->sibling);
	}
}



