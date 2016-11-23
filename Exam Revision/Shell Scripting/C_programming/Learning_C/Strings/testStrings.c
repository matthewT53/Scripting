/*
	Author: Matthew Ta
	Date: 4/7/2015
	Description: this program tests the functions of the charset.h as well as myStrings.h files
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "charTypes.h"
#include "myStrings.h"
#include "memhandl.h"

#define TRUE 1
#define FALSE 0

#define MAX_LENGTH 100

void testCharTypes(void);
void testStringConversions(void);
void testInputOutput(void);
void testComparisons(void);
void testSearchFunctions(void);
void testMemHandling(void);

int main(void)
{
	// testCharTypes();
	// testStringConversions();
	// testInputOutput();
	// testComparisons();
	// testSearchFunctions();
	testMemHandling();
	return 0;
}

void testMemHandling(void)
{
	// tests for the memblkcpy() function
	printf("Testing the memblkcpy() function.\n");
	char testArray[MAX_LENGTH];
	char *testStr = "asfhjsabfsdjk";
	char *retPtr = NULL;
	memset(testArray, 0, MAX_LENGTH);
	retPtr = memblkcpy(testArray, testStr, strlen(testStr));
	assert(strcmp(retPtr, testStr) == 0);
	printf("Passed first test.\n"); 

	memset(testArray, 0, MAX_LENGTH);
	retPtr = memblkcpy(testArray, testStr, 3);
	assert(strncmp(retPtr, testStr, 3) == 0);
	printf("Passed second test.\n");

	memset(testArray, 0, MAX_LENGTH);
	testStr = "";
	retPtr = memblkcpy(testArray, testStr, 1);
	assert(strncmp(testArray, retPtr, 1) == 0);
	printf("Passed third test.\n");

	memset(testArray, 0, MAX_LENGTH);
	testStr = NULL;
	retPtr = memblkcpy(testArray, testStr, 5);
	assert(retPtr == NULL);
	printf("Passed fourth test.\n");

	memset(testArray, 0, MAX_LENGTH);
	memset(testArray, 'a', 5);
	testStr = "asjfks";
	retPtr = memblkcpy(testArray, testStr, 5);
	assert(strncmp(testArray, testStr, 5) == 0);
	memset(testArray, 0, MAX_LENGTH);
	printf("Passed fifth test.\n");
	
	printf("Passed all tests for memblkcpy().\n");

	// tests for the memblkmove() function
	printf("Testing the memblkmove() function.\n");
	char test[MAX_LENGTH];
	testStr = "kjsdvnksdkjsd";
	retPtr = NULL;
	memset(test, 0, MAX_LENGTH);
	retPtr = memblkcpy(test, testStr, strlen(testStr));
	assert(strcmp(retPtr, testStr) == 0);
	printf("Passed first test.\n"); 

	memset(test, 0, MAX_LENGTH);
	retPtr = memblkcpy(test, testStr, 3);
	assert(strncmp(retPtr, testStr, 3) == 0);
	printf("Passed second test.\n");

	memset(test, 0, MAX_LENGTH);
	testStr = "";
	retPtr = memblkcpy(test, testStr, 1);
	assert(strncmp(test, retPtr, 1) == 0);
	printf("Passed third test.\n");

	memset(test, 0, MAX_LENGTH);
	testStr = NULL;
	retPtr = memblkcpy(test, testStr, 5);
	assert(retPtr == NULL);
	printf("Passed fourth test.\n");

	memset(test, 0, MAX_LENGTH);
	memset(test, 'a', 5);
	testStr = "lknlxvlcxn";
	retPtr = memblkcpy(test, testStr, 5);
	assert(strncmp(test, testStr, 5) == 0);
	printf("Passed fifth test.\n");
	
	printf("Passed all tests for memblkmove().\n");
	
	// testing the memblkcmp() function
	printf("Testing the memblkcmp() function.\n");
	char *testStr1 = "wabba dabba flabba";
	char *testStr2 = "wabba dabba flabba";
	char testc;
	int value = 0;
	
	value = memblkcmp(testStr1, testStr2, 5);
	assert(value == 0);
	printf("Passed first test.\n");
	
	testStr1 = "hgythu";
	testStr2 = "fskfsd";
	value = memblkcmp(testStr1, testStr2, 5);
	assert(value == 1);
	printf("Passed second test.\n");

	value = memblkcmp(testStr2, testStr1, 5);
	assert(value == -1);
	printf("Passed third test.\n");

	testStr1 = "asfsdgdhsd";
	testStr2 = "";
	value = memblkcmp(testStr1, testStr2, 1);
	assert(value == 1);
	value = memblkcmp(testStr2, testStr1, 1);
	assert(value == -1);
	printf("Passed fourth test.\n");

	// should print an error message if one of the arguments is a pointer to null
	testStr1 = "fdgdf";
	testStr2 = NULL;
	value = memblkcmp(testStr1, testStr2, 5);
	assert(value == 0);
	value = memblkcmp(testStr2, testStr1, 5);
	assert(value == 0);
	printf("Passed fifth test.\n");

	// testing the memblkchr() function
	printf("Testing the memblkchr() function.\n");
	testStr1 = "fsdfsdgdh";
	testc = 'd';
	retPtr = memblkchr(testStr1, testc, 8);
	assert(retPtr != NULL && *retPtr == testc);
	printf("Passed first test.\n");

	testStr1 = "";
	testc = 'a';
	retPtr = memblkchr(testStr1, testc, 0);
	assert(retPtr == NULL);
	printf("Passed second test.\n");

	testStr1 = "sdgsekjglflsd";
	testc = 'e';
	retPtr = memblkchr(testStr1, testc, 9);
	assert(retPtr != NULL && *retPtr == testc);
	printf("Passed third test.\n");

	testStr1 = NULL;
	testc = 'g';
	retPtr = memblkchr(testStr1, testc, 5);
	assert(retPtr == NULL);
	printf("Passed fourth test.\n");

	testStr1 = "my name is jafasfs";
	testc = 'v';
	retPtr = memblkchr(testStr1, testc, 10);
	assert(retPtr == NULL);
	printf("Passed fifth test.\n");

	// tests for the memblkset() func
	printf("Testing the memblkset() function.\n");
	char testArray1[MAX_LENGTH];
	int i = 0;
	retPtr = memblkset(testArray1, 0, MAX_LENGTH);
	for (i = 0; i < MAX_LENGTH; i++){
		assert(*(retPtr + i) == 0);
	}
	
	printf("Passed first test.\n");

	retPtr = memblkset(testArray1, 'A', 0);
	for (i = 0; i < MAX_LENGTH; i++){
		assert(*(retPtr + i) == 0);
	}

	printf("Passed second test.\n");

	retPtr = memblkset(testArray1, 'B', MAX_LENGTH);
	for (i = 0; i < MAX_LENGTH; i++){
		assert(*(retPtr + i) == 'B');
	}

	printf("Passed third test.\n");
	
	// misc tests
	printf("Misc tests.\n");
	int array1[5] = {0};
	int array2[5] = {1, 2, 3, 4, 5};
	memblkcpy(array1, array2, 20);
	for (i = 0; i < 5; i++){
		assert(array1[i] == array2[i]);
	}

	printf("Passed first test.\n");

	char str[] = "Home Sweet Home";
	retPtr = memblkmove(str, &str[5], 10);
	assert(strcmp(retPtr, "Sweet Home Home") == 0);
	printf("Passed second test.\n");

	printf("Passed all misc tests.\n");

	printf("Passed all tests for memblkcpy(), memblkmove(), memblkcmp(), memblkchr() and memblkset().\n");
	printf("You are awesome!\n");
	
}

void testSearchFunctions(void)
{
	// testing the cfstr()
	printf("Testing the cfstr() function.\n");
	char *testStr = "hello world";
	char testc = 'h';
	char *retPtr = NULL;
	retPtr = cfstr(testStr, testc);
	assert(retPtr != NULL && *retPtr == 'h');
	printf("Passed first test.\n");

	testc = '\0';
	retPtr = NULL;
	retPtr = cfstr(testStr, testc);
	assert(retPtr != NULL && *retPtr == '\0');
	printf("Passed second test.\n");

	testStr = "";
	retPtr = NULL;
	testc = 0;
	retPtr = cfstr(testStr, testc);
	assert(retPtr != NULL && *retPtr == 0);
	printf("Passed third test.\n");

	testStr = "hello world";
	retPtr = NULL;
	testc = 'a';
	retPtr = cfstr(testStr, testc);
	assert(retPtr == NULL);
	printf("Passed fourth test.\n");
	
	printf("Passed all tests for cfstr().\n");

	// test strsegnot()
	printf("Testing the strsegnot() function.\n");
	char *testStr2 = "hello aworld";
	testStr = "hello world";
	unsigned int value = 0;
	value = strsegnot(testStr, testStr2);
	assert(value == 0);
	printf("Passed first test.\n");

	testStr = "";
	testStr2 = "";
	value = strsegnot(testStr, testStr2);
	assert(value == 0);
	printf("Passed second test.\n");

	testStr = "tyuhello world";
	testStr2 = "hello world";
	value = strsegnot(testStr, testStr2);
	assert(value == 3);
	printf("Passed third test.\n");
	
	testStr = "world hello";
	testStr2 = "hello world";
	value = strsegnot(testStr, testStr2);
	assert(value == 0);
	printf("Passed fourth test.\n");

	testStr = "fghy hello";
	testStr2 = "hjku";
	value = strsegnot(testStr, testStr2);
	assert(value == 2);
	printf("Passed fifth test.\n");

	testStr = "hello world";
	testStr2 = "hello world";
	value = strsegnot(testStr, testStr2);
	assert(value == 0);
	printf("Passed sixth test.\n");
	
	printf("Passed all tests for strsegnot().\n");

	// testing strsegin()
	printf("Testing the strsegin() function.\n");
	testStr = NULL;
	testStr2 = NULL;
	value = 0;
	
	testStr = "hello world";
	testStr2 = "hello world";
	value = strsegin(testStr, testStr2);
	assert(value == 11);
	printf("Passed first test.\n");

	testStr = "ghello world";
	testStr2 = "hello world";
	value = strsegin(testStr, testStr2);
	assert(value == 0);
	printf("Passed second test.\n");

	testStr = "hellojworld";
	testStr2 = "hello world";
	value = strsegin(testStr, testStr2);
	assert(value == 5);
	printf("Passed third test.\n");

	testStr = "hello sahfbajh";
	testStr2 = "";
	value = strsegin(testStr, testStr2);
	assert(value == 0);
	printf("Passed fourth test.\n");
	
	testStr = "";
	testStr2 = "dasnfaslkflnsaf";
	value = strsegin(testStr, testStr2);
	assert(value == 0);
	printf("Passed fifth test.\n");

	testStr = "haello world";
	testStr2 = "hvxcvbxc";
	value = strsegin(testStr, testStr2);
	assert(value == 1);
	printf("Passed sixth test.\n");

	printf("Passed all tests for strsegin().\n");

	// testing the strc() function
	printf("Testing the strc() function.\n");
	testStr = "hello world";
	testStr2 = "hello world";
	retPtr = NULL;
	retPtr = strc(testStr, testStr2);
	assert(retPtr != NULL && *retPtr == 'h');
	printf("Passed first test.\n");
	
	testStr = "kafaslkf fsdmflskf";
	testStr2 = "safoasfd";
	retPtr = NULL;
	retPtr = strc(testStr, testStr2);
	assert(retPtr != NULL && *retPtr == 'a');
	printf("Passed second test.\n");
		
	testStr = "asfkjsafk fsndkksd";
	testStr2 = "opopopoppo b";
	retPtr = NULL;
	retPtr = strc(testStr, testStr2);
	assert(retPtr != NULL && *retPtr == ' ');
	printf("Passed third test.\n");

	testStr = "";
	testStr2 = "dasdfsd";
	retPtr = strc(testStr, testStr2);
	assert(retPtr == NULL);
	printf("Passed fourth test.\n");

	testStr = "sdgsdg";
	testStr2 = "";
	retPtr = strc(testStr, testStr2);
	assert(retPtr == NULL);
	printf("Passed fifth test.\n");

	testStr = "hello world";
	testStr2 = "acmvnxnmc";
	retPtr = strc(testStr, testStr2);
	assert(retPtr == NULL);
	printf("Passed sixth test.\n");

	printf("Passed all tests for strc().\n");

	// testing for clstr()
	testStr = "hello world";
	testc = 'd';
	retPtr = clstr(testStr, testc);
	assert(retPtr != NULL && *retPtr == 'd');
	printf("Passed first test.\n");

	testStr = "";
	testc = 'a';
	retPtr = clstr(testStr, testc);
	assert(retPtr == NULL);
	printf("Passed second test.\n");
	
	testStr = "hello world";
	testc = 'a';
	retPtr = clstr(testStr, testc);
	assert(retPtr == NULL);
	printf("Passed third test.\n");

	printf("Passed all tests for clstr().\n");

	// testing for strinstr()
	printf("Testing the strinstr() function.\n");
	testStr = "hello world";
	testStr2 = "hello";
	retPtr = NULL;
	retPtr = strinstr(testStr, testStr2);
	assert(retPtr != NULL && *retPtr == 'h');
	printf("Passed first test.\n");

	testStr = "dsfnsd ldksankllsa fsdllkds";
	testStr2 = "fsdllk";
	retPtr = strinstr(testStr, testStr2);
	assert(retPtr != NULL && *retPtr == 'f');	
	printf("Passed second test.\n");

	testStr = "";
	testStr2 = "hello friends";
	retPtr = strinstr(testStr, testStr2);
	assert(retPtr == NULL);
	printf("Passed third test.\n");

	testStr = "dasfkjasfksd";
	testStr2 = "";
	retPtr = strinstr(testStr, testStr2);
	assert(retPtr != NULL && *retPtr == 'd');
	printf("Passed fourth test.\n");

	testStr = "hello friends wabfla";
	testStr2 = "hello friends wabfla";
	retPtr = strinstr(testStr, testStr2);
	assert(retPtr != NULL && *retPtr == 'h');
	printf("Passed fifth test.\n");

	printf("Passed all tests for strinstr().\n");
	
	// tests for strtokens()
	printf("Testing the strtokens() function.\n");
	char string[MAX_LENGTH] = "hello world my name is billy bob";
	testStr2 = " ";
	retPtr = NULL;
	retPtr = strtokens(string, testStr2);
	assert(retPtr != NULL && *retPtr == 'h');
	retPtr = strtokens(NULL, testStr2);
	assert(retPtr != NULL && *retPtr == 'w');
	retPtr = strtokens(NULL, testStr2);
	assert(retPtr != NULL && *retPtr == 'm');
	retPtr = strtokens(NULL, testStr2);
	assert(retPtr != NULL && *retPtr == 'n');
	retPtr = strtokens(NULL, testStr2);
	assert(retPtr != NULL && *retPtr == 'i');
	retPtr = strtokens(NULL, testStr2);
	assert(retPtr != NULL && *retPtr == 'b');
	retPtr = strtokens(NULL, testStr2);
	assert(retPtr != NULL && *retPtr == 'b');
	printf("Starting last test.\n");
	retPtr = strtokens(NULL, testStr2);
	assert(retPtr == NULL);
	printf("Passed the first test.\n");	

	char string1[MAX_LENGTH] = "this program is good";
	retPtr = NULL;
	retPtr = strtokens(string1, "");
	assert(*retPtr == 't');
	retPtr = strtokens(NULL, "");
	assert(retPtr == NULL);
	printf("Passed second test.\n");

	char string2[MAX_LENGTH] = "";
	retPtr = NULL;
	retPtr = strtokens(string2, " ");
	assert(retPtr == NULL);
	printf("Passed third test.\n");
	printf("Passed all tests for strtokens().\n");

	// tests for slength()
	printf("Testing the slength() and slengthPtr() functions.\n");
	testStr = "ads dsaf fsd";
	unsigned int length = slength(testStr);
	assert(length == 12);
	length = slengthPtr(testStr);
	assert(length == 12);
	printf("Passed first test.\n");

	testStr = "";
	length = slength(testStr);
	assert(length == 0);
	length = slengthPtr(testStr);
	assert(length == 0);
	printf("Passed second test.\n");

	testStr = NULL;
	length = slength(testStr);
	assert(length == -1);
	length = slengthPtr(testStr);
	assert(length == -1);
	printf("Passed third test.\n");
	
	printf("Passed all tests for slength() and slengthPtr().\n");

	printf("Passed all tests for the string search functions.\n");
}

void testComparisons(void)
{
	char *s1 = "hello world";
	char *s2 = "hello world";

	printf("Testing two equal strings.\n");
	assert(scmp(s1, s2) == 0);
	assert(sncmp(s1, s2, 5) == 0);
	assert(scmpPtr(s1, s2) == 0);
	assert(sncmpPtr(s1, s2, 8) == 0);
	printf("Passed first test.\n");

	printf("Testing when s1 is > s2.\n");
	s1 = "hello world";
	s2 = "hello aorld";
	assert(scmp(s1, s2) > 0);
	assert(sncmp(s1, s2, 8) > 0);
	assert(scmpPtr(s1, s2) > 0);
	assert(sncmpPtr(s1, s2, 8) > 0);
	printf("Passed second test.\n");
	
	printf("Testing when s1 is < s2.\n");
	s1 = "hello aorld";
	s2 = "hello world";
	assert(scmp(s1, s2) < 0);
	assert(sncmp(s1, s2, 8) < 0);
	assert(scmpPtr(s1, s2) < 0);
	assert(sncmpPtr(s1, s2, 8) < 0);
	printf("Passed third test.\n");

	printf("Testing when second arg is empty.\n");
	s1 = "hello world";
	s2 = "";
	assert(scmp(s1, s2) > 0);
	assert(sncmp(s1, s2, 5) > 0);
	assert(scmpPtr(s1, s2) > 0);
	assert(sncmpPtr(s1, s2, 6) > 0);
	printf("Passed fourth test.\n");
	
	printf("Testing when 1st arg is empty.\n");
	s1 = "";
	s2 = "hello world";
	assert(scmp(s1, s2) < 0);
	assert(sncmp(s1, s2, 2) < 0);
	assert(scmpPtr(s1, s2) < 0);
	assert(sncmpPtr(s1, s2, 3) < 0);
	printf("Passed fifth test.\n");

	printf("Testing when both args are empty.\n");
	s1 = "";
	s2 = "";
	assert(scmp(s1, s2) == 0);
	assert(sncmp(s1, s2, 1) == 0);
	assert(scmpPtr(s1, s2) == 0);
	assert(sncmpPtr(s1, s2, 2) == 0);
	printf("Passed sixth test.\n");

	printf("Misc tests.\n");
	s1 = "Happy New Year";
	s2 = "Happy Holidays";
	assert(scmp(s1, s2) > 0);
	assert(scmp(s2, s1) < 0);
	assert(sncmp(s1, s2, 5) == 0);
	assert(sncmp(s1, s2, 6) == 0);
	assert(sncmp(s2, s1, 6) == 0);
	assert(scmpPtr(s1, s2) > 0);
	assert(sncmpPtr(s1, s2, 8) > 0);
	assert(sncmpPtr(s1, s2, 7) > 0);
	assert(sncmpPtr(s2, s1, 7) < 0);
	assert(sncmp(s1, s2, 7) > 0);
	assert(sncmp(s2, s1, 7) < 0);
	printf("Passed misc tests.\n");

	printf("Passed all tests for scmp(), sncmp(), scmpPtr() and sncmpPtr().\n");
}

void testInputOutput(void)
{
	// testing the inchr() function
	char c;
	int retValue = 0;
	printf("Test me with char, string then nothing.\n");
	c = inchr();
	outchr(c);
	// testing the outstr() function
	outchr('\n');
	printf("Testing the outstr() function.\n");
	char *string = "hello world";
	retValue = outstr(string);
	assert(retValue != EOF);
	string = "a";
	retValue = outstr(string);
	assert(retValue != EOF);
	string = "";
	retValue = outstr(string);
	assert(retValue != EOF);
	string = NULL;
	retValue = outstr(string);
	assert(retValue == EOF);
}

void testStringConversions(void)
{
	double value = 0;
	
	// test the stof() function
	char *strings[8] = {"5.67 hello", "8.65", "-100.56", "asdj dasd", "-0.01", "5asd6.7", "5293857.3453008", ""};
	printf("Testing the stof() function.\n");
	value = stof(strings[0]);
	assert(value == 5.67);
	
	value = stof(strings[1]);
	assert(value == 8.65);

	value = stof(strings[2]);
	assert(value == -100.56);
	
	value = stof(strings[3]);
	assert(value == 0);

	value = stof(strings[4]);
	assert(value == -0.01);

	value = stof(strings[5]);
	assert(value == 5);

	value = stof(strings[6]);
	assert(value == 5293857.3453008);

	value = stof(strings[7]);
	assert(value == 0);

	printf("Passed all tests for stof().\n");

	// test the stoi() function
	char *strings1[4] = {"56 hello", "-90", "56.78", ""};
	int value1 = 0;
	
	value1 = stoi(strings1[0]);
	assert(value1 == 56);

	value1 = stoi(strings1[1]);
	assert(value1 == -90);

	value1 = stoi(strings1[2]);
	assert(value1 == 56);

	value1 = stoi(strings[3]);
	assert(value1 == 0);
		
	printf("Passed all tests for stoi().\n");

	// tests for the stol() function
	int value2 = 0;
	char *strings2[5] = {"45 dasd", "-100.54sdf", "", "100.0", "-5.6"};
	printf("Testing the strl() function.\n");
	value2 = stol(strings2[0]);
	assert(value2 == 45);

	value2 = stol(strings2[1]);
	assert(value2 == -100);

	value2 = stol(strings2[2]);
	assert(value2 == 0);
	
	value2 = stol(strings2[3]);
	assert(value2 == 100);
	
	value2 = stol(strings2[4]);
	assert(value2 == -5);

	printf("Passed all tests for stol().\n");

	// tests for the stofre() function
	printf("Testing the stofre() function.\n");
	double value3 = 0;
	char *strings3[5] = {"55.67989 dasfsdgfgdfgs", "", "5fsdf", "-654.765", "-65-.das"};
	char *strPtr = NULL;
	value3 = stofre(strings3[0], &strPtr);
	assert(value3 == 55.67989);
	printf("(DEBUG) strPtr = %s\n", strPtr); 

	value3 = stofre(strings3[1], &strPtr);
	assert(value3 == 0);
	printf("(DEBUG) strPtr = %s\n", strPtr); 

	value3 = stofre(strings3[2], &strPtr);
	assert(value3 == 5);
	printf("(DEBUG) strPtr = %s\n", strPtr);

	value3 = stofre(strings3[3], &strPtr);
	printf("(DEBUG) strPtr = %s\n", strPtr); 
	assert(value3 == -654.765 && strPtr == NULL);
	
	value3 = stofre(strings3[4], &strPtr);	
	assert(value3 == -65);
	printf("(DEBUG) strPtr = %s\n", strPtr);;

	printf("Passed all tests for stofre().\n");

	// test the stolre() function
	printf("Testing the stolre() function.\n");
	long value4 = 0;
	char *strings4[5] = {"10010101 asdasd", "dasd 100012", "", "78deade fsdvxcbdfbs", "100536 dasd"};
	char *endPtr = NULL;
	
	value4 = stolre(strings4[0], &endPtr, 2); 
	printf("endPtr: %s\n", endPtr);
	assert(value4 == 149);

	value4 = stolre(strings4[1], &endPtr, 2);
	assert(value4 == 0);

	value4 = stolre(strings4[2], &endPtr, 2);
	assert(value4 == 0 && endPtr == NULL);

	value4 = stolre(strings4[3], &endPtr, 16);
	printf("value4 = %ld, endPtr: %s\n", value4, endPtr);
	assert(value4 == 126741214);

	value4 = stolre(strings4[4], &endPtr, 0);
	printf("endPtr: %s\n", endPtr);
	assert(value4 == 100536);

	printf("Passed all tests for stolre().\n");

	// tests for stoulre()
	printf("Testing the stoulre() function.\n");
	unsigned long value5 = 0;
	char *strings5[5] = {"", "-564 dasdfgd", "101011xcvxcv", "ADBC6ssdnsdnn", "56.67dasd"};
	char *endPtr1 = NULL;

	value5 = stoulre(strings5[0], &endPtr1, 0);
	printf("endPtr: %s.\n", endPtr1);
	assert(value5 == 0);

	value5 = stoulre(strings5[1], &endPtr1, 10);
	printf("endPtr: %s.\n", endPtr1);
	assert(value5 == -564);
	
	value5 = stoulre(strings5[2], &endPtr1, 2);
	printf("endPtr: %s.\n", endPtr1);
	assert(value5 == 43);

	value5 = stoulre(strings5[3], &endPtr1, 16);
	printf("endPtr: %s.\n", endPtr1);
	assert(value5 == 711622);

	value5 = stoulre(strings5[4], &endPtr1, 10);
	printf("endPtr: %s.\n", endPtr1);
	assert(value5 == 56);

	printf("Passed all tests for stoulre().\n");

	// tests for the scpy() and scpyPtr() functions
	printf("Testing the scpy() and scpyPtr() functions.\n");
	char *retStr = NULL;
	char *testStr = "hello world";
	char array[MAX_LENGTH];

	// testing with a sentence
	retStr = scpy(array, testStr);
	assert(strcmp(retStr, testStr) == 0 && strcmp(array, testStr) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = scpyPtr(array, testStr);
	assert(strcmp(retStr, testStr) == 0 && strcmp(array, testStr) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = sncpy(array, testStr, 10);
	assert(strncmp(retStr, testStr, 10) == 0 && strncmp(array, testStr, 10) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = sncpyPtr(array, testStr, 10);
	assert(strncmp(retStr, testStr, 10) == 0 && strncmp(array, testStr, 10) == 0);
	printf("Passed first test.\n");
	
	// testing with one letter
	retStr = NULL;
	testStr = "a";
	memset(array, 0, MAX_LENGTH);
	retStr = scpy(array, testStr);
	assert(strcmp(retStr, array) == 0 && strcmp(testStr, array) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = scpyPtr(array, testStr);
	assert(strcmp(retStr, array) == 0 && strcmp(testStr, array) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = sncpy(array, testStr, 1);
	assert(strncmp(array, testStr, 1) == 0 && strncmp(array, retStr, 1) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = sncpyPtr(array, testStr, 1);
	assert(strncmp(array, testStr, 1) == 0 && strncmp(array, retStr, 1) == 0);
	memset(array, 0, MAX_LENGTH);
	printf("Passed second test.\n");

	// testing with empty string
	retStr = NULL;
	testStr = "";
	retStr = scpy(array, testStr);
	assert(strcmp(retStr, array) == 0 && strcmp(array, testStr) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = scpyPtr(array, testStr);
	assert(strcmp(retStr, array) == 0 && strcmp(array, testStr) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = sncpy(array, testStr, 1);
	assert(strcmp(retStr, array) == 0 && strcmp(array, testStr) == 0);
	memset(array, 0, MAX_LENGTH);
	retStr = sncpyPtr(array, testStr, 1);
	assert(strcmp(retStr, array) == 0 && strcmp(array, testStr) == 0);
	memset(array, 0, MAX_LENGTH);
	printf("Passed third test.\n");

	printf("Passed all tests for scpy(), sncpy(), scpyPtr(), sncpyPtr().\n");

	// testing the concatenation functions
	printf("Testing scat(), sncat(), scatPtr(), sncatPtr().\n");
	char *retStr1 = NULL;
	char *testStr1 = " hello world";
	char array1[MAX_LENGTH] = "yo";
	
	// testing with a string
	printf("Didnt go wrong here.\n");
	retStr1 = scat(array1, testStr1);
	printf("Result string is: %s <end>.\n", retStr1); 
	assert(strcmp(retStr1, "yo hello world") == 0 && strcmp(array1, "yo hello world") == 0);
	memset(array1, 0, MAX_LENGTH);
	strcpy(array1, "yp");
	printf("Didnt go wrong here1.\n");
	retStr1 = sncat(array1, testStr1, 10);
	printf("Result string is: %s <end>.\n", retStr1); 
	assert(strncmp(retStr1, "yp hello world", 10) == 0 && strncmp(array1, "yp hello world", 10) == 0);
	memset(array1, 0, MAX_LENGTH);
	strcpy(array1, "yo");
	printf("Didnt go wrong here2.\n");
	retStr1 = scatPtr(array1, testStr1);
	assert(strcmp(retStr1, "yo hello world") == 0 && strcmp(array1, "yo hello world") == 0);
	memset(array1, 0, MAX_LENGTH);
	strcpy(array1, "yw");
	printf("Didnt go wrong here3.\n");
	retStr1 = sncatPtr(array1, testStr1, 8);
	assert(strncmp(retStr1, "yw hello world", 8) == 0 && strncmp(array1, "yw hello world", 8) == 0);
	memset(array1, 0, MAX_LENGTH);
	printf("Passed first test.\n");

	// testing with one of the arguments as an empty string
	testStr1 = "hello world";
	retStr1 = scat(array1, testStr1);
	assert(strcmp(retStr1, "hello world") == 0 && strcmp(array1, "hello world") == 0);
	memset(array1, 0, MAX_LENGTH);
	testStr1 = "hallah bullah";
	retStr1 = sncat(array1, testStr1, 10);
	assert(strncmp(retStr1, "hallah bullah", 10) == 0 && strncmp(array1, "hallah bullah", 10) == 0);
	memset(array1, 0, MAX_LENGTH);
	testStr1 = "hoooray habba";
	retStr1 = scatPtr(array1, testStr1);
	assert(strcmp(retStr1, "hoooray habba") == 0 && strcmp(array1, "hoooray habba") == 0);
	memset(array1, 0, MAX_LENGTH);
	testStr1 = "happy hoodies";
	retStr1 = sncatPtr(array1, testStr1, 8);
	assert(strncmp(retStr1, "happy hoodies", 8) == 0 && strncmp(array1, "happy hoodies", 8) == 0);
	memset(array1, 0, MAX_LENGTH);
	printf("Passed second test.\n");

	// testing with the second argument empty
	testStr1 = "";
	strcpy(array1, "hello world");
	retStr1 = scat(array1, testStr1);
	assert(strcmp(retStr1, "hello world") == 0 && strcmp(array1, "hello world") == 0);
	memset(array1, 0, MAX_LENGTH);
	strcpy(array1, "yp ");
	retStr1 = sncat(array1, testStr1, 10);
	assert(strncmp(retStr1, "yp ", 10) == 0 && strncmp(array1, "yp ", 10) == 0);
	memset(array1, 0, MAX_LENGTH);
	strcpy(array1, "yo ");
	retStr1 = scatPtr(array1, testStr1);
	assert(strcmp(retStr1, "yo ") == 0 && strcmp(array1, "yo ") == 0);
	memset(array1, 0, MAX_LENGTH);
	strcpy(array1, "yw ");
	retStr1 = sncatPtr(array1, testStr1, 8);
	assert(strncmp(retStr1, "yw ", 8) == 0 && strncmp(array1, "yw ", 8) == 0);
	memset(array1, 0, MAX_LENGTH);
	printf("Passed third test.\n");

	// testing with both strings empty
	testStr1 = "";
	retStr1 = scat(array1, testStr1);
	assert(strcmp(retStr1, "") == 0 && strcmp(array1, "") == 0);
	retStr1 = sncat(array1, testStr1, 10);
	assert(strncmp(retStr1, "", 10) == 0 && strncmp(testStr1, "", 10) == 0);
	retStr1 = scatPtr(array1, testStr1);
	assert(strcmp(retStr1, "") == 0 && strcmp(testStr1, "") == 0);
	retStr1 = sncatPtr(array1, testStr1, 8);
	assert(strncmp(retStr1, "", 8) == 0 && strncmp(testStr1, "", 8) == 0);
	printf("Passed the fourth test.\n");

	// misc tests
	testStr1 = " ";
	strcpy(array1, "");
	retStr1 = scatPtr(array1, testStr1);
	printf("retStr1: %s\n", retStr1);
	assert(strcmp(retStr1, " ") == 0);

	printf("Passed the misc test.\n");
	printf("Passed all tests for scat(), sncat(), scatPtr() and sncatPtr().\n");

	printf("Passed all tests! You are awesome!\n");
}

void testCharTypes(void)
{
	// test the equivalent of isdigit()
	int test = 0;
	char c[5] = {'a', 'B', '5', '9', '?'};
	printf("Testing the isCharDigit() function.\n");
	test = isCharDigit(c[0]);
	assert(test == FALSE);
	
	test = isCharDigit(c[1]);
	assert(test == FALSE);
	
	test = isCharDigit(c[2]);	
	assert(test == TRUE);
	
	test = isCharDigit(c[3]);
	assert(test == TRUE);

	test = isCharDigit(c[4]);
	assert(test == FALSE);

	printf("Passed all tests for isCharDigit().\n");

	// test the equivalent of isalpha()
	int test1 = 0;
	char c1[5] = {'b', 'h', '/', 'M', '>'};
	printf("Testing the isCharLetter() function.\n");
	test1 = isCharLetter(c1[0]);
	assert(test1 == TRUE);
	
	test1 = isCharLetter(c1[1]);
	assert(test1 == TRUE);
	
	test1 = isCharLetter(c1[2]);
	assert(test1 == FALSE);

	test1 = isCharLetter(c1[3]);
	assert(test1 == TRUE);
	
	test1 = isCharLetter(c1[4]);
	assert(test1 == FALSE);

	printf("Passed all tests for isCharLetter().\n");

	// test for isCharDigNum()
	int test2 = 0;
	char c2[5] = {'a', 'B', '5', ';', '['};
	printf("Testing isCharDigNum() function.\n");
	test2 = isCharDigNum(c2[0]);
	assert(test2 == TRUE);

	test2 = isCharDigNum(c2[1]);
	assert(test2 == TRUE);

	test2 = isCharDigNum(c2[2]);
	assert(test2 == TRUE);
	
	test2 = isCharDigNum(c2[3]);
	assert(test2 == FALSE);

	test2 = isCharDigNum(c2[4]);
	assert(test2 == FALSE);

	printf("Passed all tests for isCharDigNum().\n");

	// tests for isCharHex()
	int test3 = 0;
	char c3[8] = {'e', 'R', 'a', '5', '9', '/', 'B', 'f'};
	printf("Testing isCharHex() function.\n");
	test3 = isCharHex(c3[0]);
	assert(test3 == TRUE);
	
	test3 = isCharHex(c3[1]);
	assert(test3 == FALSE);
	
	test3 = isCharHex(c3[2]);
	assert(test3 == TRUE);

	test3 = isCharHex(c3[3]);
	assert(test3 == TRUE);

	test3 = isCharHex(c3[4]);
	assert(test3 == TRUE);

	test3 = isCharHex(c3[5]);
	assert(test3 == FALSE);

	test3 = isCharHex(c3[6]);
	assert(test3 == TRUE);
	
	test3 = isCharHex(c3[7]);
	assert(test3 == TRUE);

	printf("Passed all tests for isCharHex().\n");

	// testing for isCharUpper()
	int test4 = 0;
	char c4[5] = {'e', 'E', 'F', ';', '9'};
	printf("Testing isCharUpper().\n");
	test4 = isCharUpper(c4[0]);
	assert(test4 == FALSE);

	test4 = isCharUpper(c4[1]);
	assert(test4 == TRUE);

	test4 = isCharUpper(c4[2]);
	assert(test4 == TRUE);

	test4 = isCharUpper(c4[3]);
	assert(test4 == FALSE);
	
	test4 = isCharUpper(c4[4]);
	assert(test4 == FALSE);

	printf("Passed all tests for isCharUpper().\n");

	// testing for isCharLower()
	int test5 = 0;
	char c5[5] = {'e', 'E', 'g', '&', '#'};
	printf("Testing isCharLower().\n");
	test5 = isCharLower(c5[0]);
	assert(test5 == TRUE);

	test5 = isCharLower(c5[1]);
	assert(test5 == FALSE);

	test5 = isCharLower(c5[2]);
	assert(test5 == TRUE);

	test5 = isCharLower(c5[3]);
	assert(test5 == FALSE);
	
	test5 = isCharLower(c5[4]);
	assert(test5 == FALSE);

	printf("Passed all tests for isCharLower().\n");

	// tests for convertToUpper()
	int test6 = 0;
	char c6[5] = {'a', 'H', '5', ']', ';'};
	printf("Testing convertToUpper().\n");
	test6 = convertToUpper(c6[0]);
	assert(test6 == 'A');

	test6 = convertToUpper(c6[1]);
	assert(test6 == 'H');
	
	test6 = convertToUpper(c6[2]);
	assert(test6 == '5');

	test6 = convertToUpper(c6[3]);
	assert(test6 == ']');
	
	test6 = convertToUpper(c6[4]);
	assert(test6 == ';');

	printf("Passed all tests for convertToUpper().\n");

	// tests for convertToLower()
	int test7 = 0;
	char c7[5] = {'H', 'L', 'a', '[', '^'};
	printf("Testing convertToLower().\n");
	test7 = convertToLower(c7[0]);
	assert(test7 == 'h');
	
	test7 = convertToLower(c7[1]);
	assert(test7 == 'l');

	test7 = convertToLower(c7[2]);
	assert(test7 == 'a');

	test7 = convertToLower(c7[3]);
	assert(test7 == '[');

	test7 = convertToLower(c7[4]);
	assert(test7 == '^');

	printf("Passed all tests for convertToLower().\n");
	
	// tests for isCharFormat()
	int test8 = 0;
	char c8[5] = {'\n', '\0', 'n', '\r', 'L'};
	printf("Testing isCharFormat().\n");

	test8 = isCharFormat(c8[0]);
	assert(test8 == TRUE);

	test8 = isCharFormat(c8[1]);
	assert(test8 == FALSE);

	test8 = isCharFormat(c8[2]);
	assert(test8 == FALSE);
	
	test8 = isCharFormat(c8[3]);
	assert(test8 == TRUE);
	
	test8 = isCharFormat(c8[4]);
	assert(test8 == FALSE);

	printf("Passed all tests for isCharFormat().\n");

	// tests for isCharControl() function
	int test9 = FALSE;
	char c9[5] = {'\n', '\r', '\\', 'a', ';'};
	printf("Testing isCharControl().\n");
	test9 = isCharControl(c9[0]);
	assert(test9 == TRUE);

	test9 = isCharControl(c9[1]);
	assert(test9 == TRUE);

	test9 = isCharControl(c9[2]);
	assert(test9 == TRUE);

	test9 = isCharControl(c9[3]);
	assert(test9 == FALSE);

	test9 = isCharControl(c9[4]);
	assert(test9 == FALSE);

	printf("Passed all tests for isCharControl().\n");
	
	// tests for isCharPunct()
	int test10 = FALSE;
	char c10[5] = {'#', '\n', '\r', '*', 'a'};
	printf("Testing isCharPunct().\n");
	
	test10 = isCharPunct(c10[0]);
	assert(test10 == TRUE);

	test10 = isCharPunct(c10[1]);
	assert(test10 == FALSE);

	test10 = isCharPunct(c10[2]);
	assert(test10 == FALSE);

	test10 = isCharPunct(c10[3]);
	assert(test10 == TRUE);
	
	test10 = isCharPunct(c10[4]);
	assert(test10 == FALSE);

	printf("Passed all tests for isCharPunct().\n");

	// tests for isCharPrint()
	int test11 = FALSE;
	char c11[6] = {'^', '\n', '5', 'a', 'v', ' '};
	printf("Testing isCharPrint().\n");
	
	test11 = isCharPrint(c11[0]);
	assert(test11 == TRUE);
		
	test11 = isCharPrint(c11[1]);
	assert(test11 == FALSE);
	
	test11 = isCharPrint(c11[2]);
	assert(test11 == TRUE);

	test11 = isCharPrint(c11[3]);
	assert(test11 == TRUE);

	test11 = isCharPrint(c11[4]);
	assert(test11 == TRUE);

	test11 = isCharPrint(c11[5]);
	assert(test11 == TRUE);

	printf("Passed all tests for isCharPrint().\n");

	// tests for isCharPrint_space()
	int test12 = FALSE;
	char c12[5] = {' ', 'a', 'B', '\n', '\v'};
	printf("Testing isCharPrint_space().\n");

	test12 = isCharPrint_space(c12[0]);
	assert(test12 == FALSE);

	test12 = isCharPrint_space(c12[1]);
	assert(test12 == TRUE);

	test12 = isCharPrint_space(c12[2]);
	assert(test12 == TRUE);

	test12 = isCharPrint_space(c12[3]);
	assert(test12 == FALSE);

	test12 = isCharPrint_space(c12[4]);
	assert(test12 == FALSE);

	printf("Passed all tests for isCharPrint_space().\n");

	printf("Passed all tests! You are phenomenal!\n");

}
