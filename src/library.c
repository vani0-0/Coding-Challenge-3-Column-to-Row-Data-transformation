#include "../includes/library.h"
#include "../includes/sll.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Lib
{
    NODEPTR languages; // a dynamic array of languages
    NODEPTR words;
    NODEPTR translations;
};

LIBRARY _initLib()
{
    LIBRARY lib = malloc(sizeof(LIBRARY));
    if (lib == NULL)
    {
        printf("Failed to allocate mem to library\n");
        return NULL;
    }

    lib->languages = NULL; // head of node
    lib->words = NULL;
    lib->translations = NULL;
    return lib;
}

bool _validate(const char *str)
{
    while (*str)
    {
        if (!isalpha(*str) && *str != '-')
            return false;
        str++;
    }
    return true;
}

// VARIADIC FUNCTION
void InitializeLibrary(LIBRARY *lib, ...)
{
    *lib = _initLib();
    if (*lib == NULL)
        return;

    va_list args;
    va_start(args, lib);
    const char *lang = va_arg(args, const char *);

    while (lang != NULL)
    {
        if (!_validate(lang))
            printf("\x1b[31mError: \"%s\" Invalid Culture\x1b[0m\n", lang);
        else
        {
            if (!validationTime((*lib)->languages, (char *)lang, STRING_TYPE))
                insert(&(*lib)->languages, (char *)lang, STRING_TYPE);
        }
        lang = va_arg(args, const char *);
    }
    va_end(args);
}

void AddWord(LIBRARY *lib, WORD word)
{
    if (!validationTime((*lib)->words, word.code, WORD_TYPE) &&
        !validationTime((*lib)->words, word.value, WORD_TYPE))
    {
        insert(&(*lib)->words, &word, WORD_TYPE);
    }
}

void AddTranslation(LIBRARY *lib, TRANSLATION translation)
{
    if (!validationTime((*lib)->words, translation.code, TRANSLATION_TYPE))
    {
        printf("\x1b[31mNot found Error: Word Code: \"%s\" does not exist.\x1b[0m\n", translation.code);
        return;
    }
    if (!validationTime((*lib)->languages, translation.culture, TRANSLATION_TYPE2))
    {
        printf("\x1b[31mNot found Error: Culture: \"%s\" does not exist.\x1b[0m\n", translation.culture);
        return;
    }
    insert(&(*lib)->translations, &translation, TRANSLATION_TYPE);
}

void DisplayOriginal(LIBRARY lib)
{
    printf("**ORIGINAL DATA**\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-16s | ", "Code", "Text");
    traverse(lib->languages, DISPLAY_ORIGINAL);
    printf("-------------------------------------------------------------------------------------------------------\n");
    DisplayOriginalCodeAndWord(lib->languages, lib->words, lib->translations);
    printf("**END OF ORIGINAL DATA**\n\n");
}

void DisplayTransformed(LIBRARY lib)
{
    printf("**TRANSFORMED DATA**\n");
    printf("--------------------------------------\n");
    printf("| %-5s | %-6s | %-16s |\n", "Code", "Culture", "Value");
    // printf("| Code \t| Culture \t\t| Value \t\t\t |");
    printf("--------------------------------------\n");
    traverse(lib->translations, DISPLAY_TRANSLATION);
    printf("**END OF TRANSFORMED DATA**\n\n");
}

void DestroyLibrary(LIBRARY library)
{
    destroyNode(library->languages);
    destroyNode(library->translations);
    destroyNode(library->words);
    free(library);
}