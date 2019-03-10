// HASH.C
// Program for use with ELEC278 Lab 5 Part 2.
//
// History:
// 161106	HF	First release
// 171102	DA	Minor tweaks


#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"
#include <time.h>
#include <math.h>

#define MAX_WORD_SIZE 50

typedef struct HashTable {
	LinkedList** a;
	int size;
	int collisions;
} HashTable;


HashTable* initHashTable(int s)
{
	HashTable* h = malloc(sizeof(HashTable));
	int		i;
	h->size = s;
	h->a = malloc(sizeof(LinkedList) * s);
	for(i=0;i<s;i++)
		h->a[i]= init();
	h->collisions = 0;
	return h;
}//initHashTable()


long h(char* x)
// This function computes a hash code for a given string.  Note that hash
// code is unbounded - it needs to be reduced modulo the size of the array
// used to store the data. (You will see another function hash() below that
// completes the index calculation.)
{
	long sum = 0;
	int len = 0;
	while (*(x + len++) != '\0');
	
	for (int i = 0; i < len; i++) {
		char t = *(x + i);
		sum += ((int)(t)) * pow(31, len - 1 - i);
	}
	
	return sum;
}//h()


double loadFactor(HashTable* ht)
{
	double nonempty = 0;
	int i;
	// count number of non-empty hash table slots
	for(i=0; i<ht->size; i++)	{
		if (isEmpty(ht->a[i])==0)	nonempty++;
		}
	return nonempty/ht->size*100;
}//loadFactor()


int hash(char* x, int size)
// Index calculation. Function h() computes general hash for the string;
// this function turns the hash into a valid index, given the size of the
// array.
{
	return h(x) % size;
}


void insert(HashTable* ht, char* x)
{
    // ---<SNIP>---

    if (loadFactor(ht)>60) {
        // new hash table
        HashTable* newHashTable = initHashTable(ht->size*2);
        // iterate through array
        for (int i=0;i<ht->size;++i) {
            // iterate through linked list
            LinkedList* ll = ht->a[i];
            Node* curr = ll->head;
            while (curr!=NULL) {
                insert(newHashTable,curr->value); // yeet
                Node* Scum = curr;
                curr = curr->next;
                free(Scum);
            }
        }
        // the linked lists
        for (int i=0;i<ht->size;++i) { 
            free(ht->a[i]);
        }
        // the struct
        free(ht);
        // copy stuff back into old table
        ht->size = newHashTable->size;
        ht->a = newHashTable->a;
        ht->collisions = newHashTable->collisions;
    }

    int xhash = hash(x,ht->size);
    LinkedList* ll = ht->a[xhash];
    if (!isEmpty(ll)) {
        ++ht->collisions;
    }
    addFront(ll,x);

    // ---<SNIP>---
}//insert()

int findInTable(HashTable *ht, char* x)
{
	int index = hash(x, ht->size);
	LinkedList *cur = *(ht->a + index);
	return find(cur, x) == 1;
}


void printTable(HashTable *ht)
{
	int i;
	printf("----------\n");
	for (i = 0; i < ht->size; i++)	{
		printf("%d --> ", i);
		print(ht->a[i]);
		}
	printf("# of Collisions=%d\n", ht->collisions);
	printf("Load Factor %%=%.2f\n----------", loadFactor(ht));
}

void erase(HashTable *ht, char *x){
	int h = hash(x,ht->size);
	LinkedList* ll = ht->a[h];
	// thing is at front
	if (ll->head!=NULL && strcmp(x,ll->head->value)==0) {
		ll->head=ll->head->next;
		ht->collisions;
		return;
	}
	if (ll->head==NULL) return;
	Node *prev = ll->head;
	Node *ptr = ll->head->next;
	while (ptr!=NULL) {
		if (strcmp(ptr->value,x)==0) {
			prev->next = ptr->next;
		-	-ht->collisions;
			return;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}


int main() {
	FILE *fp;
	fp = fopen("words.txt","r");
	int i=0;
	HashTable* h = initHashTable(101);


	char *word = (char*)malloc(sizeof(char)*MAX_WORD_SIZE);

	while (fgets(word,sizeof(word),fp)) {
	insert(h,word);
	word = (char*)malloc(sizeof(char)*MAX_WORD_SIZE);
	}

	printTable(h);
	return 0;
}
