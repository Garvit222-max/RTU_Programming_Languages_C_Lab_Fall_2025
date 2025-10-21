// Name Garvit YourStudentID 241ADB140
// Compile with: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// -----------------------------
// GLOBAL VARIABLES
// -----------------------------
const char *src;   // input text
int pos = 1;       // current position (1-based)
int error_pos = 0; // if nonzero -> first error position

// -----------------------------
// FUNCTION DECLARATIONS
// -----------------------------
long long parse_expr();  // expression = term { ('+' | '-') term }
long long parse_term();  // term = NUMBER
void skip_spaces();

// -----------------------------
// ERROR HANDLER
// -----------------------------
void fail(int p) {
    if (!error_pos) error_pos = p;
}

// -----------------------------
// TOKEN HELPERS
// -----------------------------
void skip_spaces() {
    while (*src && isspace((unsigned char)*src)) {
        src++;
        pos++;
    }
}

// parse a number (only integers)
int parse_number(long long *out) {
    skip_spaces();
    if (!isdigit((unsigned char)*src)) {
        fail(pos);
        return 0;
    }

    long long val = 0;
    while (isdigit((unsigned char)*src)) {
        val = val * 10 + (*src - '0');
        src++;
        pos++;
    }
    *out = val;
    return 1;
}

// -----------------------------
// PARSER FUNCTIONS
// -----------------------------
long long parse_term() {
    long long val;
    if (!parse_number(&val)) {
        fail(pos);
        return 0;
    }
    return val;
}

long long parse_expr() {
    long long value = parse_term();
    skip_spaces();

    while (*src == '+' || *src == '-') {
        char op = *src;
        src++; pos++;
        skip_spaces();

        long long rhs = parse_term();

        if (error_pos) return 0; // stop if error found

        if (op == '+') value += rhs;
        else value -= rhs;

        skip_spaces();
    }
    return value;
}

// -----------------------------
// MAIN
// -----------------------------
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s input.txt\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("File open failed");
        return 1;
    }

    // read full file into memory
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = malloc(len + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(f);
        return 1;
    }

    size_t n = fread(buffer, 1, len, f);
    buffer[n] = '\0';
    fclose(f);

    src = buffer;
    pos = 1;
    error_pos = 0;

    long long result = parse_expr();
    skip_spaces();

    if (*src != '\0' && !error_pos) {
        fail(pos);
    }

    if (error_pos)
        printf("ERROR:%d\n", error_pos);
    else
        printf("%lld\n", result);

    free(buffer);
    return 0;
}
