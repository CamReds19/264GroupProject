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

bool contains(node_l ar[], char ch, int size);
node_l* getNode(node_l ar[],char ch, int size);

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
    //insert(ll, 'c', 67);
    //insert(ll, 'a', 1);
    //insert(ll, 'v', 945);
    //insert(ll, 'u', 5);

    
    FILE* file = fopen("short.txt","r");
    if(file == NULL){
        perror("Not open");
    }
    readFile(file);
    
    
    // printList(ll);

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
int sizeFile(FILE* file){
    char ch = fgetc(file);
    int count = 0;
    while(ch != EOF){
        count += 1;
        ch = fgetc(file);
    }
    return count;
}
void readFile(FILE* file){
    char ch = fgetc(file);
    int size = sizeFile(file);
    int elements = 0;
    node_l ar[size];
    int sizeAr = sizeof(ar)/sizeof(ar[0]);
    // printf("Size of array:%d",sizeAr);
    int i = 0;
    // node_l n1, n2, n3;
    // n1.data = 'a';
    // n2.data = 'p';
    // n3.data = 'l';
    // ar[0]= n1;
    // ar[1]= n2;
    // ar[2]= n3;
    
    printf("%d",contains(ar,'p',size));
    // while(i < sizeAr){

    //     // printf("%c",ch);
    //     if(contains(ar,ch,sizeAr)){
    //         //Increment node freq by 1
    //         // printf("inside if contains\n");
    //         node_l* nodeFound = getNode(ar,ch,sizeAr);
    //         nodeFound->frequency += 1;
    //     }else{//If new character not in array
    //         // printf("New char\n");
    //         node_l* newNode = (node_l*)malloc(sizeof(node_l));
    //         newNode->data = ch;
    //         newNode->frequency = 1;
    //         ar[elements] = *newNode;
    //         elements += 1;
    //         // sizeAr = sizeof(ar)/sizeof(ar[0]);

    //     }
    //     ch = fgetc(file);
    //     i += 1;
    // }
    printArray(ar, size);
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
        printf("{%c, %d}",ar[i].data,ar[i].frequency);
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
