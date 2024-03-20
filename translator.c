#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "translator.h"

int count_lines(FILE *file) {
    int lines = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lines++;
        }
    }
    return lines;
}

struct word_t** allocate_memory(int count) {
    struct word_t** words = malloc(sizeof(struct word_t*) * (count + 1));
    if (words == NULL) {
        return NULL;
    }
    *(words + count) = NULL;
    return words;
}

int read_file(const char* filename, struct word_t** words, int count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char buffer[100];
    for (int i = 0; i < count; i++) {
        *(words + i) = malloc(sizeof(struct word_t));
        if (*(words + i) == NULL) {
            fclose(file);
            return 0;
        }
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            fclose(file);
            return 0;
        }
        char* txt1 = strtok(buffer, " ");
        char* txt2 = strtok(NULL, "\n");
        (*(words + i))->text_pl = strdup(txt1);
        (*(words + i))->text_en = strdup(txt2);
        if ((*(words + i))->text_pl == NULL || (*(words + i))->text_en == NULL) {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

struct word_t** read_words(const char* filename, enum error_t* errcode) {
    if (filename == NULL || errcode == NULL) {
        if (errcode != NULL) {
            *errcode = ERROR_INCORRECT_PARAMETERS;
        }
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        if (errcode != NULL) {
            *errcode = ERROR_FILE_IO;
        }
        return NULL;
    }

    int lines = count_lines(file);
    fclose(file);

    struct word_t** words = allocate_memory(lines);
    if (words == NULL) {
        *errcode = ERROR_MEMORY;
        return NULL;
    }

    int success = read_file(filename, words, lines);
    if (!success) {
        delete_words(words);
        *errcode = ERROR_MEMORY;
        return NULL;
    }

    *errcode = ERROR_OK;
    return words;
}
void delete_words(struct word_t** tab) {
    if (tab != NULL) {
        int i = 0;
        while (*(tab+i)) {
            free((*(tab+i))->text_pl);
            free((*(tab+i))->text_en);
            free(*(tab+i));
            i++;
        }
        free(tab);
    }
}
char** translate_words( struct word_t** tab, int n, ...) {
    if (tab == NULL || n <= 0) {
        return NULL;
    }
    char ** translate= malloc(sizeof (char *) *(n+1));
    if(translate==NULL){
        return NULL;
    }
    va_list args;
    va_start(args,n);
    for (int i = 0; i < n; ++i) {
        char * one_w= va_arg(args,char *);
        for (int j = 0; *(tab+j) != NULL; ++j) {
            if(strcmp((*(tab+j))->text_pl ,one_w)==0){
                *(translate+i)=(*(tab+j))->text_en;
                break;

            } else {
                *(translate+i)=NULL;
            }
        }
    }
    va_end(args);
    *(translate+n)=NULL;
    return translate;
}