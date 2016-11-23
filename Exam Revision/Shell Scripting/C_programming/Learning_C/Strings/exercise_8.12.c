/*
	Name: Matthew Ta
	Date: 29/6/2015
	Description: Program to randomly generate limericks
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <assert.h>

// constants for array sizes
#define START_INDEX 0
#define MAX_SIZE 5
#define LINE_SIZE 100
#define START_SIZE 7
#define POS_SIZE 12
#define CON_SIZE 9
#define OWN_SIZE 3
#define JUN_SIZE 6
#define OBJECTS_SIZE 22
#define VERBS_SIZE 14
#define DES_SIZE 10

#define MAX_LIMERICKS 20

#define TRUE 1
#define FALSE 0

// this function returns the index of the best word to use for the rhyming
void testFindRhyme(char *[]);
int alreadyUsed(char *[], char *);
// this function still needs improvements
int findRhyme(char *[], char *, int, int);

int main(void)
{
	// strings for line 1
	char *start[MAX_SIZE] = {"There once was", "There was", "Once there was", "Some time, there was", "Few knew there was"};
	char *what[MAX_SIZE] = {"an old lady", "an old man", "a young lady", "a young man", "a boy"};
	char *from = "from";
	char *places[MAX_SIZE] = {"Peru", "Pengoo", "Kentucky", "Abullah", "New York"};
	// const char *people[MAX_SIZE] = {"Janet", "Ibrahim", "Pablo", "Mario", "Mr Bean"};

	// word bank to choose from
	char *lineStarters[START_SIZE] = {"he", "she", "whose", "who", "there", "his", "her"};
	char *prepositions[POS_SIZE] = {"to","from", "over", "under", "on", "at", "beside", "next", "near", "within", "close", "during"};
	char *connectionWords[CON_SIZE] = {"a", "with", "an", "the", "it", "that", "then", "for", "so"};
	char *ownershipWords[OWN_SIZE] = {"had", "was", "have"};
	char *conjunctions[JUN_SIZE] = {"and", "also", "along", "as well as", "including", "which"};
	char *objects[OBJECTS_SIZE] = {"car", "apple", "gun", "haruuu", "light", "tree", "deer", "queer", "watch", "torch", "lunch", "fork", "torque", "bar", "bed", "head", "dollar", "menu", "grapple", "pork", "pun", "waterloo"};
	char *verbs[VERBS_SIZE] = {"touch", "lick", "slap", "eat", "shot", "fired", "tinkled", "felt", "kick", "hit", "punch", "tank", "steal", "said"};
	char *descriptions[DES_SIZE] = {"clean", "dirty", "glean", "size", "large", "small", "miniscule", "dilapidated", "lucky", "squark"};
	char line[LINE_SIZE], *rhyme = NULL, *rhyme2 = NULL;
	char *wordsUsed[MAX_SIZE] = {NULL};
	int randomWord = 0, indexToUse = 0, randomNum = 0;
	int i = 0, wordAlreadyUsed = 0;

	// make the first character of every line capital

	// do some testing first
	testFindRhyme(objects);
	
	// generate the first line
	srand(time(NULL));
	memset(line, 0, LINE_SIZE);
	randomWord = rand() % MAX_SIZE;
	strcat(line, start[randomWord]);
	strcat(line, " ");
	strcat(line, what[randomWord]);
	strcat(line, " ");
	strcat(line, from);
	strcat(line, " ");
	strcat(line, places[randomWord]);
	rhyme = places[randomWord];
	wordsUsed[i] = rhyme;
	i++;
	*line = toupper(*line);
	puts(line);
	
	// generate the second line
	memset(line, 0, LINE_SIZE);
	randomWord = rand() % MAX_SIZE;
	strcat(line, lineStarters[randomWord]);
	strcat(line, " ");
	randomWord = rand() % DES_SIZE;
	strcat(line, descriptions[randomWord]);
	strcat(line, " ");
	randomWord = rand() % OBJECTS_SIZE;
	strcat(line, objects[randomWord]);
	strcat(line, " ");
	randomWord = rand() % VERBS_SIZE;
	strcat(line, verbs[randomWord]);
	strcat(line, " ");
	randomWord = rand() % POS_SIZE;
	strcat(line, prepositions[randomWord]);
	strcat(line, " ");
	randomWord = rand() % CON_SIZE;
	strcat(line, connectionWords[randomWord]);
	strcat(line, " ");
	// find a word that rhymes
	indexToUse = findRhyme(objects, rhyme, OBJECTS_SIZE, START_INDEX);
	strcat(line, objects[indexToUse]);
	wordsUsed[i] = objects[indexToUse];
	i++;
	*line = toupper(*line);
	puts(line);
	
	// generate line 3
	memset(line, 0, LINE_SIZE);
	randomWord = rand() % START_SIZE;
	strcat(line, lineStarters[randomWord]);
	strcat(line, " ");
	// determine how to start
	randomNum = rand() % 2;
	if (randomNum == 0){
		randomWord = rand() % VERBS_SIZE;
		strcat(line, verbs[randomWord]);
		strcat(line, " ");
		randomWord = rand() % POS_SIZE;
		strcat(line, prepositions[randomWord]);
		strcat(line, " ");
		randomWord = rand() % OBJECTS_SIZE;
		strcat(line, objects[randomWord]);
		rhyme2 = objects[randomWord];
		
	}

	else{
		randomWord = rand() % OBJECTS_SIZE;
		strcat(line, objects[randomWord]);
		strcat(line, " ");
		randomWord = rand() % VERBS_SIZE;
		strcat(line, verbs[randomWord]);
		strcat(line, " ");
		randomWord = rand() % CON_SIZE;
		strcat(line, connectionWords[randomWord]);
		strcat(line, " ");
		randomWord = rand() % OBJECTS_SIZE;
		strcat(line, objects[randomWord]);
		rhyme2 = objects[randomWord];
	}
	
	wordsUsed[i] = rhyme2;
	i++;
	*line = toupper(*line);
	puts(line);

	// generate line 4
	memset(line, 0, LINE_SIZE);
	randomWord = rand() % CON_SIZE;
	strcat(line, conjunctions[randomWord]);
	strcat(line, " ");
	randomWord = rand() % VERBS_SIZE;
	strcat(line, verbs[randomWord]);
	strcat(line, " ");
	randomWord = rand() % CON_SIZE;
	strcat(line, connectionWords[randomWord]);
	strcat(line, " ");
	indexToUse = findRhyme(objects, rhyme2, OBJECTS_SIZE, START_INDEX);
	wordAlreadyUsed = alreadyUsed(wordsUsed, objects[indexToUse]);
	while (wordAlreadyUsed == TRUE){
		indexToUse = findRhyme(objects, rhyme2, OBJECTS_SIZE, indexToUse + 1);
		wordAlreadyUsed = alreadyUsed(wordsUsed, objects[indexToUse]);
	}
	strcat(line, objects[indexToUse]);
	wordsUsed[i] = objects[indexToUse];
	i++;
	*line = toupper(*line);
	puts(line);

	// generate final line
	memset(line, 0, LINE_SIZE);
	randomWord = rand() % JUN_SIZE;
	strcat(line, conjunctions[randomWord]);
	strcat(line, " ");
	randomWord = rand() % OWN_SIZE;
	strcat(line, ownershipWords[randomWord]);
	strcat(line, " ");
	randomWord = rand() % CON_SIZE;
	strcat(line, connectionWords[randomWord]);
	strcat(line, " ");
	randomWord = rand() % DES_SIZE;
	strcat(line, descriptions[randomWord]);
	strcat(line, " ");
	randomWord = rand() % OBJECTS_SIZE;
	strcat(line, objects[randomWord]);
	strcat(line, " ");
	randomWord = rand() % JUN_SIZE;	
	strcat(line, conjunctions[randomWord]);
	strcat(line, " ");
	randomWord = rand() % OWN_SIZE;
	strcat(line, ownershipWords[randomWord]);
	strcat(line, " ");
	randomWord = rand() % CON_SIZE;
	strcat(line, connectionWords[randomWord]);
	strcat(line, " ");
	indexToUse = findRhyme(objects, rhyme, OBJECTS_SIZE, START_INDEX);
	wordAlreadyUsed = alreadyUsed(wordsUsed, objects[indexToUse]);
	while (wordAlreadyUsed == TRUE){
		indexToUse = findRhyme(objects, rhyme2, OBJECTS_SIZE, indexToUse + 1);
		wordAlreadyUsed = alreadyUsed(wordsUsed, objects[indexToUse]);
	}
	strcat(line, objects[indexToUse]);
	*line = toupper(*line);
	puts(line);

	return 0;
} 


// if two central letters of word1 is the same as two central letters of word2 then both words rhyme
int findRhyme(char *charArray[], char *word, int arraySize, int startingIndex)
{
	int bestIndex = 0, foundSame = 0, index = 0, foundWord = 0;
	int i = 0, j = 0, k = 0;
	char *currentWord = NULL, currentLetter;

	for (i = startingIndex; i < arraySize && foundWord != 1; i++){
		currentWord = charArray[i];
		// loop though each letter of each word in the charArray
		for (j = 0; *(currentWord + (j + 1)) != '\0' && foundWord != 1; j++){
			currentLetter = *(currentWord + j);
			
			// find letters in word which are the same as currentLetter
			foundSame = 0;
			for (k = 0; *(word + k) != '\0' && foundSame != 1 ; k++){
				// find the index to check from
				if (currentLetter == *(word + k)){
					index = k;
					foundSame = 1;
				}
			}
			
			// if the central words of both words are the same then return the word
			if (*(currentWord + (j + 1)) == *(word + (index + 1)) && foundSame == 1){
				bestIndex = i;
				foundWord = 1;
			}
		}
	}
	
	return bestIndex;
}

int alreadyUsed(char *array[], char *word)
{
	int returnValue = 0;
	int i = 0, breakLoop = 0;

	for (i = 0; i < MAX_SIZE && breakLoop != 1; i++){
		if (array[i] == word){
			returnValue = 1;
			breakLoop = 1;
		}
	}


	return returnValue;

}


void testFindRhyme(char *testArray[])
{
	int index = 0;

	// easy test
	printf("Testing with word: bar.\n");
	char *word = "bar";
	index = findRhyme(testArray, word, OBJECTS_SIZE, START_INDEX);
	printf("(DEBUG): index = %d\n", index);
	assert(index == 0);
	printf("Passed easy test.\n");

	// medium test
	char *word2 = "bright";
	printf("Testing with word: %s.\n", word2);
	index = findRhyme(testArray, word2, OBJECTS_SIZE, START_INDEX);
	printf("(DEBUG): index = %d\n", index);
	assert(index == 4);
	printf("Passed medium test.\n");
	
	// hard test
	char *word3 = "abullah";
	printf("Testing with word %s.\n", word3);
	index = findRhyme(testArray, word3, OBJECTS_SIZE, START_INDEX);
	printf("(DEBUG): index = %d\n", index);
	assert(index == 16);
	printf("Passed hard test.\n");

	char *word4 = "kentucky";
	printf("Testing with word: %s.\n", word4);
	index = findRhyme(testArray, word4, OBJECTS_SIZE, START_INDEX);
	printf("(DEBUG): index = %d\n", index);
	assert(index == 17);
	printf("Passed random test.\n");
	
	printf("All tests passed, you are awesome.\n\n");

}


