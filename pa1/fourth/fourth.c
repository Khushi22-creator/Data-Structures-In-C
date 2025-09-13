#include <stdio.h>
#include <stdlib.h>

void readMatrix(FILE *file, int ***matrix, int *rows, int *cols) {
    fscanf(file, "%d\t%d", rows, cols);
    *matrix = (int **)malloc((*rows) * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = (int *)malloc((*cols) * sizeof(int));
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &(*matrix)[i][j]);
        }
    }
}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void multiplyMatrices(int **first, int firstRows, int firstCols, int **second, int secondRows, int secondCols, int ***result) {
    *result = (int **)malloc(firstRows * sizeof(int *));
    for (int i = 0; i < firstRows; i++) {
        (*result)[i] = (int *)malloc(secondCols * sizeof(int));
        for (int j = 0; j < secondCols; j++) {
            (*result)[i][j] = 0;
            for (int k = 0; k < firstCols; k++) {
                (*result)[i][j] += first[i][k] * second[k][j];
            }
        }
    }
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf("\t");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    int **first, **second, **result;
    int firstRows, firstCols, secondRows, secondCols;

    readMatrix(file, &first, &firstRows, &firstCols);
    
    readMatrix(file, &second, &secondRows, &secondCols);

    if (firstCols != secondRows) {
        printf("bad-matrices\n");
        fclose(file);
        freeMatrix(first, firstRows);
        freeMatrix(second, secondRows);
        return 0;
    }

    multiplyMatrices(first, firstRows, firstCols, second, secondRows, secondCols, &result);

    printMatrix(result, firstRows, secondCols);

    freeMatrix(first, firstRows);
    freeMatrix(second, secondRows);
    freeMatrix(result, firstRows);
    
    fclose(file);
    return 0;
}
