#include <stdio.h>
#include <string.h>
void generateMachineCode(const char *ir) {
    char buffer[256];
    strcpy(buffer, ir);
    char *line = strtok(buffer, "\n");
    printf("Pseudo-Machine Code:\n");  
    while (line != NULL) {
        if (strncmp(line, "LOAD", 4) == 0) {
            printf("MOV ACC, %s\n", line + 5);
        } else if (strncmp(line, "STORE", 5) == 0) {
            printf("MOV %s, ACC\n", line + 6);
        } else if (strncmp(line, "ADD", 3) == 0) {
            printf("ADD ACC, %s\n", line + 4);
        } else if (strncmp(line, "SUB", 3) == 0) {
            printf("SUB ACC, %s\n", line + 4);
        } else if (strncmp(line, "MUL", 3) == 0) {
            printf("MUL ACC, %s\n", line + 4);
        } else if (strncmp(line, "DIV", 3) == 0) {
            printf("DIV ACC, %s\n", line + 4);
        } else {
            printf("Unknown instruction: %s\n", line);
        }
        line = strtok(NULL, "\n");
    }
}

int main() {
    const char *ir = 
        "LOAD x\n"
        "ADD y\n"
        "MUL z\n"
        "STORE w\n";
    printf("Intermediate Representation:\n%s\n", ir);
    generateMachineCode(ir);
    return 0;
}
