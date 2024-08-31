#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

void rotate_char(char *ch, int n) {
    if (isalpha(*ch)) {
        char base = islower(*ch) ? 'a' : 'A';
        *ch = (char)(((*ch - base + n) % 26 + 26) % 26 + base);
    } else if (isdigit(*ch)) {
        char base = '0';
        *ch = (char)(((*ch - base + n) % 10 + 10) % 10 + base);
    }
}

void create_file(const char *file_name, const char *content) {
    struct stat buffer;
    if (stat(file_name, &buffer) == 0) {
        printf("File already exists\n");
        return;
    }

    FILE *f = fopen(file_name, "w");
    if (!f) {
        perror("Error opening file");
        return;
    }

    fprintf(f, "%s", content);
    printf("File created successfully\n");
}

void read_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        perror("File not found");
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (strstr(file_name, "flag")) {
            rotate_char(&ch, rand() % 26);
        }
        putchar(ch);
    }
    putchar('\n');
}

int main() {
    read_file("flag.txt");
    return 0;
}