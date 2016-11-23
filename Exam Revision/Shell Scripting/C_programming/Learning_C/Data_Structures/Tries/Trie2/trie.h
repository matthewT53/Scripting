/*
	Name: Matthew Ta
	Date: 30/5/2016
	Description: Alternate Trie representation
*/

#ifndef TRIE_H
#define TRIE_H

typedef struct _trie * Trie;
typedef char * String; 

// creates and returns a new trie
Trie newTrie(int f);

// frees all the memory resources used by the Trie
void deleteTrie(Trie t);

/*
	t = trie data type to operate on
	s = string that is used to operate on the trie
*/

// adds a word into the trie
void addword(Trie t, String s);

// checks for a word in the trie
int checkword(Trie t, String s);

// removes a word from the trie
void delword(Trie t, String s);

// prints all the words in the Trie
void showTrie(Trie t);

#endif
