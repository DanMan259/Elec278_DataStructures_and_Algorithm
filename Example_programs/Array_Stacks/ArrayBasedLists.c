// ArrayLists.c
// This code is supplied for use with ELEC278.  It requires that the student
// add some missing pieces.

#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayList {
	// Structure describes collection of data to describe and contain
	// a set of numbers.  The set is described by end and size, and
	// the actual data is in an array pointed to by a.
	int		size;		// record size to detect if full
	int		end;		// records index of last location used
	int		*a;		// pointer to allocated array memory
} ArrayList;

#define EMPTY	(-1)	// invalid array index used as end when empty

void init (ArrayList *list,int size)
// Initialize an ArrayList to hold an array of specified size.
{
	list->a = malloc(sizeof(int)*size);
	list->size = size;
	list->end = EMPTY;
}


void addFront(ArrayList* list,int x)
// Add value in parameter x to front of list.  If list already full,
// don't do anything
{
/* Write your code here */
	if (list->end == (list->size - 1)){
		printf("list full");
		return;
	}

	for (int i= list->end; i>=0; i--)
		list->a[i+1]=list->a[i];
	
	list->a[0]=x;
	list->end++;
	printf("adding %d to front of the list \n", x);
}



void addEnd(ArrayList* list,int x)
// Add value in parameter x to rear of list
{
	// end holds index of current last value in list.
	// Add 1 to list and store value in new end location.
	// Note this works even if list initially empty. Note also
	// that we check if array already full.  (Remember, size is
	// 1 greater than last valid index, so size needs to be greater
	// than what end index will become
	if (list->size > (list->end+1))	{
    		list->end++;
    		list->a[list->end] = x;
		printf("added %d to end of the list\n", x);
	}
}


void removeEnd(ArrayList* list)
// Remove last value from list. In a more elaborate implementation,
// end value may be provided to the calling code. At the very least,
// code should indicate whether it actually did what was asked.
{
	printf ("Remove last value from list\n");
	if(list->end != EMPTY)	{
		// list not empty, so it is possible to remove last value
		list->end--;			// may empty list
	} else {
		printf("List is empty");
	}
}


void removeFront(ArrayList* list)
// Remove front value from list. Note that you will have to move all values
{
    /* Write your code here */
	if (list->end != (list->size-1) && list->end !=EMPTY)
	{
		for (int  i=0; i<=list->end; i++)
			list->a[i]=list->a[i+1];
	
		list->end--;
		printf("Removing first element from list \n");
	}
}


void print(ArrayList *list)
// Print contents of list
{
	// Print brackets around whole list
	printf ("(");
	// Check first to see if anything to print
	if (list->end == EMPTY)	{
        	printf("EMPTY LIST");
	} else {
		int i;
		for( i=0; i<=list->end-1; i++) {
			printf("%d - ",list->a[i]);
		}
		// No trailing dash after last one
		printf("%d",list->a[list->end]);
	}
	//finish with closing bracket and NL
	printf (")\n");
}


void main (){
	ArrayList ll;

	printf ("ELEC278 - Lab2 Part1 arrayslist program\n");
	init(&ll,10);
	addFront(&ll,5);
	addFront(&ll,2);
	addEnd(&ll,4);
	addEnd(&ll,3);
	print(&ll);
	printf("\n");	

  	removeFront(&ll);
	print(&ll);
	printf("\n");

	removeEnd(&ll);
	print(&ll);
	printf("\n");
    	
	removeFront(&ll);
    	print(&ll);
	printf("\n");
    	
	removeFront(&ll);
    	print(&ll);
	printf("\n");
    	
	removeFront(&ll);
	addFront(&ll,10);
	print(&ll);
}

