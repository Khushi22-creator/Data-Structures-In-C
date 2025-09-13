#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct hashtable {
    int size;
    node** buckets;
} hashtable;

// create new hashtable of whatevr size 
hashtable* createHashTable(int size) {
    hashtable* table = (hashtable*)malloc(sizeof(hashtable));
    table->size = size;
    table->buckets = (node**)malloc(size * sizeof(node*));
    
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

// find the hash value for the given number, negative values are converted to positive 
int hashFunction(int value, int size) {
    if (value < 0) {
        value = -value;
    }
    return value % size;
}

// search for a value in table
int search(hashtable* table, int value) {
    int index = hashFunction(value, table->size);
    node* entry = table->buckets[index];

    while (entry != NULL) {
        if (entry->data == value) {
            return 1;  
        }
        entry = entry->next;
    }
    return 0;  
}

// insert a value into the table 
int insert(hashtable* table, int value) {
    int index = hashFunction(value, table->size);

    node* current = table->buckets[index];
    while (current != NULL) {
        if (current->data == value) {
            return 0;  
        }
        current = current->next;
    }

// new node created and inserted in front of the list 
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;

    return 1;  
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("error\n");
        return 0;
    }

    hashtable* table = createHashTable(10000);

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("error\n");
        return 0;
    }

    char operation;
    int num;
    while (fscanf(file, "%c\t%d\n", &operation, &num) != EOF) {
        if (operation == 'i') {
            int result = insert(table, num);
            if (result == 1) {
                printf("inserted\n");
            } else {
                printf("duplicate\n");
            }
        } else if (operation == 's') {
            int result = search(table, num);
            if (result == 1) {
                printf("present\n");
            } else {
                printf("absent\n");
            }
        }
    }

    fclose(file);
    return 0;
}
