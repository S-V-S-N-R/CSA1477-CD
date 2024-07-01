#include <stdio.h>

// Function to convert a left-recursive grammar
void eliminateLeftRecursion() {
    printf("Original Grammar:\n");
    printf("S ? Sa | b\n");

    // New grammar without left recursion
    printf("\nConverted Grammar:\n");
    printf("S ? bS'\n");
    printf("S' ? aS' | e\n");
}

int main() {
    eliminateLeftRecursion();
    return 0;
}

