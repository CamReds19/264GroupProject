/*
-------------------------------------
File:    avl_tree.c
Project: avl_tested
file description
-------------------------------------
Author:  Heider Ali
ID:      9999999999
Email:   heali@wlu.ca
Version  2020-11-15
-------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

#define FALSE 0
#define TRUE 1

typedef struct node
{
	struct node *lchild;
	int info;
	struct node *rchild;
	int balance;
} node;

struct node *insert(struct node *pptr, int ikey)
{
	// < put your code here >
	static int taller;
	if(pptr==NULL)	/*Base case*/
	{
		pptr = (struct node *) malloc(sizeof(struct node));
		pptr->info = ikey;
		pptr->lchild = NULL;
		pptr->rchild = NULL;
		pptr->balance = 0;
		taller = TRUE;
	}
	else if(ikey < pptr->info)	//Insert in left subtree
	{
		pptr->lchild = insert(pptr->lchild, ikey);
		if (taller) {
			pptr = insert_left_check( pptr, &taller );
		}
	}
	else if(ikey > pptr->info)	//Insert in right subtree
	{
		pptr->rchild = insert(pptr->rchild, ikey);
		if (taller) {
			pptr = insert_right_check(pptr, &taller);
		}
	}
	else  //if key already exists
	{
		printf("Duplicate key\n");
		taller = FALSE;
	}
	return pptr;
}/*End of insert( )*/

struct node *insert_left_check(struct node *pptr, int *ptaller )
{
	switch(pptr->balance)
	{
	 // < put your code here >
		case 0:
			pptr->balance = 1;	//left heavy
			break;
		case -1:
			pptr->balance = 0;	//balanced
			*ptaller = FALSE;
			break;
		case 1:
			pptr = insert_LeftBalance(pptr);
			*ptaller = FALSE;
	}
	return pptr;
}/*End of insert_left_check( )*/

struct node *insert_right_check(struct node *pptr, int *ptaller )
{
	// < put your code here >
	switch(pptr->balance)
	{
		case 0:
			pptr->balance = -1;	//right heavy
			break;
		case 1:
			pptr->balance = 0;	//now balanced
			*ptaller = FALSE;
			break;
		case -1:
			pptr = insert_RightBalance(pptr);
			*ptaller = FALSE;
	}
	return pptr;
}/*End of insert_right_check( )*/

struct node *insert_LeftBalance(struct node *pptr)
{
	struct node *aptr, *bptr;

	aptr = pptr->lchild;
	if(aptr->balance == 1)  /* Case L_C1 : Insertion in AL */
	{
			pptr->balance = 0;
			aptr->balance = 0;
			pptr = RotateRight(pptr);
	}
	else            /* Case L_C2 : Insertion in AR */
	// < put your code here >
	{
		bptr = aptr->rchild;
		switch(bptr->balance)
		{
			case 0:
				pptr->balance = 0;
				aptr->balance = 0;
				break;
			case 1:
				pptr->balance = -1;
				aptr->balance = 0;
				break;
			case -1:
				pptr->balance = 0;
				aptr->balance = 1;
		}
		bptr->balance = 0;
		pptr->lchild = RotateLeft(aptr);
		pptr = RotateRight(pptr);
	}
	return pptr;
}/*End of insert_LeftBalance( )*/

struct node *insert_RightBalance(struct node *pptr)
{
	struct node *aptr, *bptr;

	aptr = pptr->rchild;
	if(aptr->balance == -1) /* Case R_C1 : Insertion in AR */
	{
			pptr->balance = 0;
			aptr->balance = 0;
			pptr = RotateLeft(pptr);
	}
	else            /* Case R_C2 : Insertion in AL */
	{
		// < put your code here >
		bptr = aptr->lchild;
		switch(bptr->balance)
		{
		case -1:
			pptr->balance = 1;
			aptr->balance = 0;
			break;
		case 1:
			pptr->balance = 0;
			aptr->balance = -1;
			break;
		case 0:
			pptr->balance = 0;
			aptr->balance = 0;
		}
		bptr->balance = 0;
		pptr->rchild = RotateRight(aptr);
		pptr = RotateLeft(pptr);
	}
	return pptr;
}/*End of insert_RightBalance( )*/

struct node *RotateLeft(struct node *pptr)
{
	// < put your code here>
	struct node *aptr = pptr->rchild;
	pptr->rchild = aptr->lchild;
	aptr->lchild = pptr;
	return aptr;
}/*End of RotateLeft( )*/

struct node *RotateRight(struct node *pptr)
{
	// < put your code here>
	struct node *aptr = pptr->lchild;
	pptr->lchild = aptr->rchild;
	aptr->rchild = pptr;
	return aptr;
}/*End of RotateRight( )*/


void display(struct node *ptr,int level)
{
        int i;
        if(ptr == NULL )/*Base Case*/
                return;
        else
    {
                display(ptr->rchild, level+1);
                printf("\n");
                for (i=0; i<level; i++)
                        printf("    ");
                printf("%d", ptr->info);
                display(ptr->lchild, level+1);
        }
}/*End of display()*/

