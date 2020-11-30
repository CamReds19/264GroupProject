/*
 * CP 264 Huffman Coding
 *
 * This file contains the main program,the structure of the Huffman node
 * and user interface for running your Huffman Encoder/Decoder. 
 *
 * @author Dennis, Cam, Tyler, Melissa
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
    struct node_l* left;
    struct node_l* right;

} node_l;

typedef struct linkedList {
    /* data */
    struct node_l* head;
    struct node_l* tail;
    int size;
} linkedList;

// Forward Declarations
bool contains(node_l ar[], char ch, int size);
node_l * getNode(node_l ar[],char ch, int size);
void printArray(node_l ar[],int size);
node_l * readFile(FILE* file);
bool isInList(linkedList* nodeList, char c);
void insert(linkedList* lst, node_l *node);
linkedList* createOrderedList(node_l ar[]);
void printList(linkedList* lst);
node_l *pqToTree(linkedList *pq);
void display( node_l *ptr, int level);
int * encode_c(node_l* node, int encoding[], int index, char c);
char* decode(node_l* node, char* decodeStr);
FILE* makeFileWrite(char* fName);
FILE* makeFileRead(char* fName);


int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr,
                "USAGE: ./huffman [encode | decode] "
                "<input file> <output file>\n");
        return 0;
    }

    bool treeInfo = false;

    linkedList* ll = (linkedList*)malloc(sizeof(linkedList));
    ll->head = NULL;
    ll->tail = NULL;

    if (strcmp(argv[1], "encode") == 0) {
        FILE* file = makeFileRead(argv[2]); // opens text file to read
        FILE* outFile = makeFileWrite(argv[3]); // creates output text file with given file name
        node_l * ar = readFile(file);           // read thru contents of file adding to array
        linkedList *pq = createOrderedList(ar); //priority list of huffman pairs from array
        while (pq->size > 1) {
            pqToTree(pq);   // pq to tree while pq has elements
        }
        display(pq->head, 0);   // testing display tree function
        printf("\n\nThe Huffman Encoding is: ");
        int * encoding = (int *) malloc(sizeof(int)*100);
        printf("The encoding is: \n");
        FILE * file2 = makeFileRead(argv[2]);
        char ch = fgetc(file2);
        while (ch != EOF) {
        	encode_c(pq->head, encoding, 0, ch);   // requires tree root and encoding string
        	ch = fgetc(file2);
        }

        int size = 100;

//        for (int i = 0; i < size; i++) {
//        	printf("%d", encoding[i]);
//        }
        printf("\n");
        treeInfo = true;            // if we encoded, we have information to decode
        // encode_c(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "decode") == 0)
        if (treeInfo) {
            decode(argv[2], argv[3]);
        }
        else {
            printf("Must encode before decode");
        }
    else
        fprintf(stderr,
                "USAGE: ./huffman [encode | decode] "
                "<input file> <output file>\n");


    // printf("%s",decode(pq->head,"011001010111011100"));
}

linkedList* createOrderedList(node_l ar[]) {
    // Creates and frequency ordered list
	linkedList * newList = (linkedList *) malloc(sizeof(linkedList));
	newList->head = NULL;
	newList->tail = NULL;
	int i = 0;
	while((ar+i)->frequency > 0) {
		insert(newList, &ar[i]);
		i++;
	}
	return newList;
}


bool isInList(linkedList* nodeList, char c) {
    // returns true if 'c' is in Linked list
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
    // Dequeue will always be 2 smallest elements in linked list
	node_l *result = nodeList->head;
	nodeList->head = nodeList->head->next;
	result->next = NULL;
	nodeList->size--;
	if (nodeList->head==NULL) nodeList->tail = NULL;
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

	while(ch != EOF){

		 if(contains(ar,ch,size)) {
			 //Increment node freq by 1
			 node_l* nodeFound = getNode(ar,ch,size);
			 nodeFound->frequency += 1;
		 } else{//If new character not in array
			 node_l* newNode = (node_l*)malloc(sizeof(node_l));
			 newNode->data = ch;
			 newNode->frequency = 1;
             // update newNode data and frequency and add to ar array
			 ar[elements] = *newNode;
			 elements += 1;

		 }
		 ch = fgetc(file);
	}
	return ar;
}

bool contains(node_l ar[], char ch,int size){
    // returns true if array ar contains char 'ch'
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
    // test function to print contents of array
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

void insert(linkedList* lst, node_l* node) {
    // inserted designed to handle all priority sorting within the insert
    // all elements inserted will be inserted in their proper position
    bool inserted = false;

    node_l* fcurr;

    fcurr = lst->head;
    lst->size++;
    while (fcurr != NULL && (fcurr->frequency <= node->frequency)) {
        fcurr = fcurr->next;
    }
    // dont make it past head
    if (fcurr != NULL) {        // if list is not empty
        if (fcurr->prev == NULL) {
            // insert at front
            node->next = fcurr;
            fcurr->prev = node;
            lst->head = node;
            inserted = true;
            return;
        }
        else {
            //  inserting in middle
            node->next = fcurr;
            node->prev = fcurr->prev;
            fcurr->prev->next = node;
            fcurr->prev = node;
            inserted = true;
            return;
        }

    }

    // now fcurr is pointing to NULL
    // if lst is not empty
    // adding to tail
    if (lst->tail != NULL) {
        lst->tail->next = node;
        node->prev = lst->tail;
        node->next = NULL;
        lst->tail = lst->tail->next;
    }
    else {      // also if lst is empty
        lst->head = lst->tail = node;
        node->next = NULL;
        node->prev = NULL;
    }

}

void printList(linkedList* lst) {
    // helper function to print contents of list
    node_l *curr = lst->head;

    while (curr != NULL) {
        printf("{%c, %d}, \n", curr->data, curr->frequency);
        curr = curr->next;
    }
}

//creates a nodeT from a nodeL
// node_t *nodeLtoT(node_l *node) {
// 	node_t *nodeT = (node_t *) malloc(sizeof(node_t));
// 	nodeT->data = node->data;
// 	nodeT->frequency = node->frequency;
// 	return nodeT;
// }

node_l *pqToTree(linkedList *pq) {
    // handles taking 2 smallest values from pq (linked list) into our huffman tree
    // updates the parents nodes accordingly
    // returns a tree with pq values as leaf nodes within huffman tree

    node_l* leafOne = dequeue(pq);
    node_l* leafTwo = dequeue(pq);

    node_l* rootParent = (node_l *) malloc (sizeof(node_l));

    rootParent->left = leafOne;
    rootParent->right = leafTwo;

    rootParent->data = '*';
    // parent frequency sum of child frequencies
    rootParent->frequency = leafOne->frequency + leafTwo->frequency;
    insert(pq, rootParent);

	return rootParent;
}

void display( node_l *ptr, int level)
// taken from previous labs
// helper code to display tree structure
{
	int i;
	if(ptr == NULL )// Base Case
		return;
	else
    {
		display(ptr->right, level+1);
		printf("\n");
		for (i=0; i<level; i++)
				printf("    ");
		printf("%c", ptr->data);
		display(ptr->left, level+1);
	}
}

int * encode_c(node_l* node, int encoding[], int index, char c) {
	if (node->left != NULL)
	{
		encoding[index] = 0;
		encode_c(node->left, encoding, index + 1, c);
	}

	if (node->right != NULL)
	{
		encoding[index] = 1;
		encode_c(node->right, encoding,index + 1, c);
	}
	if (node->data!='*') {
		if (node->data == c) {
			FILE *fptr = fptr = fopen("encoded.dat","a");
			for(int i = 0; i < index; i++) {

				fprintf(fptr, "%d", encoding[i]);
			}
			fclose(fptr);
		}
	}
	return encoding;
}

char* decode(node_l* root, char decodeStr[]){
    char* result = (char*)malloc(sizeof(char)*100);
    node_l* temp = root;

    int size = strlen(decodeStr);
    // do for each char in decodeStr
    for(int i = 0; i <size;i++){

        if(temp->data == '*'){
            // not at a leaf node
            if(decodeStr[i] == '1'){
                // if we read a 1, go right
                temp = temp->right;
                if(temp->data != '*'){
                    // now at a leaf node
                    strcat(result,&temp->data);
                    temp = root;
                }
            }else{

                temp = temp->left;
                if(temp->data != '*'){
                    // now at leaf node
                    strcat(result,&temp->data);
                    // concatenate the data from value at temp with our resulting decoded string
                    temp = root;
                }
            }
        }
    }
    return result;
}


FILE* makeFileWrite(char* fName){
    // creates a new output file given user input
    // returns a newly created file already open
    FILE* fp = fopen(fName,"w");
    if(fp == NULL){
        perror("Not open");
    }
    return fp;
}

FILE* makeFileRead(char* fName){
    // creates a new output file given user input
    // returns a newly created file already open
    FILE* fp = fopen(fName,"r");
    if(fp == NULL){
        perror("Not open");
    }
    return fp;
}
