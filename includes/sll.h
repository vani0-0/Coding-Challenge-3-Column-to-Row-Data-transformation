/*
    SINGLE LINKED LIST

    AUTHOR: VAN.__.

 */

#ifndef __SLL_H_INCLUDED
#define __SLL_H_INCLUDED 1
#include "library.h"

#include <stdbool.h>

#define DISPLAY_ORIGINAL 1
#define DISPLAY_TRANSLATION 4

typedef enum
{
    STRING_TYPE,
    WORD_TYPE,
    TRANSLATION_TYPE,
    TRANSLATION_TYPE2
} TYPES;

typedef struct Node *NODEPTR;

void DisplayOriginalCodeAndWord(NODEPTR language, NODEPTR words, NODEPTR translations);

void traverse(NODEPTR head, unsigned short option);
bool validationTime(NODEPTR head, char *target, TYPES type);
void insert(NODEPTR *head, void *lang, TYPES type);
void destroyNode(NODEPTR head);

#endif // __SLL_H_INCLUDED