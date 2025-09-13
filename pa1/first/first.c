#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// check if # is prime
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// check if # is trunctable prime
bool isRightTruncatablePrime(int n) {
    // og # prime?
    if (!isPrime(n)) {
        return false;
    }
    
    // check right truncation
    while (n > 0) {
        if (!isPrime(n)) {
            return false;
        }
        n /= 10; 
    }
    
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int count;
    fscanf(file, "%d", &count); 

    for (int i = 0; i < count; i++) {
        int num;
        fscanf(file, "%d", &num); 

        if (isRightTruncatablePrime(num)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }

    fclose(file);
    return 0;
}
