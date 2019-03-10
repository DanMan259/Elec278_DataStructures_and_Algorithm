#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ArrayQueue {
    // Structure describes collection of data to describe and contain
    // a set of numbers.  The set is described by end and size, and
    // the actual data is in an array pointed to by a.
    int		size;		// record size to detect if full
    int		front;		// records index of first location used
    int		end;		// records index of last location used
    int     count;      //counts the number of elements
    int		*a;		// pointer to allocated array memory
} ArrayQueue;

bool isEmpty(ArrayQueue *list){
    return (list->count == 0);
}

bool isFull(ArrayQueue *list){
    return (list->count == list->size);
}

void init (ArrayQueue *list, int size) {
    // Initialize an ArrayList to hold an array of specified size.
    list->a = malloc(sizeof(int)*size);
    list->size = size;
    list->count = 0;
    list->end = list->front = -1;
}
void printHelper(ArrayQueue *list, int index){
    if (index == list->end){
        printf("%d,",list->a[index]);
        return;
    }
    printf("%d,",list->a[index]);
    index = (index+1)% list->size;
    printHelper(list,index);
}

void printQueue(ArrayQueue *list){
    printf("[");
    if (list->end < 0){
        printf("NULL ");
    } else {
        printHelper(list,list->front);
    }
    printf("\b]\n");
}

bool enqueue (ArrayQueue *list, int n){
    if (isFull(list)){
        printf("Array is Full\n");
        return false;
    }
    list->end=(list->end+1)%list->size;
    list->a[list->end]=n;
    list->count++;
    printf("Adding %d to the queue \n", n);
    if (list->front==-1){
        printf("First Element is added!\n");
        list->front=list->end;
    }
    return true;
}

bool dequeue (ArrayQueue *list, int *n){
    if (isEmpty(list)){
        printf("Array is empty\n");
        return false;
    }
    *n=list->a[list->front];
    list->front=(list->front+1)%list->size;
    list->count--;
    //Checking to see if the thing is empty
    if (isEmpty(list)){
        printf("Array is Empty!\n");
        list->front=list->end=-1;
    }
    return true;
}


void main(void) {
    ArrayQueue list;
    init(&list,8);
    int n;

    printQueue(&list);
    enqueue(&list,5);
    dequeue(&list,&n);
    enqueue(&list,10);
    enqueue(&list,3);
    printQueue(&list);

    enqueue(&list,2);
    printQueue(&list);

    dequeue(&list,&n);
    printf("Dequeued element: %d\n", n);

    enqueue(&list,5);
    enqueue(&list,8);
    enqueue(&list,2);
    printQueue(&list);


    dequeue(&list,&n);
    printf("Dequeued element: %d\n", n);
    dequeue(&list,&n);
    printf("Dequeued element: %d\n", n);
    dequeue(&list,&n);
    printf("Dequeued element: %d\n", n);
    dequeue(&list,&n);
    printf("Dequeued element: %d\n", n);
    dequeue(&list,&n);
    printf("Dequeued element: %d\n", n);
}