/*
	Name: Matthew Ta
	Date: 30/5/2016
	Description: Implementation of Trie data type and operations
	Note: Vulnerable to buffer overflows if user enters a string with length > 1000
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

#define NUM_LETTERS_ALPHABET 26
#define FIRST_LETTER 'a'
#define NULL_CHAR 0
#define MAX_LEN 1000

// boolean constants
#define TRUE 1
#define FALSE 0

typedef struct _trie{
	int flag;
	Trie next[NUM_LETTERS_ALPHABET];
} trie;

void addword_trie(Trie t, String s, int index);
int checkword_trie(Trie t, String s, int index);
void delword_trie(Trie t, String s, int index);
void printWords(Trie t, String s, int index);

// adds a word into the trie
void addword(Trie t, String s)
{
	addword_trie(t, s, 0);
}

void addword_trie(Trie t, String s, int index)
{
	if (t != NULL){
		// base case
		if (s[index] == NULL_CHAR){
			t->flag = TRUE;
		}

		else{
			if (t->next[s[index] - FIRST_LETTER] == NULL){
				t->next[s[index] - FIRST_LETTER] = newTrie(FALSE);
			}

			addword_trie(t->next[s[index] - FIRST_LETTER], s, index + 1);
		}
	}
}

// checks for a word in the trie
int checkword(Trie t, String s)
{
	return checkword_trie(t, s, 0);
}

int checkword_trie(Trie t, String s, int index)
{
	int wordExists = FALSE;
	if (t != NULL){
		if (s[index] == NULL_CHAR){
			wordExists = t->flag;
		}

		else{
			wordExists = checkword_trie(t->next[s[index] - FIRST_LETTER], s, index + 1);
		}
	}

	return wordExists;
}

// deletes a word from the trie
void delword(Trie t, String s)
{
	delword_trie(t, s, 0);
}

void delword_trie(Trie t, String s, int index)
{
	if (t != NULL){
		if (s[index] == NULL_CHAR){
			t->flag = FALSE;
		}

		else{
			delword_trie(t->next[s[index] - FIRST_LETTER], s, index + 1);
		}
	}
}

Trie newTrie(int f)
{
	Trie t = malloc(sizeof(trie));
	int i = 0;
	
	// initialise the data structure
	for (i = 0; i < NUM_LETTERS_ALPHABET; i++){
		t->next[i] = NULL;
	}
	t->flag = f;
	return t;
}

void deleteTrie(Trie t)
{
	int i = 0;
	if (t != NULL){
		for (i = 0; i < NUM_LETTERS_ALPHABET; i++){
			if (t->next[i] != NULL){
				deleteTrie(t->next[i]);
				free(t->next[i]);
			}
		}
	}
}

void showTrie(Trie t)
{
	char s[MAX_LEN] = {0};
	if (t != NULL){
		printWords(t, s, 0);
	}
}

void printWords(Trie t, String s, int index)
{
	int i = 0, j = 0;
	if (t != NULL){
		for (i = 0; i < NUM_LETTERS_ALPHABET; i++){
			// clear everything past the current index
			for (j = index; j < MAX_LEN; j++){
				s[j] = NULL_CHAR;
			}	

			// go to the letter below
			if (t->next[i] != NULL){
				s[index] = i + FIRST_LETTER;	
				printWords(t->next[i], s, index + 1); 
				// print the word
				if (t->next[i]->flag == TRUE){
					printf("%s\n", s);
				}
			}
		}
	}
}

