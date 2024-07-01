#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef enum {NUMBER, ADD, SUBTRACT, MULTIPLY, DIVIDE, EXPONENT, LPAREN, RPAREN, END} TokenType;

typedef struct {
    TokenType type;
    double value;
} Token;

typedef struct Node {
    TokenType type;
    double value;
    struct Node *left;
    struct Node *right;
} Node;

// Function prototypes
Token get_next_token(const char **expr);
Node* expression(const char **expr);
Node* term(const char **expr);
Node* factor(const char **expr);
Node* exponent(const char **expr);
double evaluate(Node *node);
void free_tree(Node *node);

// Lexer: Convert input string to tokens
Token get_next_token(const char **expr) {
    while (isspace(**expr)) (*expr)++;
    if (**expr == '\0') return (Token){END, 0};
    if (**expr == '+') return (Token){ADD, 0}; (*expr)++;
    if (**expr == '-') return (Token){SUBTRACT, 0}; (*expr)++;
    if (**expr == '*') return (Token){MULTIPLY, 0}; (*expr)++;
    if (**expr == '/') return (Token){DIVIDE, 0}; (*expr)++;
    if (**expr == '^') return (Token){EXPONENT, 0}; (*expr)++;
    if (**expr == '(') return (Token){LPAREN, 0}; (*expr)++;
    if (**expr == ')') return (Token){RPAREN, 0}; (*expr)++;
    if (isdigit(**expr) || **expr == '.') {
        char *end;
        double value = strtod(*expr, &end);
        *expr = end;
        return (Token){NUMBER, value};
    }
    fprintf(stderr, "Unexpected character: %c\n", **expr);
    exit(EXIT_FAILURE);
}

// Recursive Descent Parser: Build AST based on tokens
Node* expression(const char **expr) {
    Node *node = term(expr);
    Token token = get_next_token(expr);
    while (token.type == ADD || token.type == SUBTRACT) {
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->type = token.type;
        new_node->left = node;
        new_node->right = term(expr);
        node = new_node;
        token = get_next_token(expr);
    }
    (*expr)--;
    return node;
}

Node* term(const char **expr) {
    Node *node = exponent(expr);
    Token token = get_next_token(expr);
    while (token.type == MULTIPLY || token.type == DIVIDE) {
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->type = token.type;
        new_node->left = node;
        new_node->right = exponent(expr);
        node = new_node;
        token = get_next_token(expr);
    }
    (*expr)--;
    return node;
}

Node* exponent(const char **expr) {
    Node *node = factor(expr);
    Token token = get_next_token(expr);
    if (token.type == EXPONENT) {
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->type = token.type;
        new_node->left = node;
        new_node->right = exponent(expr);
        node = new_node;
    } else {
        (*expr)--;
    }
    return node;
}

Node* factor(const char **expr) {
    Token token = get_next_token(expr);
    if (token.type == NUMBER) {
        Node *node = (Node*)malloc(sizeof(Node));
        node->type = NUMBER;
        node->value = token.value;
        node->left = node->right = NULL;
        return node;
    } else if (token.type == LPAREN) {
        Node *node = expression(expr);
        token = get_next_token(expr);
        if (token.type != RPAREN) {
            fprintf(stderr, "Mismatched parentheses\n");
            exit(EXIT_FAILURE);
        }
        return node;
    } else {
        fprintf(stderr, "Unexpected token\n");
        exit(EXIT_FAILURE);
    }
}

// Evaluate AST
double evaluate(Node *node) {
    if (node->type == NUMBER) return node->value;
    double left = evaluate(node->left);
    double right = evaluate(node->right);
    switch (node->type) {
        case ADD: return left + right;
        case SUBTRACT: return left - right;
        case MULTIPLY: return left * right;
        case DIVIDE: return left / right;
        case EXPONENT: return pow(left, right);
        default: fprintf(stderr, "Unknown node type\n"); exit(EXIT_FAILURE);
    }
}

// Free AST
void free_tree(Node *node) {
    if (node) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}

int main() {
    const char *expression_str = "3 + 5 * (2 ^ 3 - 1)";
    Node *root = expression(&expression_str);
    double result = evaluate(root);
    printf("Result: %f\n", result);
    free_tree(root);
    return 0;
}

