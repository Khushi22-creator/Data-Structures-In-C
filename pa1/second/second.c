#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node structure
struct Node {
    int data;
    struct Node* next;
};

// create new node 
struct Node* nodeCreate(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// insert value in sorted order
void insert(struct Node** head, int value) {
    struct Node* newNode = nodeCreate(value);
    
    // inserting at head
    if (*head == NULL || (*head)->data > value) {
        if (*head != NULL && (*head)->data == value) {
            free(newNode); 
            return;
        }
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while (current->next && current->next->data < value) {
        current = current->next;
    }

    // if value already exists
    if (current->data == value) {
        free(newNode); 
        return;
    }
    
    // if inserting in between or end
    if (current->next && current->next->data == value) {
        free(newNode); 
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// delete value
void deleteVal(struct Node** head, int value) {
    if (*head == NULL) {
        return; 
    }

    struct Node* temp = *head;

    // if head needs to be deleted
    if (temp->data == value) {
        *head = temp->next;
        free(temp);
        return;
    }

    // traverse list to find node to delete
    while (temp->next && temp->next->data != value) {
        temp = temp->next;
    }

    // if value not found
    if (temp->next == NULL) {
        return;
    }

    struct Node* toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
}

// display linked list
void display(struct Node* head) {
    struct Node* current = head;
    int count = 0;

    char output[1024] = {0}; 
    char buffer[32]; 

    while (current) {
        snprintf(buffer, sizeof(buffer), "%d", current->data);
        if (count > 0) {
            strcat(output, "\t");
        }
        strcat(output, buffer);
        count++;
        current = current->next;
    }

    printf("%d\n", count);
    printf("%s\n", output);
}

// free the linked list
void freeLinkedList(struct Node* head) {
    struct Node* current = head;
    struct Node* nextNode;

    while (current) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("error\n");
        return 1;
    }

    struct Node* head = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char command;
        int value;

        if (sscanf(line, "%c\t%d", &command, &value) != 2) {
            continue;
        }

        if (command == 'i') {
            insert(&head, value);
        } else if (command == 'd') {
            deleteVal(&head, value);
        }
    }

    fclose(file);

    // if list empty, print 0
    if (head == NULL) {
        printf("0\n\n");
    } else {
        display(head);
    }

    freeLinkedList(head);
    return 0;
}
