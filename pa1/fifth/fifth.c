#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// check if all elements in matrix are distinct
int isDistinct(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    int seen[MAX_SIZE * MAX_SIZE] = {0}; // array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num = matrix[i][j];
            if (seen[num]) {
                return 0; 
            }
            seen[num] = 1;
        }
    }
    return 1;
}

// check is matrix is magic square
int isMagicSquare(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    int magicSum = 0;

    // sum of first row 
    for (int j = 0; j < n; j++) {
        magicSum += matrix[0][j];
    }

    for (int i = 0; i < n; i++) {
        int rowSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += matrix[i][j];
        }
        if (rowSum != magicSum) {
            return 0; 
        }
    }

    // sum of each column checked 
    for (int j = 0; j < n; j++) {
        int colSum = 0;
        for (int i = 0; i < n; i++) {
            colSum += matrix[i][j];
        }
        if (colSum != magicSum) {
            return 0; 
        }
    }

    // sum of main diagonal 
    int mainDiagonalSum = 0;
    for (int i = 0; i < n; i++) {
        mainDiagonalSum += matrix[i][i];
    }
    if (mainDiagonalSum != magicSum) {
        return 0; 
    }

    // sum of secondary diagonal 
    int secondaryDiagonalSum = 0;
    for (int i = 0; i < n; i++) {
        secondaryDiagonalSum += matrix[i][n - i - 1];
    }
    if (secondaryDiagonalSum != magicSum) {
        return 0; 
    }

    // if all #s are distinct?
    if (!isDistinct(matrix, n)) {
        return 0; 
    }

    return 1; 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    int matrix[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);

    // if magic square?
    if (isMagicSquare(matrix, n)) {
        printf("magic\n");
    } else {
        printf("not-magic\n");
    }

    return 0;
}
