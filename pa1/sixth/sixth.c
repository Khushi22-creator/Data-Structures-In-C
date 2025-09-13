#include <stdio.h>
#include <string.h>
#include <ctype.h>

// check is char is vowel
int isVowel(char ch) {
    char lower_ch = tolower(ch);
    return (lower_ch == 'a' || lower_ch == 'e' || lower_ch == 'i' || lower_ch == 'o' || lower_ch == 'u');
}

void pigLatin(char *word) {
    int len = strlen(word);
    if (isVowel(word[0])) {
        // ff the word starts with vowel, add "yay" in end
        printf("%syay", word);
    } else {
        int vowel_index = -1;
        for (int i = 0; i < len; i++) {
            if (isVowel(word[i])) {
                vowel_index = i;
                break;
            }
        }
        if (vowel_index != -1) {
            // move letters before first vowel to end and add ay
            printf("%s", word + vowel_index);  
            for (int i = 0; i < vowel_index; i++) {
                putchar(word[i]);  
            }
            printf("ay");
        } else {
            // if no vowel found:
            printf("%say", word);  
        }
    }
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        pigLatin(argv[i]);  
        if (i < argc - 1) {
            printf(" ");  // space
        }
    }
    printf("\n");  
    return 0;
}
