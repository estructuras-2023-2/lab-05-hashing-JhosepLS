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

HashTable* createHashTable(int (*hashFunc)(int)) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    for(int i = 0; i < BUCKET_SIZE; i++) {
        ht->bucket[i] = NULL;
    }
    ht->hashFunc = hashFunc;
    return ht;
}

void insert(HashTable* ht, int x) {
    int index = ht->hashFunc(x);
    Node* newNode = createNode(x);
    newNode->next = ht->bucket[index];
    ht->bucket[index] = newNode;
}

bool find(HashTable* ht, int x) {
    int index = ht->hashFunc(x);
    Node* temp = ht->bucket[index];
    while(temp) {
        if(temp->data == x) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void delete(HashTable* ht, int x) {
    int index = ht->hashFunc(x);
    Node* temp = ht->bucket[index];
    Node* prev = NULL;
    while(temp) {
        if(temp->data == x) {
            if(prev) {
                prev->next = temp->next;
            } else {
                ht->bucket[index] = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

int mi_Mod(int x) {
    return x % BUCKET_SIZE;
}

int randomFn(int x) {
    return rand() % BUCKET_SIZE;
}

int main() {
    srand(time(NULL));

    HashTable* ht = createHashTable(mi_Mod);
    int x = 1234567;
    insert(ht, x);
    printf("Element %d found: %d\n", x, find(ht, x));

    ht = createHashTable(randomFn);
    insert(ht, x);
    printf("Element %d found: %d\n", x, find(ht, x));

    printf("Random number for 52: %d\n", randomFn(52));
    printf("Random number for 3235235: %d\n", randomFn(3235235));

    return 0;
}
