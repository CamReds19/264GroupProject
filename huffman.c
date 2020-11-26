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
#include "huffman.h"
#include "linkedList.h"

// A Huffman tree node
typedef struct {
    int index;
    unsigned int frequency;    // weight
    char data;
    node_t* left;
    node_t* right;
} node_t;

typedef struct {
    int index;
    unsigned int frequency;    // weight
    char data;
    node_l* next;
    node_l* prev;
} node_l;

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr,
                "USAGE: ./huffman [encode | decode] "
                "<input file> <output file>\n");
        return 0;
    }
    
    int i =0;

    initialize();

    if (strcmp(argv[1], "encode") == 0)
        encode(argv[2], argv[3]);
    else if (strcmp(argv[1], "decode") == 0)
        decode(argv[2], argv[3]);
    else
        fprintf(stderr,
                "USAGE: ./huffman [encode | decode] "
                "<input file> <output file>\n");

    free_memory();

    return 0;
}

linkedList* createOrderedList(FILE* f) {
    linkedList newList;
    FILE* file = fopen(f, "r");

    while(!feof(file)){     // while not enf of file
        char c = fgetc(file);       // c is the current character

        if (!isInList(newList, c)) {
            // insert(newList, c, freq)     // frequency
        }
        // if c is not in the list
            // 
        
        // if c is in list
            // disregard
    }

    fclose(file);
    return newList;
}


bool isInList(linkedList* nodeList, char c) {
    node_l* curr = nodeList->head;

    bool result = false;

    while (curr != NULL && !result) {
        if (curr->data == c) {
            result = true;
        }
    }
    return result;
}