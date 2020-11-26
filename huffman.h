#include <stdbool.h>

#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef node_t;
typedef node_l;

node_t* createOrderedList(FILE* f);
bool isInList(node_t* node, char c);

#endif