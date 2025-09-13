#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNewNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// insert a key into BST & return height of inserted node
int insert(Node** root, int key) {
    if (*root == NULL) {
        *root = createNewNode(key);
        return 1; 
    }
    
    if (key < (*root)->key) {
        int height = insert(&(*root)->left, key);
        if (height != 0) {
            return height + 1; // increase height going down
        } else {
            return 0;
        }
    } else if (key > (*root)->key) {
        int height = insert(&(*root)->right, key);
        if (height != 0) {
            return height + 1; // increase height when going down
        } else {
            return 0; 
        }
    } else {
        return 0; 
    }
}

// search for key in BST
Node* search(Node* root, int key) {
    if (root == NULL) {
        return NULL; 
    }
    
    if (key < root->key) {
        return search(root->left, key);
    } else if (key > root->key) {
        return search(root->right, key);
    } else {
        return root; 
    }
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    Node *root = NULL;
    char line[100];
    

    while (fgets(line, sizeof(line), file)) {
        char command;
        int value;
        sscanf(line, "%c\t%d", &command, &value);

        if (command == 'i') {
            int height = insert(&root, value);
            if (height == 0) {
                printf("duplicate\n");
            } else {
                printf("inserted %d\n", height);
            }
        } else if (command == 's') {
            Node* foundNode = search(root, value);
            if (foundNode) {
                int height = 1; // cont height from root
                Node* current = root;
                while (current != NULL) {
                    if (value < current->key) {
                        current = current->left;
                    } else if (value > current->key) {
                        current = current->right;
                    } else {
                        break; 
                    }
                    height++;
                }
                printf("present %d\n", height);
            } else {
                printf("absent\n");
            }
        }
    }

    fclose(file);
    freeTree(root); 
    return 0;
}
