#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
    int coef;
    int expo;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

LinkedList* init(LinkedList *l){

    l = (LinkedList*)malloc(sizeof(LinkedList));
    l->head = NULL;
    return  l;

}

int isEmpty(LinkedList *l) {
    return ( l==NULL || l->head == NULL);
}

void removeElements(LinkedList *l) {
    if (!isEmpty (l)) {
        Node *ptr = l->head;
        l->head = l->head->next;
        free(ptr);
    }
    l->head=NULL;
}

void destroy(LinkedList* l){
    removeElements(l);
    free(l);
}
Node *createNode (int _exp, int _coef, Node *nxt){
    Node *pNode = (Node *)malloc (sizeof(Node));
    if (pNode != NULL) {
        pNode->expo = _exp;
        pNode->coef = _coef;
        pNode->next = nxt; return pNode;
    }
    return pNode;
}

void add (LinkedList *l, int _exp, int _coef){
    if (l !=NULL){
        if (l->head == NULL){
            l->head = createNode(_exp,_coef,NULL);
            return;
        }
        Node *temp = l->head;
        Node *prev = NULL;
        while(temp->next!=NULL && temp->expo > _exp ){
            prev=temp;
            temp = temp ->next;
        }
        if (temp->next == NULL){
            if (temp -> expo == _exp){
                temp->coef= (temp->coef)+_coef;
                return;
            } else{
                temp->next = createNode(_exp,_coef,NULL);
                return;
            }
        }
        if (temp->expo <_exp){
            if (prev == NULL){
                l->head = createNode(_exp,_coef,temp);
                return;
            } else {
                prev->next = createNode(_exp, _coef, temp);
                return;
            }
        }else if (temp -> expo == _exp){
            temp->coef= (temp->coef)+_coef;
            return;
        }
    }
}

void PrintALL (LinkedList *l){
    printf("[");
    Node *n = l->head;
    while (n != NULL){
        printf("%dx^%d,",n->coef,n->expo);
        n=n->next;
    }
    printf("\b]\n");
}

void main(){
    LinkedList *ll = init(ll);
    add(ll,2,5);
    add(ll,3,8);
    add(ll,0,2);
    add(ll,0,2);
    PrintALL(ll);
    add(ll,2,5);
    add(ll,3,8);
    add(ll,0,2);
    add(ll,0,2);
    PrintALL(ll);
}
