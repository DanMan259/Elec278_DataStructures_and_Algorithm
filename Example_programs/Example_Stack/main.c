#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _stk_node {
    struct _stk_node *next;
    int nodval;
} StkNode;

StkNode *head = NULL;

void push (int n)
{
    StkNode *p = malloc(sizeof(StkNode));
    p->nodval = n;
    p->next = head;
    head = p;
}

int pop (void)
{
    StkNode *p = head;
    int rslt = p->nodval;
    head = p->next;
    return rslt;
}

int *tos (void)
{
    return &(head->nodval);
}

void main() {
    int *x, y = 3;

    push(8);

    push(9);

    push(y);

    x = tos();

    printf(" %d", *x);

    pop();

    x = tos();

    pop();

    push(22+ *x);

    printf("%d", *x);
}