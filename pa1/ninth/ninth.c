#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// creates new node 
Node* createNewNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; 
    return newNode;
}

// get height of node 
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// update height of node 
void replaceHeight(Node* node) {
    if (node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

// returns new root of subtree
Node* insert(Node* root, int value, int* depth) {
    if (!root) {
        *depth = 1;  
        return createNewNode(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value, depth);
        *depth += 1;  // increment depth going down
    } else if (value > root->value) {
        root->right = insert(root->right, value, depth);
        *depth += 1;  // ^^
    } else {
        *depth = 0;  
        return root;
    }

    replaceHeight(root);
    return root;
}


// tracks height from root
Node* search(Node* root, int value, int* depth) {
    if (!root) return NULL;
    if (root->value == value) return root;

    *depth += 1; 
    if (value < root->value) {
        return search(root->left, value, depth);
    } else {
        return search(root->right, value, depth);
    }
}

// find node with min val.
Node* findMin(Node* node) {
    while (node->left) node = node->left;
    return node;
}

// delete node from BST
Node* deleteNode(Node* root, int value, int* success) {
    if (!root) {
        *success = 0; 
        return root;
    }

    if (value < root->value) {
        root->left = deleteNode(root->left, value, success);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value, success);
    } else {
        *success = 1; 

        // no left child
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        // no right child 
        else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: two children, min in right subtree 
        Node* temp = findMin(root->right);
        root->value = temp->value; 
        root->right = deleteNode(root->right, temp->value, success); 
    }

    replaceHeight(root);
    return root;
}

// print results 
void printResult(int operationType, int heightOrSuccess) {
    if (operationType == 1) { 
        if (heightOrSuccess == 0) {
            printf("duplicate\n");
        } else {
            printf("inserted %d\n", heightOrSuccess);
        }
    } else if (operationType == 2) { 
        if (heightOrSuccess == 0) {
            printf("absent\n");
        } else {
            printf("present %d\n", heightOrSuccess);
        }
    } else if (operationType == 3) { 
        if (heightOrSuccess) {
            printf("success\n");
        } else {
            printf("fail\n");
        }
    }
}

void processFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("error\n");
        return;
    }

    Node* root = NULL;
    char operation;
    int value, height, success;

    while (fscanf(file, " %c %d", &operation, &value) == 2) {
    if (operation == 'i') { 
        int depth = 1;  
        root = insert(root, value, &depth);
        printResult(1, depth);  
    } else if (operation == 's') { 
        int depth = 1;  
        Node* foundNode = search(root, value, &depth);
        printResult(2, foundNode ? depth : 0);
    } else if (operation == 'd') { 
        root = deleteNode(root, value, &success);
        printResult(3, success);
    }
    }


    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("error\n");
        return 1;
    }
    processFile(argv[1]);
    return 0;
}
