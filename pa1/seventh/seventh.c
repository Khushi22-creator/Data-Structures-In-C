#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argumentCount, char **arguments) {
    // varibale to hold last char's index
    int length = 0;

    for (int index = 1; index < argumentCount; index++) {
        length = strlen(arguments[index]);

        // print last character of  current argument if not empty
        if (length > 0) {
            putchar(arguments[index][length - 1]);
        }
    }
    
    putchar('\n'); 
    return 0;
}
