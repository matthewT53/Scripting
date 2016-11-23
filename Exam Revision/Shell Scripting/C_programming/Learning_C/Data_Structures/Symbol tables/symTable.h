/*
	Name: Matthew Ta
	Date: 9/11/2015
	Desciption: Interface for the symbol table
*/

typedef int Item; // create a data type for item
typedef int Key; // keys to use to access data

typedef struct _symbolTable *sTab; // pointer to a symbol table data structure

sTab newTable(int n); // creates a new table with n slots
void disposeTable(sTab st); // frees a symbol table

// NOTE: key must be n <= key <= 2n - 1

void insertItem(sTab st, Item value, Key k); // inserts an item into the symbol table
void removeItem(sTab st, Key k); // removes an item from the symbol table
Item *searchItem(sTab st, Key k); 

void printTable(sTab st); // outputs the symbol table
