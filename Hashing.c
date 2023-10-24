#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BUCKET_SIZE 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* bucket[BUCKET_SIZE];
    int (*hashFunc)(int);
} HashTable;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
