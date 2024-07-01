#include <stdio.h>
#include <ctype.h>

// Function prototypes
void countCharactersWordsLines(FILE *file, int *characters, int *words, int *lines);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int characters = 0, words = 0, lines = 0;
    countCharactersWordsLines(file, &characters, &words, &lines);

    fclose(file);

    printf("Characters: %d\n", characters);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);

    return 0;
}

void countCharactersWordsLines(FILE *file, int *characters, int *words, int *lines) {
    char c;
    int inWord = 0;

    while ((c = fgetc(file)) != EOF) {
        (*characters)++;
        if (c == '\n') {
            (*lines)++;
        }
        if (isspace(c)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            (*words)++;
        }
    }

    // If the last line does not end with a newline character, increment the line count
    if (*characters > 0 && c != '\n') {
        (*lines)++;
    }
}

