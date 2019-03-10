#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayStack {
    // Structure describes collection of data to describe and contain
    // a set of numbers.  The set is described by end and size, and
    // the actual data is in an array pointed to by a.
    int		size;		// record size to detect if full
    int		end;		// records index of last location used
    int		*a;		// pointer to allocated array memory
} ArrayStack;

void init (ArrayStack *list, int size) {
    // Initialize an ArrayList to hold an array of specified size.
    list->a = malloc(sizeof(int)*size);
    list->size = size;
    list->end = -1;
}

void push (ArrayStack *list,int n){

    if (list->end == (list->size - 1)){
        realloc(list->a, (list->size)*2);
        list->size*=2;
        printf("Stack was full, the array sized was just doubled. Size Now: %d\n",list->size);
        list->a[++list->end] = n;
    } else {
        list->a[++list->end] = n;
    }
    printf("Adding %d to the stack \n", n);
}

int pop (ArrayStack *list) {

    if (list->end < 0){
        printf("Stack was empty\n");
        return -999999;
    }else if ((list->end-1) < ((list->size - 1) / 2)){
        realloc(list->a, (list->size) / 2);
        list->size /= 2;
        printf("Stack is going to be less than half full, the array sized was just halved. Size Now: %d\n", list->size);
        return (list->a[list->end--]);
    }else{
        return (list->a[list->end--]);
    }
}

int *tos(ArrayStack *list){
    return &(list->a[list->end]);
}

void printStack(ArrayStack *list){
    printf("[");
    if (list->end < 0){
        printf("NULL ");
    } else {
        int i;
        for (i=0; i<=list->end ; i++){
            printf("%d,",list->a[i]);
        }
    }
    printf("\b]\n");
}

void main(void) {
    ArrayStack ll;
    int n, *n2;

    init(&ll,8);

    printStack(&ll);

    push(&ll,5);
    push(&ll,6);
    push(&ll,8);
    push(&ll,6);
    push(&ll,8);
    push(&ll,5);
    push(&ll,6);
    push(&ll,8);
    push(&ll,6);
    push(&ll,8);

    printStack(&ll);

    n = pop(&ll);
    printf("Popped %d Top index now: %d\n",n, ll.end);
    n = pop(&ll);
    printf("Popped %d Top index now: %d\n",n, ll.end);

    n2 = tos(&ll);
    printf("This is the top element: %d Top now at: %d\n", *n2, ll.end);

    printStack(&ll);

    n = pop(&ll);
    printf("Popped %d Top index now: %d\n",n, ll.end);
    printStack(&ll);

    n = pop(&ll);
    printf("Popped %d Top index now: %d\n",n, ll.end);
    n = pop(&ll);
    printf("Popped %d Top index now: %d\n",n, ll.end);
    n = pop(&ll);
    printf("Popped %d Top index now: %d\n",n, ll.end);
    n = pop(&ll);
    printf("Popped %d Top index now: %d\n",n, ll.end);

    printStack(&ll);
}