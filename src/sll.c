#include "../includes/sll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    union
    {
        char *str;
        WORD *word;
        TRANSLATION *translation;
    } data;
    NODEPTR next;
};

void traverse(NODEPTR head, unsigned short option)
{
    NODEPTR current = head;
    while (current != NULL)
    {
        switch (option)
        {
        case DISPLAY_ORIGINAL:
            printf(" %-16s|  ", current->data.str);
            break;
        case DISPLAY_TRANSLATION:
        {
            TRANSLATION *translate = current->data.translation;
            printf("| %-6s | %-6s | %-16s |", translate->code, translate->culture, translate->value);
            printf("\n");
            break;
        }

        default:
            break;
        }
        current = current->next;
    }
    printf("\n");
}

void insert(NODEPTR *head, void *data, TYPES type)
{
    NODEPTR node = (NODEPTR)malloc(sizeof(struct Node));

    if (node == NULL)
    {
        printf("Failed to create new node.\n");
        return;
    }

    node->next = NULL;

    switch (type)
    {
    case STRING_TYPE:
        node->data.str = malloc(strlen((char *)data) + 1);
        if (node->data.str == NULL)
        {
            free(node);
            printf("Failed to allocate memory for data.\n");
            return;
        }
        strcpy(node->data.str, (char *)data);
        break;

    case WORD_TYPE:
    {
        WORD *word = (WORD *)data;
        node->data.word = (WORD *)malloc(sizeof(WORD));
        if (node->data.word == NULL)
        {
            free(node);
            printf("Failed to allocate memory for data.\n");
            return;
        }
        strcpy(node->data.word->code, word->code);
        strcpy(node->data.word->value, word->value);
        break;
    }
    case TRANSLATION_TYPE:
        TRANSLATION *translation = (TRANSLATION *)data;
        node->data.translation = (TRANSLATION *)malloc(sizeof(TRANSLATION));
        if (node->data.translation == NULL)
        {
            free(node);
            printf("Failed to allocate memory for data.\n");
            return;
        }
        strcpy(node->data.translation->code, translation->code);
        strcpy(node->data.translation->value, translation->value);
        strcpy(node->data.translation->culture, translation->culture);
        break;

    default:
        printf("Unsupported data type.\n");
        free(node);
        return;
    }

    if (*head == NULL) // Beginning of list
        *head = node;
    else
    {
        NODEPTR last = *head;
        // Insert new node at the end of list
        while (last->next != NULL)
            last = last->next;
        last->next = node;
    }
}

bool validationTime(NODEPTR head, char *target, TYPES type)
{
    bool res = false;
    NODEPTR current = head;
    while (current != NULL)
    {
        switch (type)
        {
        case STRING_TYPE:
            if (strcmp(current->data.str, target) == 0)
            {
                printf("\x1b[31mError: \"%s\" Culture already exists\x1b[0m\n", target);
                res = true;
            }
            break;
        case WORD_TYPE:
            if (strcmp(current->data.word->code, target) == 0)
            {
                printf("\x1b[31mError: \"%s\" Code already exists\x1b[0m\n", target);
                res = true;
            }
            if (strcmp(current->data.word->value, target) == 0)
            {
                printf("\x1b[31mError: \"%s\" Value already exists\x1b[0m\n", target);
                res = true;
            }
            break;
        case TRANSLATION_TYPE:
            if (strcmp(current->data.word->code, target) == 0)
            {
                res = true;
            }
            break;
        case TRANSLATION_TYPE2:
            if (strcmp(current->data.str, target) == 0)
            {
                res = true;
            }
            break;
        default:
            printf("Unsupported data type.\n");
            return true;
        }

        current = current->next;
    }

    return res;
}

void DisplayOriginalCodeAndWord(NODEPTR language, NODEPTR words, NODEPTR translations)
{
    NODEPTR currentWord = words;
    while (currentWord != NULL)
    {
        WORD *cWordData = currentWord->data.word;
        NODEPTR currentLang = language;
        printf("| %-5s | %-16s |", cWordData->code, cWordData->value);

        while (currentLang != NULL)
        {
            char *cLangStr = currentLang->data.str;
            NODEPTR currentTran = translations;
            bool found = false;

            while (currentTran != NULL)
            {
                TRANSLATION *cTransData = currentTran->data.translation;
                bool isCultureMatch = strcmp(cLangStr, cTransData->culture) == 0;
                if (isCultureMatch)
                {
                    bool isSameCode = strcmp(cWordData->code, cTransData->code) == 0;
                    if (isSameCode)
                    {
                        printf(" %-16s | ", cTransData->value);
                        found = true;
                        break;
                    }
                }
                currentTran = currentTran->next;
            }

            if (!found)
                printf(" %-16s | ", "");
            currentLang = currentLang->next;
        }

        printf("\n");
        currentWord = currentWord->next;
    }
}

void destroyNode(NODEPTR head)
{
    NODEPTR current = head;
    while (current != NULL)
    {
        NODEPTR nextNode = current->next;
        if (current->data.str)
            free(current->data.str);
        if (current->data.translation)
            free(current->data.translation);
        if (current->data.word)
            free(current->data.word);
        free(current);
        current = nextNode;
    }
}