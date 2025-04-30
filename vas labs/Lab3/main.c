#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iconv.h>

#define MAX_LINE 1024
#define MAX_FIELD 256
#define COMPARE_LEN 5
#define MAX_PATH 1024

typedef struct Book {
    char author[MAX_FIELD];
    char title[MAX_FIELD];
    char publisher[MAX_FIELD];
    int year;
    struct Book *left;
    struct Book *right;
} Book;

int isBibFile(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return dot && !strcmp(dot, ".bib");
}

//////////////////////////////////////////////////

Book* createBook(const char *author, const char *title, const char *publisher, int year) {
    Book *newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL) {
        exit(1);
    }
    
    strncpy(newBook->author, author, MAX_FIELD - 1);
    newBook->author[MAX_FIELD - 1] = '\0';
    strncpy(newBook->title, title, MAX_FIELD - 1);
    newBook->title[MAX_FIELD - 1] = '\0';
    strncpy(newBook->publisher, publisher, MAX_FIELD - 1);
    newBook->publisher[MAX_FIELD - 1] = '\0';
    newBook->year = year;
    newBook->left = NULL;
    newBook->right = NULL;
    
    return newBook;
}

//////////////////////////////////////////////////

int compareStrings(const char *s1, const char *s2) {
    return strncmp(s1, s2, COMPARE_LEN);
}

Book* insertBook(Book *root, Book *newBook) {
    if (root == NULL) {
        return newBook;
    }
    
    int cmp = compareStrings(newBook->author, root->author);
    if (cmp < 0) {
        root->left = insertBook(root->left, newBook);
    } else if (cmp > 0) {
        root->right = insertBook(root->right, newBook);
    } else {
        // if authors ==
        cmp = compareStrings(newBook->title, root->title);
        if (cmp < 0) {
            root->left = insertBook(root->left, newBook);
        } else {
            root->right = insertBook(root->right, newBook);
        }
    }
    
    return root;
}

void freeTree(Book *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void writeTreeToFile(FILE *output, Book *root) {
    if (root != NULL) {
        writeTreeToFile(output, root->left);
        fprintf(output, "Author: %s\n", root->author);
        fprintf(output, "Title: %s\n", root->title);
        fprintf(output, "Publisher: %s\n", root->publisher);
        fprintf(output, "Year: %d\n\n", root->year);
        writeTreeToFile(output, root->right);
    }
}

//////////////////////////////////////////////////

void searchInTree(Book *root, const char *searchStr) {
    if (root == NULL) {
        return;
    }
    
    int cmp = compareStrings(searchStr, root->author);
    if (cmp == 0) {
        printf("Found: %s - %s\n", root->author, root->title);
    }
    
    cmp = compareStrings(searchStr, root->title);
    if (cmp == 0) {
        printf("Found: %s - %s\n", root->author, root->title);
    }
    
    if (compareStrings(searchStr, root->author) <= 0 || compareStrings(searchStr, root->title) <= 0) {
        searchInTree(root->left, searchStr);
    }
    
    if (compareStrings(searchStr, root->author) >= 0 || compareStrings(searchStr, root->title) >= 0) {
        searchInTree(root->right, searchStr);
    }
}

void processBibFile(const char *filename, Book **root) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File opening error: %s\n", filename);
        return;
    }
    
    char line[MAX_LINE];
    char currentAuthor[MAX_FIELD] = "";
    char currentTitle[MAX_FIELD] = "";
    char currentPublisher[MAX_FIELD] = "";
    int currentYear = 0;
    
    while (fgets(line, MAX_LINE, file) != NULL) {

        char *trimmedLine = line;
        while (isspace(*trimmedLine)) trimmedLine++;
        char *end = trimmedLine + strlen(trimmedLine) - 1;
        while (end > trimmedLine && isspace(*end)) end--;
        *(end + 1) = '\0';

        if (strlen(trimmedLine) == 0 || trimmedLine[0] == '%') {
            continue;
        }
        
        if (strstr(trimmedLine, "author") == trimmedLine) {
            char *start = strchr(trimmedLine, '{');
            if (start != NULL) {
                char *end = strrchr(trimmedLine, '}');
                if (end != NULL) {
                    *end = '\0';
                    strncpy(currentAuthor, start + 1, MAX_FIELD - 1);
                    currentAuthor[MAX_FIELD - 1] = '\0';
                }
            }
        } else if (strstr(trimmedLine, "title") == trimmedLine) {
            char *start = strchr(trimmedLine, '{');
            if (start != NULL) {
                char *end = strrchr(trimmedLine, '}');
                if (end != NULL) {
                    *end = '\0';
                    strncpy(currentTitle, start + 1, MAX_FIELD - 1);
                    currentTitle[MAX_FIELD - 1] = '\0';
                }
            }
        } else if (strstr(trimmedLine, "publisher") == trimmedLine) {
            char *start = strchr(trimmedLine, '{');
            if (start != NULL) {
                char *end = strrchr(trimmedLine, '}');
                if (end != NULL) {
                    *end = '\0';
                    strncpy(currentPublisher, start + 1, MAX_FIELD - 1);
                    currentPublisher[MAX_FIELD - 1] = '\0';
                }
            }
        } else if (strstr(trimmedLine, "year") == trimmedLine) {
            char *start = strchr(trimmedLine, '{');
            if (start != NULL) {
                char *end = strrchr(trimmedLine, '}');
                if (end != NULL) {
                    *end = '\0';
                    currentYear = atoi(start + 1);
                }
            }
        } else if (strcmp(trimmedLine, "}") == 0) {
        	
            if (strlen(currentAuthor) > 0 && strlen(currentTitle) > 0) {
                Book *newBook = createBook(currentAuthor, currentTitle, currentPublisher, currentYear);
                *root = insertBook(*root, newBook);
                
                currentAuthor[0] = '\0';
                currentTitle[0] = '\0';
                currentPublisher[0] = '\0';
                currentYear = 0;
            }
        }
    }
    
    fclose(file);
}

//////////////////////////////////////////////////

void processDirectory(const char *dirname, Book **root) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char path[MAX_PATH];

    if ((dir = opendir(dirname)) == NULL) {
        fprintf(stderr, "No such directory: %s\n", dirname);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(path, MAX_PATH, "%s/%s", dirname, entry->d_name);
        
        if (stat(path, &statbuf)) {
            fprintf(stderr, "File opening error: %s\n", path);
            continue;
        }

        if (S_ISREG(statbuf.st_mode) && isBibFile(entry->d_name)) {
            printf("File processing: %s\n", path);
            processBibFile(path, root);
        }
    }

    closedir(dir);
}

//////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("No arguments");
        return 1;
    }
    
    const char *outputFilename = argv[1];
    const char *dirname = argv[2];
    Book *root = NULL;

    processDirectory(dirname, &root);
    
    FILE *output = fopen(outputFilename, "w");
    if (output == NULL) {
        freeTree(root);
        return 1;
    }
    
    writeTreeToFile(output, root);
    fclose(output);
    
    printf("Search: ", COMPARE_LEN);
    char searchStr[MAX_FIELD];
    fgets(searchStr, MAX_FIELD, stdin);
    searchStr[strcspn(searchStr, "\n")] = '\0';
    
    printf("Results:\n");
    searchInTree(root, searchStr);
    
    freeTree(root);
    
    return 0;
}

/////////// Build ///////////
// gcc -o main main.c -liconv

////////// Execute //////////
// ./main output.txt .bib
