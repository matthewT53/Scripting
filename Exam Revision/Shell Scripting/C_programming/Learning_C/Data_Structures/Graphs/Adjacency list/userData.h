/*
	Name: Matthew Ta
	Date: 18/9/2015
	Description: Contains data structures that the user wants
*/

#define STR_SIZE 40

typedef struct _item *Item;

// user defined structure
typedef struct _item{
    char IpAddr[STR_SIZE];
    int deviceType;
} item;

