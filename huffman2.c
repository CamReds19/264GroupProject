/*
 * CP 264 Huffman Coding
 *
 * This file contains the main program,the structure of the Huffman node
 * and user interface for running your Huffman Encoder/Decoder. 
 *
 * @author Dennis, Cam, Tyler
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// A Huffman tree node
typedef struct node_t {
    unsigned int frequency;    // weight
    char data;
    struct node_t* left;
    struct node_t* right;
} node_t;

//a linked list node
typedef struct node_l {
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

bool contains(node_l ar[], char ch, int size);
node_l * getNode(node_l ar[],char ch, int size);
void printArray(node_l ar[],int size);
node_l * readFile(FILE* file);
bool isInList(linkedList* nodeList, char c);
void insert(linkedList* lst, char data, int freq);
linkedList* createOrderedList(node_l ar[]);
void printList(linkedList* lst);

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

    FILE* file = fopen("medium.txt","r");
    if(file == NULL){
        perror("Not open");
    }
    node_l * ar = readFile(file);
    linkedList *pq = createOrderedList(ar); //priority list of huffman pairs
    printList(pq);
    //create tree

    // printList(ll);

    return 0;
}

linkedList* createOrderedList(node_l ar[]) {
	linkedList * newList = (linkedList *) malloc(sizeof(linkedList));
	newList->head = NULL;
	newList->tail = NULL;
	int i = 0;
	while((ar+i)->frequency > 0) {
		insert(newList, ar[i].data, ar[i].frequency);
		i++;
	}
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

node_l * dequeue(linkedList *nodeList) {
	node_l *result = nodeList->head;
	nodeList->head = nodeList->head = nodeList->head->next;
	result->next = NULL;
	return result;
}

//returns an array
node_l * readFile(FILE* file){
	char ch = fgetc(file);
	int size = 52;
	int elements = 0;
	node_l * ar = (node_l *) malloc(sizeof(node_l)*52);
	//initialize elements to zero
	for (int i = 0; i < size; i++) {
		ar[i].data = '0';
		ar[i].frequency = 0;
	}

//    printf("%d",contains(ar,'p',size));
	while(ch != EOF){

		 // printf("%c",ch);
		 if(contains(ar,ch,size)) {
			 //Increment node freq by 1
			 // printf("inside if contains\n");
			 node_l* nodeFound = getNode(ar,ch,size);
			 nodeFound->frequency += 1;
		 } else{//If new character not in array
			 // printf("New char\n");
			 node_l* newNode = (node_l*)malloc(sizeof(node_l));
			 newNode->data = ch;
			 newNode->frequency = 1;
			 ar[elements] = *newNode;
			 elements += 1;
			 // sizeAr = sizeof(ar)/sizeof(ar[0]);

		 }
		 ch = fgetc(file);
//		 i += 1;
	}
//	printArray(ar, size);
	return ar;
    // printf("Outside of while");
}

bool contains(node_l ar[], char ch,int size){
    bool result = false;
    for(int i = 0; i < size;i++){
        if(ar[i].data == ch){
            result = true;
            break;
        }

    }
    return result;
}
void printArray(node_l ar[],int size){
    printf("In printArray, size:%d",size);

    for(int i = 0; i < size;i++){
        printf("{%c, %d} ",ar[i].data,ar[i].frequency);
    }
}
node_l* getNode(node_l ar[],char ch, int size){
    node_l * result = NULL;
    for(int i = 0; i < size;i++){
        if(ar[i].data == ch){
            result = &ar[i];
        }

    }
    return result;
}

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

//creates a nodeT from a nodeL
node_t *nodeLtoT(node_l *node) {
	node_t *nodeT = (node_t *) malloc(sizeof(node_t));
	nodeT->data = node->data;
	nodeT->frequency = node->frequency;
	return nodeT;
}

node_t *pqToTree(linkedList *pq) {
	node_t *tree = (node_t *) malloc (sizeof(node_t));

	return tree;
}
\
