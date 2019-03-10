// MYSTRING.C
// Code provided for ELEC278 Lab 1 Step 4
// See the instructions in the lab sheet for details about
// the code you are to add to the functions shown below.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myString.h"


char *copyString(char *s){
	char *p = calloc(strlen(s), sizeof (char));
	int i;
	for (i=0;i<(strlen(s)+1);i++){	
		p[i] = s[i];
	}
	return 	p;
	
}//copyString()


void printString(char *s)
{
	printf ("%s\n",s);
}//printString()
