#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//----------------------------------------------------------

struct treeNode {
    int data;
    bool visited;
    struct treeNode* left;
    struct treeNode* right;
};

typedef struct stk_node {
    struct stk_node* next;
    struct treeNode* tree;
} StkNode;

struct item {
    struct item* next;
    struct treeNode* tree;
};

//-------------
void push(struct treeNode* t);
struct treeNode* pop(StkNode* stk);
struct treeNode* tos(StkNode* stk);
void print(void);
struct treeNode* dequeue(void);
void enqueue(struct treeNode* Tree);
bool isEmpty(void);
//-------------

StkNode* stk1 = NULL;
StkNode* stk2 = NULL;
struct treeNode* root = NULL;

struct item *front, *end;
int count = 0;

struct treeNode* newNode(int value)
{

    struct treeNode* node = (struct treeNode*)malloc(sizeof(struct treeNode));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    node->visited = false;

    return node;
}

/**
 * visit
 * left
 * right
 */
void preOrder(struct treeNode* t)
{

    if(t != NULL) {
        printf("%d\n", t->data);
        preOrder(t->left);
        preOrder(t->right);
    }
}

/**
 * left
 * visit
 * right
 */
void inOrder(struct treeNode* t)
{

    if(t != NULL) {
        inOrder(t->left);
        printf("%d\n", t->data);
        inOrder(t->right);
    }
}

/**
 * left
 * right
 * visit
 */
void postOrder(struct treeNode* t)
{

    if(t != NULL) {
        postOrder(t->left);
        postOrder(t->right);
        printf("%d\n", t->data);
    }
}

int treeTotal(struct treeNode* t)
{

    int sum, leftSum, rightSum;

    if(t->left == NULL)
        leftSum = 0;
    else
        leftSum = treeTotal(t->left);

    if(t->right == NULL)
        rightSum = 0;
    else
        rightSum = treeTotal(t->right);

    sum = t->data + leftSum + rightSum;
    return sum;
}

int getHeight(struct treeNode* t)
{

    int hL, hR, h;
    if(t == NULL) {
        return -1;
    } else {
        hL = getHeight(t->left);
        hR = getHeight(t->right);
        h = 1 + ((hL > hR) ? hL : hR);
    }
    return h;
}

bool wasVisited(struct treeNode* Node)
{

    if((Node->right == NULL && Node->left->visited) || (Node->left == NULL && Node->right->visited) ||
        (Node->left->visited && Node->right->visited)) {
        return true;
    } else
        return false;
}

int impTreeTotal(struct treeNode* t)
{

    int sum = 0;
    push(t);
    while(stk1 != NULL) {
        struct treeNode* node = tos(stk1);
        if(node->left == NULL && node->right == NULL || wasVisited(node)) { //|| node -> left -> visited == true
            struct treeNode* p = pop(stk1);

            sum = sum + p->data;
            node->visited = true;

        } else {
            if(node->right != NULL && node->visited == false) {
                push(node->right);
            }
            if(node->left != NULL && node->visited == false) {
                push(node->left);
            }
        }
    }
    return sum;
}

void breadthTrav(struct treeNode* root)
{

    enqueue(root);
    while(!isEmpty()) {
        struct treeNode* cNode = dequeue();
        printf("%d\n", cNode->data);
        if(cNode->left)
            enqueue(cNode->left);
        if(cNode->right)
            enqueue(cNode->right);
    }
}

struct treeNode* findNodeBst(struct treeNode* t, int n)
{
    if (t == NULL) return NULL;
    else if ( t->data > n)return (findNodeBst(t->left,n));
    else if (t->data < n)return (findNodeBst(t->right,n));
    else return t;
    
}

struct treeNode * findParentBst(struct treeNode* t, int n){
    if (t == NULL) return NULL;
    else if ( t->data > n){
        if (t->left ->data == n ) return t;
        else return (findParentBst(t->left,n));
    }
    else if (t->data < n){
        if (t->right ->data == n ) return t;
        else return (findParentBst(t->right,n));
    }
    else return t;
}

struct treeNode * findRightTreeLeftMostNode(struct treeNode * NODE){
    struct treeNode * rightSubtreeRoot = NODE -> right; 
    if (rightSubtreeRoot -> left != NULL){
        while (rightSubtreeRoot -> left != NULL){
            rightSubtreeRoot = rightSubtreeRoot -> left; 
        }
    }
    
    return rightSubtreeRoot;  //leftmost item of right subtree
    
}

struct treeNode * deleteTreeNodeBst(struct treeNode* t, int n)
{
    int sCase = 0;
    struct treeNode * NODE = findNodeBst(t,n), * nodeParent = findParentBst(t,n), *temp, *leftsParent, *NODE_RIGHT;
    // 1 if LEAF
    if (NODE -> left == NULL && NODE -> right ==NULL) sCase = 1;
    // 2 if only one right subtree
    else if (NODE -> left == NULL && NODE -> right != NULL) sCase = 2;
    // 3 if only one left subtree
    else if (NODE -> right == NULL && NODE -> left != NULL) sCase = 3;
    // 4 if both left and right subtree
    else if (NODE -> right != NULL && NODE -> left != NULL) sCase = 4;
    
    temp = NODE;
    
    switch (sCase){
        case 0 :
            break;
    
        case 1 :
            if ((nodeParent -> right -> data) == n){
                
                nodeParent -> right = NULL;
            }else{
                nodeParent -> left = NULL;
            }
            break;
       
        case 2 :
            nodeParent -> left = temp -> right;
            break;
            
        case 3 :
            nodeParent -> right = temp -> left; 
            break; 
        
        case 4 :
            
            temp = findRightTreeLeftMostNode(NODE);
            leftsParent = findParentBst(root,temp -> data);
            
            if (nodeParent -> right -> data == NODE -> data){
                if (temp->right != NULL){
                    leftsParent -> right = temp -> right; 
                    nodeParent -> right = temp;
                }else{
                    nodeParent -> right = temp;
                }
                
            }else{//here
                if (temp->right != NULL){
                    leftsParent -> right = temp -> right; 
                    nodeParent -> left = temp;
                }else{
                    nodeParent -> left = temp;
                }
            }
            
            
            
            
            
            
            
            
            
            
            
            if (temp -> right != NULL){
                
                leftsParent -> left = temp -> right; 
                
            }else {
                leftsParent -> left = NULL; 
            }
        
            break;           
    }
    return t;
    
    
}

// ----------------------------------------------------------------

void push(struct treeNode* t)
{
    StkNode* p = malloc(sizeof(StkNode));
    p->tree = t;
    p->next = stk1;
    stk1 = p;
}

struct treeNode* pop(StkNode* stk)
{
    StkNode* p = stk;
    struct treeNode* poppedItem = p->tree;
    stk1 = p->next; // stk1 instead of stk

    return poppedItem;
}

struct treeNode* tos(StkNode* stk)
{
    return &(*stk->tree);
}

// ------------------QUEUE STUFF----------------------------------------------

bool isEmpty(void)
{
    return (count == 0);
}

void enqueue(struct treeNode* Tree)
{
    struct item* pnew = malloc(sizeof(struct item));
    pnew->tree = Tree;
    pnew->next = NULL;

    if(end != NULL) {
        end->next = pnew;
    }
    end = pnew;

    if(front == NULL) {
        front = pnew;
    }
    count++;
}

struct treeNode* dequeue(void)
{ // int *n as argument why
    struct item* temp = front;
    if(count == 0) {
        return false;
    }
    //*n = front -> value;
    front = front->next;
    // free(temp);
    count--;
    return temp->tree;
}

void print(void)
{
    struct item* goThrough;
    goThrough = front;
    for(int i = 0; i < count; i++) {
        printf("%d \n", goThrough->tree->data);
        goThrough = goThrough->next;
    }
}

// ----------------------------------------------------------------

int main()
{
    struct treeNode *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m ,*n,*o,*p,*q,*r,*s;
    root = newNode(10);

    b = newNode(5);
    i = newNode(15);
    root->right = i;
    root->left = b;
    c = newNode(3);
    f = newNode(7);
    b->right = f;
    b->left = c;
    d = newNode(1);
    e = newNode(4);
    c->right = e;
    c->left = d;
    g = newNode(6);
    h = newNode(9);
    f->right = h;
    f->left = g;
    j = newNode(11);
    k = newNode(17);
    i->right = k;
    i->left = j;
    l = newNode(13);
    m = newNode(12);
    n = newNode(14);
    j -> right = l;
    l -> right = n;
    l -> left  = m;
    o = newNode(45);
    p = newNode(25);
    q = newNode(21);
   // r = newNode(20);
    s = newNode(23);
    k -> right = o;
    o -> left = p;
    p -> left = q;
   // q -> left = r;
    q -> right = s;
    

    //breadthTrav(root);
    //  inOrder(root);
    // preOrder(root);
    //int a = 3;
    //struct treeNode* temp = findParentBst(root, a);
    //printf("parent of %d is %d\n",a,temp->data);
    //printf("parent points to right is %d\n", temp->right->data);
    //printf("parent points to left is %d\n", temp->left->data);
    
    root = deleteTreeNodeBst(root, 5);
    breadthTrav(root);
    
    
    // int height = getHeight(root);
    // printf("\nThe height of the tree is %d\n", height);
}
