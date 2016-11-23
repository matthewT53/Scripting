/*
	Author: Matthew Ta
	Date: 5/7/2015
	Description: Funtions to handle strings
*/

// note the floating pointer number returned may be slightly inaccurate but should be ok for most purposes

// converts the string str into a double type
double stof(const char *str);

// converts the string str into an interger type
int stoi(const char *str);

// converts the string str into a long int
long stol(const char *str);

// converts the string str to double and also returns the string after the double value
double stofre(const char *str, char **remainderPtr);

// searches str for a number in a certain base and converts the number to a long
long stolre(const char *str, char **remainderPtr, unsigned int base);

// searches str for a number in a certain base and converts it to an unsigned long
unsigned long stoulre(const char *str, char **remainderPtr, unsigned int base);

/* 
	string copy and concatenation functions using array sub scripting
*/

/* array subscripting */
char *scpy(char *str1, const char *str2);

// copy a certain number of bytes from s2 into s1
char *sncpy(char *str1, const char *str2, const unsigned int bytes);

// join two strings
char *scat(char *str1, const char *str2);

// join a certain number of bytes from s2 to s1
char *sncat(char *str1, const char *str2, const unsigned int bytes);

/* Now using pointer arithmetic */

char *scpyPtr(char *str1, const char *str2);

// copy a certain number of bytes from s2 into s1
char *sncpyPtr(char *str1, const char *str2, const unsigned int bytes);

// join two strings
char *scatPtr(char *str1, const char *str2);

// join a certain number of bytes from s2 to s1
char *sncatPtr(char *str1, const char *str2, const unsigned int bytes);

/* string input and output functions */

// inputs a char
int inchr(void);

// outputs a char
int outchr(int c);

// outputs a string with a newline
int outstr(const char *str);

/* 
	string comparison functions 
	returns:
	0 if both strings are equal
	-1 if str1 is < str2
	1 if str1 > str2
*/

// using array sub scripting

// compares str1 with str2
int scmp(const char *str1, const char *str2);

// compares n bytes of str1 with str2
int sncmp(const char *str1, const char *str2, const unsigned int n);

// using pointer airthmetic
int scmpPtr(const char *str1, const char *str2);
	
int sncmpPtr(const char *str1, const char *str2, const unsigned int n);

/* string search functions */

// finds the first occurrence of a char c in a string str
char *cfstr(const char *str, const char c);

// finds the length of the initial segment of chars in s1 that is not in s2
unsigned int strsegnot(const char *str1, const char *str2);

// finds the length of the initial segment of chars in s1 that is in s2
unsigned int strsegin(const char *str1, const char *str2);

// locates the first occurence of any char from str2 in str1
char *strc(const char *str1, const char *str2);

// finds the last occurence of a char c in string str
char *clstr(const char *str, const char c);

// locates the first occurence of str2 in str1
char *strinstr(const char *str1, const char *str2);

// locates the last occurence of str2 in str1
char *strinstrl(const char *str1, const char *str2);

// locates the first occurence of str2 in str1 within maxBytes of str1
char *nstrinstr(const char *str1, const char *str2, const unsigned int maxBytes);

// locates the last occurence of str2 in str1 within maxBytes of str1
char *nstrinstrl(const char *str1, const char *str2, const unsigned int maxBytes);

// tokenizes the string str
char *strtokens(char *str, const char *delimiter);

// determines the length of the string by counting the number of characters excluding the NULL character, returns -1 if str is NULL
unsigned int slength(const char *str);

// using pointer arithmetic
unsigned int slengthPtr(const char *str);




