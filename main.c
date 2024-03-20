#include <stdio.h>
#include <stdlib.h>
#include "translator.h"
#include "translator.c"

int main(int argc, char *argv[]) {
    if(argc<=2){
        printf("Wrong number of parameters");
        return 2;
    }
    enum error_t error;
    struct word_t** str=read_words(*(argv+1),&error);
    if(error==ERROR_FILE_IO) {
        printf("Failed to open file");
        return 1;
    } else if(error==ERROR_MEMORY){
        printf("Failed to allocate memory");
        return 8;
    }

    for (int i = 2; i < argc; i++) {
        char** tl =translate_words(str,1,*(argv+i));
        if(tl==NULL){
            printf("Failed to allocate memory");
            delete_words(str);
            return 8;
        }
        if(*tl==NULL){
            printf("Word not found\n");
        } else{
            printf("%s\n",*tl);
        }
        free(tl);
    }
    delete_words(str);
    return 0;
}

