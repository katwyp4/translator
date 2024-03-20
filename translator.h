#ifndef TRANSLATOR_H
#define TRANSLATOR_H

enum error_t{
    ERROR_OK,
    ERROR_INCORRECT_PARAMETERS,
    ERROR_FILE_IO,
    ERROR_MEMORY
};

struct word_t {
    char* text_pl;
    char* text_en;
};

struct word_t** read_words(const char* filename, enum error_t* errcode);
void delete_words(struct word_t** tab);

char** translate_words( struct word_t** tab, int n, ...);

#endif
