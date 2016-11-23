/* 
	Author: Matthew Ta
	Date: 4/7/2015
	Description: Library containing character classfication and manipulation functions
*/

// returns true if c is a digit and false otherwise 
int isCharDigit(int c);

// determines if c is a letter
int isCharLetter(int c);

// determines if c is a letter or a num
int isCharDigNum(int c);

// determines if c is a hexadecimal digit or char
int isCharHex(int c);

// determine if c is an upper case letter
int isCharUpper(int c);

// determines if c is a lower case letter
int isCharLower(int c);

// converts a char c to lowercase
int convertToLower(int c);

// converts a char c to uppercase
int convertToUpper(int c);

// returns true if c is a formatting character
int isCharFormat(int c);

// returns true if c is a control char
int isCharControl(int c);

// returns true if c is a punctuation char (i.e not digit, letter or space)
int isCharPunct(int c);

// returns true if c is a printing character (anything that can be displayed on the screen)
int isCharPrint(int c);

// returns true if c is a printing character other than space
int isCharPrint_space(int c);
