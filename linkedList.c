#include <stdlib.h>
#include "huffman.h"

typedef struct{
    /* data */
    node_t* head;
    node_t* tail;
} linkedList;


void insert(linkedList lst, char data, int freq) {
    node_l* newNode = (node_l*)malloc(sizeof(node_l));

    newNode->data = data;
    newNode->frequency = freq;

    node_l* fcurr;

    fcurr = lst.head;

    while (fcurr != NULL) {
        if (fcurr->frequency <= newNode->frequency) {
            fcurr = fcurr->next;
        }
        else {
            // dont make it past head
            if (fcurr->prev = NULL) {
                // insert at front
                newNode->next = fcurr;
                fcurr->prev = newNode;
                lst.head = newNode;
            }
            else {
                //  inserting in middle
                fcurr->prev->next = newNode;
                fcurr->prev = newNode;
            }
        }
    }
    // now fcurr is pointing to NULL
    // if lst is not empty
    if (lst.tail != NULL) {
        lst.tail->next = newNode;
        newNode->prev = lst.tail;
        lst.tail = lst.tail->next;
    }
    else {      // also if lst is empty
        lst.head = lst.tail = newNode;
        newNode->next = newNode->prev = NULL;
    }
}