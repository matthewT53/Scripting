/*
	Name: Matthew Ta
	Date: 12/11/2015
	Description: Interface for tries ADT
*/

#define key(it) (it) // uses the same string as a key for simplicity

// some data stuff
typedef char * Item;
typedef char * Key;

typedef struct _node *Node; // pointer to node structure
typedef struct _trieRep *Trie; // ptr to trie structure

Trie newTrie(void); // creates a new trie
void disposeTrie(Trie t); // frees a current trie

void insertItem(Trie t, Item it); // insert an item into the trie
Item *searchItem(Trie t, Key k); // search for an item in the trie
void removeItem(Trie t, Key k); // remove na item from the trie

void showTrie(Trie t); // output the trie



