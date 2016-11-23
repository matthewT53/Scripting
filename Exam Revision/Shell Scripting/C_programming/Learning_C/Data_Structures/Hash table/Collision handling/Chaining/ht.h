/*
	Name: Matthew Ta
	Date: 10/11/2015
	Description: Interface for a hash table
*/

#define key(it) (it) // converts the item into a key

typedef char * Item; // Item is a string
typedef Item Key; // key is the item

typedef struct _hashTableRep *HashTable;

HashTable newTable(int N); // creates a hash table with N elements
void disposeTable(HashTable ht); // frees a hash table

void insertItem(HashTable ht, Item it); // inserts an item into the hash table
void removeItem(HashTable ht, Key k); // removes an item from the hash table
Item *searchItem(HashTable ht, Key k); // searches for an item

HashTable hashTableExpand(HashTable ht, int n); // changes the size of the current ht

void showHashTable(HashTable ht); // outputs the hash table
