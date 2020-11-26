/*
 * CP 264 Huffman Coding
 *
 * This file contains the main program,the structure of the Huffman node
 * and user interface for running your Huffman Encoder/Decoder. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// A Huffman tree node
typedef struct node_t {
    int index;
    unsigned int frequency;    // weight
    char data;
    struct node_t* left;
    struct node_t* right;
} node_t;

typedef struct node_l {
    int index;
    unsigned int frequency;    // weight
    char data;
    struct node_l* next;
    struct node_l* prev;
} node_l;

typedef struct linkedList {
    /* data */
    struct node_l* head;
    struct node_l* tail;
} linkedList;



int main() {
    // if (argc != 4) {
    //     fprintf(stderr,
    //             "USAGE: ./huffman [encode | decode] "
    //             "<input file> <output file>\n");
    //     return 0;
    // }
    
    // int i =0;

    // initialize();

    // if (strcmp(argv[1], "encode") == 0)
    //     encode(argv[2], argv[3]);
    // else if (strcmp(argv[1], "decode") == 0)
    //     decode(argv[2], argv[3]);
    // else
    //     fprintf(stderr,
    //             "USAGE: ./huffman [encode | decode] "
    //             "<input file> <output file>\n");

    // free_memory();
    linkedList* ll = (linkedList*)malloc(sizeof(linkedList));
    ll->head = NULL;
    ll->tail = NULL;
    insert(ll, 'c', 67);
    insert(ll, 'a', 1);
    insert(ll, 'v', 945);
    insert(ll, 'u', 5);

    printList(ll);

    return 0;
}

// linkedList* createOrderedList(FILE* f) {
//     linkedList newList;
//     FILE* file = fopen(f, "r");

//     while(!feof(file)){     // while not enf of file
//         char c = fgetc(file);       // c is the current character

//         if (!isInList(newList, c)) {
//             // insert(newList, c, freq)     // frequency
//         }
//         // if c is not in the list
//             // 
        
//         // if c is in list
//             // disregard
//     }

//     fclose(file);
//     return newList;
// }


// bool isInList(linkedList* nodeList, char c) {
//     node_l* curr = nodeList->head;

//     bool result = false;

//     while (curr != NULL && !result) {
//         if (curr->data == c) {
//             result = true;
//         }
//     }
//     return result;
// }












void insert(linkedList* lst, char data, int freq) {
    bool inserted = false;

    node_l* newNode = (node_l*)malloc(sizeof(node_l));

    newNode->data = data;
    newNode->frequency = freq;

    node_l* fcurr;

    fcurr = lst->head;

    while (fcurr != NULL && (fcurr->frequency <= newNode->frequency)) {
        fcurr = fcurr->next;
    }
    // dont make it past head
    if (fcurr != NULL) {        // if list is not empty
        if (fcurr->prev == NULL) {
            // insert at front
            newNode->next = fcurr;
            fcurr->prev = newNode;
            lst->head = newNode;
            inserted = true;
            return;
        }
        else {
            //  inserting in middle
            newNode->next = fcurr;
            newNode->prev = fcurr->prev;
            fcurr->prev->next = newNode;
            fcurr->prev = newNode;
            inserted = true;
            return;
        }
    }
    
    // now fcurr is pointing to NULL
    // if lst is not empty
    // adding to tail
    if (lst->tail != NULL) {
        lst->tail->next = newNode;
        newNode->prev = lst->tail;
        newNode->next = NULL;
        lst->tail = lst->tail->next;
    }
    else {      // also if lst is empty
        lst->head = lst->tail = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
}

void printList(linkedList* lst) {
    node_l *curr = lst->head;

    while (curr != NULL) {
        printf("{%c, %d}, \n", curr->data, curr->frequency);
        curr = curr->next;
    }
}
