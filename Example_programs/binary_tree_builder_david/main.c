// AVLTree  [161023]
// Code to implement AVL Trees, including test code
//
// Student exercise - change this code so that node contains key
// and string.  Write test code that builds tree with lots of nodes
// ( > 10000), adds some more nodes - confirming that tree still AVL
// tree after each insertion.  Further, test code should confirm that
// searches work - and that they all seem to be about same duration.

#include <stdio.h>
#define TESTING

#define HEADER

#ifdef HEADER

typedef struct _node  node;

struct _node {
    int		data;			// node data - single integer
    node	*left;			//
    node	*right;
    int		ht;
};

// Function prototypes
node	*insert(node *,int, int first);
node	*Delete(node *,int);
void	preorder(node *);
void	inorder(node *);
void	breadth_traverse  (node *);
node	*rotateright(node *);
node	*rotateleft(node *);
node	*RR(node *);
node	*LL(node *);
node	*LR(node *);
node	*RL(node *);

#endif //HEADER


#ifdef TESTING
int main()
{
    node *root = NULL;		// tree root node pointer
    int x,n,i,op;

    do	{
        printf("\n1)Create (enter several elements at once):   4)Print:");
        printf("\n2)Insert (enter one new element):            5)Print levels:");
        printf("\n3)Delete (element with specified data:       6)Quit");
        printf("\n\nEnter Your Choice:");
        scanf("%d",&op);

        switch(op)	{
            case 1:
                printf("Enter number of elements to insert:");
                scanf("%d",&n);
                printf("Enter element values:");
                root=NULL;
                for(i=0;i<n;i++) {
                    scanf("%d",&x);
                    root=insert(root,x,1);
                }
                break;
            case 2:
                printf("Enter data:");
                scanf("%d",&x);
                root=insert(root,x,1);
                break;
            case 3:
                printf("Enter data:");
                scanf("%d",&x);
                root=Delete(root,x);
                break;

            case 4:
                printf("\nPreorder sequence:\n");
                preorder(root);
                printf("\nInorder sequence:\n");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Levels:\n");
                breadth_traverse  (root);
                printf("\n");
                break;
        }
    } while(op!=6);

    return 0;
}// main()

#endif //TESTING


static int height (node *T)
/// Compute height of node, based on recorded heights of children. Returns
/// larger of (left-child-height +1) and (right-child-height +1). Returns 0 if
/// node pointer is NULL.
{
    int		lh = 0, rh = 0;

    if (T != NULL)	{
        lh = (T->left==NULL) ? 0 : 1+T->left->ht;
        rh = (T->right==NULL) ? 0 : 1+T->right->ht;
    }
    return (lh>rh) ? lh : rh;
}//height()


static int BF (node *T)
/// Compute balance factor - BF - for node.  BF is height of left subtree
/// minus height of right subtree.  
{
    int lh,rh;

    // Empty subtree is balanced
    if (T==NULL)	return 0;

    // Compute height of left tree - 0 for empty tree, or 1 more than height
    // recorded at root of left subtree.
    lh = (T->left==NULL) ? 0 : 1 + T->left->ht;

    // Compute height of right tree
    rh = (T->right==NULL) ? 0 : 1 + T->right->ht;

    // Balance factor - difference in height between left and right subtrees
    return (lh-rh);
}//BF()

// ============================================================================
// For amusement purposes only, some students seem to like condensed code.
// Provided here just as example of use of conditional evaluations.

int BF_condensed (node *T)
{
    return (T==NULL) ? 0 :
           ((T->left==NULL) ? 0 : 1 + T->left->ht) -
           ((T->right==NULL) ? 0 : 1 + T->right->ht);
}//balance_factor()
// ============================================================================


node *insert(node *T, int x, int first)
/// Insert new value into AVL tree.
/// @param T - pointer to AVL tree root, or NULL
/// @param x - new data to insert
/// @returns - new root node for AVL tree
{
    if (first) printf ("--Inserting value %d into AVL tree\n", x);
    if (T==NULL)	{
        // Tree pointer was null - create node, initialize and return pointer
        // essentially to new tree with one node.
        T = (node*)malloc(sizeof(node));
        T->data = x;
        T->left = NULL;
        T->right = NULL;
    } else  {
        // check that value doesn't equal root node value.  If it does, it
        // is ignored.
        if (x != T->data)	{
            // Determine which subtree node is to be placed in
            if(x > T->data) {
                // insert in right subtree
                printf ("\tInsert %d into right subtree of %d\n", x, T->data);
                T->right=insert(T->right,x,0);
                // Check if tree now unbalanced - if so, need to figure out
                // which way to balance
                if(BF(T) == -2)	{
                    printf ("\t\tHave to repair imbalance\n");
                    T = (x > T->right->data) ? RR(T) : RL(T);
                }
            } else  {
                // since equal case eliminated already, this can only be
                //  x < T->data
                printf ("\tInsert %d into left subtree of %d\n", x, T->data);
                T->left=insert(T->left,x,0);
                // check if tree now unbalanced - if so, need to figure out
                // which way to balance
                if(BF(T)==2)	{
                    printf ("\t\tHave to repair imbalance\n");
                    T = (x < T->left->data) ?  LL(T) : LR(T);
                }
            }//endif less-than/greater-than check
        } else	{
            // Found a match - which is an error. Tell user.
            printf ("\t\tERROR: Value %d already present in tree\n", x);
        }
    }//endif not NULL
    // Compute height for this node
    T->ht=height(T);
    return T;
}//insert()


node *Delete(node *T,int x)
/// Delete value from AVL tree.
/// @param T - pointer to AVL tree root, or NULL
/// @param x - data to delete
/// @returns - new root node for AVL tree
{
    node *p;

    if(T==NULL) return NULL;
    if(x > T->data)  {
        // check right subtree
        T->right=Delete(T->right,x);
        if (BF(T)==2)    T = (BF(T->left)>=0) ? LL(T) : LR(T);
    } else   if(x < T->data) {
        T->left=Delete(T->left,x);
        // Rebalance if necessary
        if (BF(T)==-2)   T = (BF(T->right)<=0) ? RR(T) : LR(T);
    } else {
        // This is where x == T->data, meaning we have found data to delete.
        if(T->right!=NULL)   {
            // delete its inorder succesor
            p = T->right;

            // find left-most node
            while(p->left!= NULL)    p=p->left;
            // copy data from that node to node being deleted
            T->data=p->data;
            T->right=Delete(T->right,p->data);
            // rebalance if needed        
            if(BF(T)==2)    T = (BF(T->left)>=0) ? LL(T) : LR(T);
        } else
            // There was no right subtree on node to delete
            return(T->left);
    }
    T->ht=height(T);
    return(T);
}


node *rotateright(node *x)
{
    node	*y;
    printf ("\t\tRight rotate around: %d\n", x->data);
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->ht=height(x);
    y->ht=height(y);
    return y;
}


node *rotateleft(node *x)
{
    node *y;
    printf ("\t\tLeft rotate around: %d\n", x->data);
    y=x->right;
    x->right=y->left;
    y->left=x;
    x->ht=height(x);
    y->ht=height(y);
    return y;
}


node *RR(node *T)
{
    T=rotateleft(T);
    return(T);
}

node * LL(node *T)
{
    T=rotateright(T);
    return(T);
}

node * LR(node *T)
// Left rotation around left child of T, followed by right rotation around T
{
    T->left=rotateleft(T->left);
    T=rotateright(T);

    return(T);
}

node *RL(node *T)
// Right rotation around right child of T, followed by left rotation around T 
{
    T->right = rotateright(T->right);
    T = rotateleft(T);
    return T;			// since T may point to a new node
}//RL()


void preorder(node *T)
// Print tree in preorder. That is, print the root node first, then print the
// left subtree, then print the right subtree.)
{
    if (T!=NULL)	{
        printf("%d(Bf=%d)",T->data,BF(T));
        if (T->left != NULL)	{
            putchar ('{'); preorder(T->left); putchar ('}');
        }
        if (T->right != NULL)	{
            putchar ('{'); preorder(T->right); putchar ('}');
        }
    }
}//preorder()

void inorder(node *T)
// Print tree inorder.  That is, print the left subtree, print the root,
// and then print the right subtree.
{
    if (T!=NULL)	{
        putchar ('{'); inorder(T->left); putchar ('}');
        printf("%d(Bf=%d)",T->data,BF(T));
        putchar ('{'); inorder(T->right); putchar ('}');
    }
}//inorder()

//=============================================================================
// Single queue code based on QUEUE1.C modified so that data items can be
// anything.  Really, I should either have #included this code or separately
// compiled it, but I wanted to keep it all together for you.

// Included because C doesn't define them, but C++ compiler used to write code
// did.
#define bool	unsigned char
#define	false	(unsigned char) 0
#define true	(unsigned char) 1

// Queue implemented using an array.  Queue positions determined by only
// front index and queue length.  Structure holds all information about one
// queue. Queue contents are typed as void pointers; with casting they can
// point to anything.

#define MAXQLEN 64

struct _queue	{
    int     front;			// index of next element to remove
    int     length;			// number of elements currently in queue
    // next place to insert is (front+length)
    // mod MAXQLEN
    void	*qdata[MAXQLEN];// queue of things of type pointer to something
};
typedef struct _queue	Queue;


Queue *qnew(void)
// Function creates new queue and initializes front and length
{
    // Get piece of memory big enough for queue and structural information
    Queue	*q = (Queue *)malloc(sizeof(Queue));
    if (q != NULL)	{
        // malloc() successful - initialize front and length for this
        // queue.
        q->front = 0;
        q->length = 0;
    }
    // return pointer to newly created queue. (If malloc() failed
    // q will be NULL; caller should check for error return.)
    return q;
}//qnew()


void qdestroy(Queue *q)
// Called when queue no longer required - basically just frees space
// malloc()ed to hold queue
{
    if (q != NULL)	free (q);
}//qdestroy()


bool qempty (Queue *q)
// Determine if queue is empty
{
    return (q->length)==0;
}//qempty()


bool qfull (Queue *q)
{
    return (q->length)==MAXQLEN;
}//qfull()


bool qinsert (Queue *q, void *n)
// Add value n to end of queue
{
    // First, check if even possible
    if (qfull(q))    return 0;
    // Can insert - new value gets placed at the end.
    q->qdata[(q->front+q->length) % MAXQLEN] = n;
    q->length++;
    return 1;
}//qinsert()


bool qremove (Queue *q, void **n)
// Parameter n is pointer to pointer to something.  Function will
// retrieve pointer to something from queue.  Only way to
// return this value to calling code is for caller to supply pointer
// to variable that can receive data; hence pointer to {pointer
// to something}.
{
    // Check if there is anything to remove
    if (qempty(q))   return 0;
    // Front element is one to remove
    *n = q->qdata[q->front++];
    // check if updating front index overflowed
    q->front = (q->front) % MAXQLEN;
    q->length--;
    return 1;
}//qremove()

//=============================================================================


void  breadth_traverse  (node* root)
// Function to traverse tree by level (or breadth).  In other words, process
// all nodes on level 0, then all nodes on level 1, then all nodes on level 2,
// etc. until there are no more nodes left to process.
{
    Queue	*q = qnew();	// Set up a queue
    node	*cNode;			// point to node currently being processed

    // Put root node of tree in queue to start
    qinsert (q, (void *)root);

    // Keep processing nodes from queue
    while (!qempty(q))    {
        // fetch front node from queue and process it
        if (qremove(q, (void **)&cNode))	{
            // print its value (example of processing)
            printf (" %3d(%d)",cNode->data, cNode->ht);
            // add children to queue of nodes to process
            if (cNode->left)	qinsert(q,(void *)cNode->left);
            if (cNode->right)	qinsert(q,(void *)cNode->right);
        } else	{
            // Something wrong - qempty() said that queue not empty, but
            // qremove() was not able to retrieve a node pointer
            fprintf (stderr, "ERROR: In breadth_traverse()\n");
            break;
        }//endif
    }//endwhile
    putchar ('\n');
    // finished with queue - we can throw it away
    qdestroy (q);
}//breadth_traverse()
