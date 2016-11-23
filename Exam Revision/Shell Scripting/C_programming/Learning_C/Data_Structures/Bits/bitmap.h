/*
	Name: Matthew Ta
	Date: 14/11/2015
	Description: ADT for Bitmap rep of sets
*/

// Note: can only store values from 1..(max - 1)

typedef struct _setRep *Bits;
typedef unsigned int Word;

Bits newSet(int max); // create a set with max number being last index in bitmap
void disposeSet(Bits b); // frees the set

void insertItem(Bits b, int it); // insert an item into the set
void removeItem(Bits b, int it); // remove an item from the set
int searchItem(Bits b, int it); // searches for an item in the set

int isPowerTwo(Word w); // determines if a number is a power of two

Bits joinSets(Bits a, Bits b); // joins two sets together
Bits elemsInCommon(Bits a, Bits b); // returns a set with elements that are in both a and b

int getNumElements(Bits a); // returns # elements in set

void showSet(Bits b); // outputs the set
void showSetSorted(Bits b); // outputs the set in order
void showBits(Bits b);
