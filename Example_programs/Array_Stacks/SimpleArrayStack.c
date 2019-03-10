#include <stdio.h>

int  top = -1;
int  stack [10];

void push (int n){
    if
    stack[++top]=n;
    printf("Pushed: %d Top: %d\n",n,top);
}

int pop (void){
    return stack[top--];
}

int *tos(void){
    return &stack[top];
}

void printStack(){
    printf("[");
    if (top < 0){
        printf("NULL ");
    } else {
        int i;
        for (i=0; i<=top ; i++){
            printf("%d,",stack[i]);
        }
    }
    printf("\b]\n");
}

void main(void) {
    int n, *n2;

    printStack();

    push(5);
    push(6);
    push(8);

    printStack();

    n = pop();
    printf("Popped %d Top: %d\n",n, top);

    n = pop();
    printf("Popped %d Top: %d\n",n, top);

    n2 = tos();
    printf("This is the top element: %d Top: %d\n", *n2, top);

    printStack();

    n = pop();
    printf("Popped %d Top: %d\n",n, top);

    printStack();
}
