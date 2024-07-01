#include <stdio.h>
#include <ctype.h>

const char *input;
char lookahead;

void error() {
    printf("Syntax Error\n");
}

void match(char expected) {
    if (lookahead == expected) {
        lookahead = *++input;
    } else {
        error();
    }
}

void E();
void E_prime();
void T();
void T_prime();
void F();

void E() {
    printf("Enter E\n");
    T();
    E_prime();
    printf("Exit E\n");
}

void E_prime() {
    printf("Enter E'\n");
    if (lookahead == '+') {
        match('+');
        T();
        E_prime();
    }
    printf("Exit E'\n");
}

void T() {
    printf("Enter T\n");
    F();
    T_prime();
    printf("Exit T\n");
}

void T_prime() {
    printf("Enter T'\n");
    if (lookahead == '*') {
        match('*');
        F();
        T_prime();
    }
    printf("Exit T'\n");
}

void F() {
    printf("Enter F\n");
    if (lookahead == '(') {
        match('(');
        E();
        match(')');
    } else if (isalpha(lookahead)) {
        match(lookahead);  // match an identifier
    } else {
        error();
    }
    printf("Exit F\n");
}

void parse(const char *expr) {
    input = expr;
    lookahead = *input;
    E();
    if (lookahead != '\0') {
        error();
    }
    printf("Parsing Successful\n");
}

int main() {
    const char *expr = "id + id * id";
    parse(expr);
    return 0;
}

