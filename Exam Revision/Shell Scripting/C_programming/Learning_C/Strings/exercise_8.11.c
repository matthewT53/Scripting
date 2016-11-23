/*
	Name: Matthew Ta
	Date: 28/6/2015
	Description: Uses random number generation to construct and print random sentences

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define SENTENCE_SIZE 100
#define MAX_SIZE 5
#define MAX_SENTENCES 20

/* 
	Note: for the short story and long term paper, simply add more words to choose from and increase the MAX_SENTENCE constant
*/

int main(void)
{
	const char *articles[MAX_SIZE] = {"the", "a", "one", "some", "any"};
	const char *nouns[MAX_SIZE] = {"boy", "girl", "dog", "town", "car"};
	const char *verbs[MAX_SIZE] = {"drove", "jumped", "ran", "walked", "skipped"};
	const char *prepositions[MAX_SIZE] = {"to", "from", "over", "under", "on"};
	char sentence[SENTENCE_SIZE] = {0};
	int i = 0, j = 0;
	int randomNumber[MAX_SIZE + 1] = {0}, sentenceLength = 0;
	
	srand(time(NULL));

	// word is constructed in the order article->noun->verb->preposition->article->noun
	for (i = 0; i < MAX_SENTENCES; i++){
		for (j = 0; j <= MAX_SIZE; j++){
			randomNumber[j] = rand() % MAX_SIZE;
		}

		strcat(sentence, articles[randomNumber[0]]);
		strcat(sentence, " ");
		strcat(sentence, nouns[randomNumber[1]]);
		strcat(sentence, " ");
		strcat(sentence, verbs[randomNumber[2]]);
		strcat(sentence, " ");
		strcat(sentence, prepositions[randomNumber[3]]);
		strcat(sentence, " ");
		strcat(sentence, articles[randomNumber[4]]);
		strcat(sentence, " ");
		strcat(sentence, nouns[randomNumber[5]]);
		// need to join a space into these sentences
		*sentence = toupper(*sentence);
		sentenceLength = strlen(sentence);
		*(sentence + sentenceLength) = '.';
		*(sentence + sentenceLength + 1) = '\0';
		printf("%s\n", sentence); 
		memset(sentence, 0, SENTENCE_SIZE);
	}
	
	return 0;
}
