#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

typedef struct list {
	int size;
	Node *head;
	Node *tail;
} list;

/*
void removeEnd(list* l){
	// Remove last Node from list
	printf ("Remove item at end of list\n");
	// First determine if any work to do
	if (!isEmpty (l))	{
		// Special case - if there is only one Node
		if (l->size==1)	{
			removeFront(l);
		} else	{
			// More than 1. Note how this code requires that a Node
			// be found that points to a last Node (one with a NULL
			// next pointer, and that doesn't work for the list with
			// only 1 Node.  Fun exercise for the student - think about 
			// how to redesign data and code so that all cases can
			// be handled with one piece of code.
			Node* ptr = l->head;

			// As long as the Node we're pointing to isn't the end of
			// the list, move to next Node
			while(ptr->next->next)	{
				ptr = ptr->next;
				}
			Node* delPtr = ptr->next;
			ptr->next = NULL;
			free(delPtr);
			l->size--;
			}
		}
}

void removeFront(list* l){
	// Remove first Node from list
	printf ("Remove item at front of list\n");
	if (!isEmpty (l))	{
		// List is not empty, so there is a first Node to delete.
		Node *ptr = l->head;		// point to first node
		// Note that list will be one shorter
		l->size--;
		// head of list is now element after first
		l->head = l->head->next;
		// discard node we no longer need
		free(ptr);
		}
}

void destroy(list* l){
	// Delete entire linked list - basically by repeatedly deleting first Node
	while(!isEmpty(l))	{
		removeFront(l);
	}
}
*/

int isEmpty(list *l){
	// Check if LinkedList is empty. It is empty if head pointer is NULL
	return (l->head == NULL);
}


void addFront(list *L, int val)
{
	Node *fNode = (Node *)malloc(sizeof(Node));
	if (fNode != NULL)	{
		L->size++;
		printf("Adding %d to the beginning of the list\n",val);
		if (isEmpty(L)){
			fNode->value = val;
			L->head = fNode;
			L->tail = fNode;
			return;
		}else{
			fNode->value = val;
			fNode->next = L->head;
			L->head = fNode;
		}
	}
}

void addEnd(list *l, int x){
	Node* newNode = (Node *)malloc(sizeof(Node));
	printf ("Adding %d to end of list\n", x);
	// start by increasing size of linked list
    	l->size++;
	// Now comes the fun part - have to find current last Node, so it
	// can be made to point to the new node
	if (isEmpty(l))	{
		// LinkedList currently empty - new node becomes first in list
		newNode->value = x;
		l->head = newNode;
	} else	{
		// Not empty - have to find last Node in current list and make
		// it point to new node.
		Node* ptr = l->head;
		// Traverse list until node found that doesn't point to a next one
		while(ptr->next!=NULL)	{
			ptr = ptr->next;
			}
		// ptr points to a Node with no next Node; make this Node point to
		// new one
		newNode->value=x;
		ptr->next = newNode;
		}
	
}

void addEnd2(list *l, int x){
	Node* newNode = (Node *)malloc(sizeof(Node));
	printf ("Adding %d to end of list\n", x);
	if (isEmpty(l)){
		newNode->value= x;
		l->head= newNode;
		l->tail= newNode;
		l->size++;
		return ;
		}
	newNode->value= x;
	l->tail->next= newNode;
	l->tail = newNode;
	l->size++;
}

void update(list* l){
	// Find smallest value in linked list and subtract that value from each value
	printf ("Subtract smallest value from all values in list\n");
	int temp;
	Node* ptr = l->head;
	temp = ptr->value;
	while (ptr->next){
		if (temp > ptr->value){
			temp = ptr->value;
		}
		ptr= ptr->next;
	}
	ptr = l->head;
	while (ptr-> next){
		ptr->value -= temp;
		ptr= ptr->next;
	}
	ptr->value-=temp;
}

void removeValue(list* l,int x){
	Node* ptr = l->head;
	Node* Pptr;
	printf ("Find first %d in list and remove it\n", x);
	if(ptr->value ==x) {
		l->head = ptr->next;
		free(ptr);
		l->size--;
		return;
	}
	Pptr = ptr;
	ptr = ptr->next;
	while(ptr){
		if (ptr-> value == x){
			Pptr->next = ptr->next;
			break;
		}
		Pptr = ptr;
        ptr = ptr->next;
	}
	free(ptr);
	l->size--;
}

void print(list *l){
    Node* ptr = l->head;
	printf("(");
    if(!ptr)	{
        printf("<EMPTY>");
    } else	{
    	while(ptr->next){
        	printf("%d -> ",ptr->value);
        	ptr = ptr->next;
			}
    	printf("%d",ptr->value);
		}
	printf(") [%d]\n",l->size);
}

void init(list *l){
	// Initialize LinkedList structure
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

void main(void)
{
    list ll;
	printf ("ELEC278 Lab 2 Part 2 - LinkedLists\n");
	printf("\n");
	
    init(&ll);
    
    print(&ll);
    printf("\n");
    
    addFront(&ll,5);
    addFront(&ll,2);
    addEnd2(&ll,4);
    addEnd2(&ll,3);
    print(&ll);
    printf("\n");
    
    update(&ll);
    print(&ll);
	printf("\n");
	
    removeValue(&ll,0);
    print(&ll);
	printf("\n");
	
    removeValue(&ll,2);
    //removeFront(&ll);
    //removeEnd(&ll);
    print(&ll);
    printf("\n");

    //removeFront(&ll);
    removeValue(&ll,3);
    print(&ll);
    printf("\n");

    removeValue(&ll,1);
    print(&ll);
}
