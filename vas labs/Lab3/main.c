#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iconv.h>

#define MAX_ENTRY_LENGTH 1024
#define MAX_FIELD_LENGTH 256
#define COMPARE_LENGTH 5

struct bib_entry {
    char author[MAX_FIELD_LENGTH];
    char title[MAX_FIELD_LENGTH];
    char publisher[MAX_FIELD_LENGTH];
    char year[MAX_FIELD_LENGTH];
    char full_entry[MAX_ENTRY_LENGTH];
};

struct tnode {
    struct bib_entry entry;
    struct tnode *lchild, *rchild;
};

int strncmp_cp1251(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            char c1 = tolower((unsigned char)s1[i]);
            char c2 = tolower((unsigned char)s2[i]);
            if (c1 != c2) {
                return c1 - c2;
            }
        }
        if (s1[i] == '\0' || s2[i] == '\0') {
            break;
        }
    }
    return 0;
}

struct tnode *tree_insert(struct tnode *p, struct bib_entry entry) {
    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        if (p == NULL) {
            printf("Cannot allocate memory\n");
            exit(1);
        }
        p->entry = entry;
        p->lchild = p->rchild = NULL;
        return p;
    }

    int cmp_author = strncmp_cp1251(entry.author, p->entry.author, COMPARE_LENGTH);
    if (cmp_author < 0) {
        p->lchild = tree_insert(p->lchild, entry);
    } 
    else if (cmp_author > 0) {
        p->rchild = tree_insert(p->rchild, entry);
    } 
    else {

        int cmp_title = strncmp_cp1251(entry.title, p->entry.title, COMPARE_LENGTH);
        if (cmp_title < 0) {
            p->lchild = tree_insert(p->lchild, entry);
        } 
        else if (cmp_title > 0) {
            p->rchild = tree_insert(p->rchild, entry);
        } 
        else {

            int cmp_year = strcmp(entry.year, p->entry.year);
            if (cmp_year < 0) {
                p->lchild = tree_insert(p->lchild, entry);
            } 
            else {
                p->rchild = tree_insert(p->rchild, entry);
            }
        }
    }
    return p;
}

void tree_print(struct tnode *p, FILE *output) {
    if (p != NULL) {
        tree_print(p->lchild, output);
        fprintf(output, "%s\n", p->entry.full_entry);
        tree_print(p->rchild, output);
    }
}

void tree_free(struct tnode *p) {
    if (p != NULL) {
        tree_free(p->lchild);
        tree_free(p->rchild);
        free(p);
    }
}

void parse_bib_file(FILE *file, struct tnode **root) {
    char line[MAX_ENTRY_LENGTH];
    struct bib_entry current_entry = {0};
    int in_entry = 0;
    char *entry_start = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '%' || line[0] == '\n') continue;

        if (line[0] == '@') {
            if (in_entry && entry_start != NULL) {

                strncpy(current_entry.full_entry, entry_start, MAX_ENTRY_LENGTH);
                *root = tree_insert(*root, current_entry);
                memset(&current_entry, 0, sizeof(current_entry));
            }
            in_entry = 1;
            entry_start = line;
        }

        if (in_entry) {
            if (strstr(line, "author =")) {
                sscanf(line, " author = { %[^}] }", current_entry.author);
            } 
            else if (strstr(line, "title =")) {
                sscanf(line, " title = { %[^}] }", current_entry.title);
            } 
            else if (strstr(line, "publisher =")) {
                sscanf(line, " publisher = { %[^}] }", current_entry.publisher);
            } 
            else if (strstr(line, "year =")) {
                sscanf(line, " year = { %[^}] }", current_entry.year);
            }
        }
    }

    if (in_entry && entry_start != NULL) {
        strncpy(current_entry.full_entry, entry_start, MAX_ENTRY_LENGTH);
        *root = tree_insert(*root, current_entry);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s output_file input_file1 [input_file2 ...]\n", argv[0]);
        return 1;
    }

    struct tnode *root = NULL;
    FILE *output_file = fopen(argv[1], "w");
    if (output_file == NULL) {
        perror("Cannot open output file");
        return 1;
    }
	int i;
    for (i = 2; i < argc; i++) {
        FILE *input_file = fopen(argv[i], "r");
        if (input_file == NULL) {
            fprintf(stderr, "Cannot open input file: %s\n", argv[i]);
            continue;
        }

        parse_bib_file(input_file, &root);
        fclose(input_file);
    }

    tree_print(root, output_file);
    fclose(output_file);

    tree_free(root);

    return 0;
}
