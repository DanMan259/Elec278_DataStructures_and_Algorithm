// BST.C [181008]
// Implementation of Binary Search Tree (BST) for illustrative purposes.
// This code has been modified from C++ version of BST - bst.cpp.
//
// This code has two test versions. The test versions are generated
// either by defining DEBUG1 or DEBUG2 (but not both).  The MAKEFILE
// shows an easy way to do this.
// Test version one uses an integer key and a string data item for each
// tree node. Test version 2 uses a string key and a string data item.
// The BST code is the same for each test - it all depends on the user
// deciding what the void* fields in the BST node really are.
//
// The code is quite incomplete.  As a minimum, it needs routines to do
// a search and a delete; it should also have routines to free the BST
// and the BSTNode structures.
//
// Enjoy!

#include	<stdio.h>

//#include "bst.h"

#define HEADER

// Header file is extracted from source file.
#ifdef HEADER
#pragma once
#pragma message ("--Including: " __FILE__ " - Last mod: " __TIMESTAMP__)
// Old-style multi-include prevention.
#ifndef	_BST_H
#define	_BST_H
// BST.H [181008]

// Definition of BST node. There are 4 fields - two data fields, one
// points to node key value and second points to actual data associated
// with key.  The final two fields are pointers to left and right
// subtrees.
typedef struct _bstnode	BSTNode, *pBSTNode;
struct _bstnode	{
    void	*key;
    void	*data;
    pBSTNode	lefttree;
    pBSTNode	righttree;
};
#define	BSTNodeSZ	(sizeof(struct _bstnode))

// Definition of BST. BST contains pointer to root node of tree.
// It also contains a pointer to a function that will compare key
// values.
typedef struct _bst	BST, *pBST;
struct _bst	{
    pBSTNode	proot;
    int			(*keycmp)(void *key1, void *key2);
};
#define	BSTSZ	(sizeof(struct _bst))

// Bit of a kludge.
#define ROOTNODE(bst)	(bst->proot)

#define	ERRORBST		-1		// Error return value
#define	BSTSUCCESS		0		// Successful return value
// Error conditions
#define	BSTNodeNoMem	1		// No memory for a node
#define	NoBST			2		// BST pointer was NULL
#define BSTDuplicateKey	3		// Cannot insert duplicate key

#endif _BST_H
//=====================================================================
#endif //HEADER


#define	MASK8BITS(x)	(x & 0xFF)

// Record the last error that occurred in this code
static int		BSTlasterror = 0;

// When caller wants to know what went wrong, tell them
int lastBSTerror (void)	{ return BSTlasterror; }


pBSTNode newBSTNode (void *initkey, void *initdata)
// Create new BSTnode and initialize it. Parameters will be used for
// initial key (pointer) and data (pointer) values.
{
    pBSTNode pbstn = (pBSTNode) malloc (BSTNodeSZ);
    // Did we get memory? If so, initialize it.
    if (pbstn != NULL)	{
        pbstn->lefttree = NULL;
        pbstn->righttree = NULL;
        pbstn->key = initkey;
        pbstn->data = initdata;
    }
    return pbstn;
}//newBSTNode()

int destroyBSTNode (pBSTNode *ppbstn,
                    int (*dkey)(void *),
                    int (*ddta)(void *))
// Destroy an existing BST node. Note that it is not sufficient to
// just release the memory that our node data structure occupies -
// the key and the data fields may contain pointers to memory that
// should aslo be released. Caller has to provide routines to do
// that. Note also that first parameter is pointer to node pointer.
// This is done so that we can wipe out actual node pointer.
// Return value is -1 if node pointer is NULL. (If it is invalid,
// bad things will happen and some exception will occur. This code
// does not attempt to forestall that.)  Return value is 0 if
// everything worked OK.  Return value will be non-zero if either (or
// both) of the supplied delete routines return a non-zero value; in
// particular, the lowest 8 bits of the ddta return value will be in
// the bootom 8 bits of the return value and the lowest 8 bits of the
// dkey return value will be in the second byte from the bottom of the
// return value.  It is up to the caller to recognize and fix what has
// gone wrong.
{
    pBSTNode	pbstn = *ppbstn;	// actual pointer to node
    int			rslt = 0;

    if (pbstn == NULL)	{
        // caller appears to be trying to mess with us
        rslt = -1;
    } else	{
        if (dkey != NULL)	{
            // caller gave us routine to destroy key
            rslt = MASK8BITS(dkey (pbstn->key)) << 8;
        }
        if (ddta != NULL)	{
            // caller gave us routine to destroy data
            rslt = rslt | MASK8BITS(ddta (pbstn->data));
        }
        // All data pointed to by node has been freed - get rid of
        // actual node.
        free (pbstn);
        *ppbstn = NULL;		// now no one even knows where it was
    }
    return rslt;
}


pBST newBST(pBSTNode initroot, int (*f)(void*, void*))
// Create new BST. Parameters are pointer to an existing BSTNode to
// become the root of the BST, and a pointer to a function that will
// compare the key values in two BST nodes. Parameter initroot may be
// NULL.
{
    pBST pbst = (pBST) malloc (BSTSZ);
    if (pbst != NULL)	{
        pbst->proot = initroot;
        pbst->keycmp = f;
    }
    return pbst;
}//newBST()


// * TODO:
// Function to destroy - deallocate all memory for - a BST. Needs to
// user supplied function to clean up node data.

// * TODO:
// Function to find node with particular key - returns pointer to data
// associated with key


static int bareinsert (pBSTNode proot, pBSTNode newnode,
                       int (*kcmp)(void *, void *))
// Actual insert into tree of BST nodes. First parameter is pointer to
// root node of BST. Second parameter is pointer to node to insert.
// Third parameter is pointer to function used to compare node keys.
{
    // Compare value of new key with root key
    int	cmp_rslt = (*kcmp)(proot->key, newnode->key);
    if (0 == cmp_rslt)	{
        // Cannot add node with same key as existing node
        BSTlasterror = BSTDuplicateKey;
        return ERRORBST;
    }
    if (cmp_rslt > 0)	{
        // newnode key is greater than root key.  New node belongs on
        // right subtree. Is there a right subtree?
        if (proot->righttree == NULL)	{
            // Empty right subtree - add newnode here
            proot->righttree = newnode;
            return BSTSUCCESS;
        }
        return bareinsert (proot->righttree, newnode, kcmp);
    } else	{
        // newnode key is less than root key.  New node belongs on
        // left subtree. Is there a left subtree?
        if (proot->lefttree == NULL)	{
            // Empty left subtree - add newnode here
            proot->lefttree = newnode;
            return BSTSUCCESS;
        }
        return bareinsert (proot->lefttree, newnode, kcmp);
    }
    return BSTSUCCESS;
}//bareinsert()


int insert (pBST ptree, void *key, void *data)
// Insert item into tree with key value and data value as given by
// parameters.  This code is unaware of actual data types.
{
    int		rslt;
    // Check first that tree specified
    if (ptree != NULL)	{
        // We have tree; let's get node to hold new stuff
        pBSTNode	pbstn = newBSTNode (key, data);
        // did we get new node?
        if (pbstn == NULL)	{
            BSTlasterror = BSTNodeNoMem;
            return ERRORBST;
        }
        // Now here's where actual work required.
        if (ptree->proot == NULL)	{
            // tree currently empty, so this is first node
            ptree->proot = pbstn;
            return BSTSUCCESS;
        }
        // Non-empty tree, so have to insert in appropriate subtree
        rslt = bareinsert (ptree->proot, pbstn, ptree->keycmp);
    }
    return rslt;
}//insert()			



void printTree (pBSTNode root, void (*prtnode)(void *key, void *data))
// Parameter root is pointer to root node of a tree. Parameter prtnode
// is pointer to a function that takes two parameters - key and data
// values - and knows how to print them.
{

    // left child.
    if (root->lefttree)	printTree (root->lefttree, prtnode);
    // Now print the node
    prtnode (root->key, root->data);
    // right child.
    if (root->righttree)	printTree (root->righttree, prtnode);
}


#if 0
void *getdata(void *pkey, Node *root)
// Limited version of find node. Searches tree looking for specified
// key. If found, returns pointer to copy of data in node. Otherwise
// returns NULL.
{
	// termination condition #1 - no tree to search
	if (root == NULL)	return root;

	// termination condition #2 - pointing to node with sought key.
	if (root->key == k)	return root;

	if (k > root->key)
		return find(k,root->rightChild);
	else
		return find(k,root->leftChild);	

// NEED BST SO THAT KEYCMP ROUTINE CAN BE FOUND
}
#endif


#ifdef DEBUG1

int	keycmp (void *a, void *b)
// Compare two keys.  In our case, the key is just an integer
{
	return  (int)((int)b - (int)a);
}

void prtnode (void *key, void *data)
{
	printf (" %d - %s\n ", (int)key, (char *)data);
}

void main (void)
{
	int	k [10] = {50, 27, 30, 72, 19, 99, 80, 78, 33, 32 };
	char *s [10] = {"Fifty", "Twenty Seven", "Thirty", "Seventy Two",
					"Nineteen", "Ninety Nine", "Eighty", "Seventy Eight",
					"Thirty Three", "Thirty Two"};
	int		i;
	pBST	BST = newBST(NULL, keycmp);

	printf ("Testing BST code\n");
	
	for (i=0; i<10; i++)	{
		printf ("Inserting  %d - %s\n", k[i], s[i]);
		insert (BST, (void *) k[i], (void *) s[i]);
		}
	printTree (ROOTNODE(BST), prtnode);
}

#endif

#ifdef DEBUG2

int	keycmp (void *a, void *b)
// Compare two keys.  In this case, the keys are c-strings.
{
	return strcmp ((char *)b, (char *)a);
}


void prtnode (void *key, void *data)
{
	printf (" %s - %s\n ", (char *)key, (char *)data);
}

void main (void)
{

	char	*parms [10] = {
			"Country",
			"Language",
			"Decimal",
			"Tax 1 Name",
			"Tax 2 Name",
			"Tax 1 Rate",
			"Tax 2 Rate",
			"Year End",
			"SubRegion",
			"Municipality"
			};
	char	*attr [10] = {
			"Canada",
			"English",
			"Dot",
			"HST",
			"PST",
			"7 pc",
			"5 pc",
			"2018-09-30",
			"Ontario",
			"Kingston"
			};


	int		i;
	pBST	BST = newBST(NULL, keycmp);

	printf ("Testing BST code\n");
	
	for (i=0; i<10; i++)	{
		printf ("Inserting  %s - %s\n", parms[i], attr[i]);
		insert (BST, (void *) parms[i], (void *) attr[i]);
		}
	printTree (ROOTNODE(BST), prtnode);
}

#endif
