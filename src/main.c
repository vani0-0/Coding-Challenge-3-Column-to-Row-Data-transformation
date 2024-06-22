#include "../includes/library.h"
#include <stdio.h>

int main()
{
    // CREATE LIBRARY
    LIBRARY library = NULL;
    InitializeLibrary(&library, FILIPINO, CHINESE, ENGLISH, JAPANESE, NULL);

    AddWord(&library, (WORD){"001", "HELLO"});

    WORD word = {"002", "GOOD"};
    AddWord(&library, word);

    AddWord(&library, (WORD){"003", "BYE"});

    AddTranslation(&library, (TRANSLATION){ENGLISH, "001", "HELLO"});
    AddTranslation(&library, (TRANSLATION){FILIPINO, "001", "KUMUSTA"});
    AddTranslation(&library, (TRANSLATION){CHINESE, "002", "hao"});
    AddTranslation(&library, (TRANSLATION){CHINESE, "003", "huai"});
    AddTranslation(&library, (TRANSLATION){JAPANESE, "001", "OHAYO"});

    // ORIGINAL
    DisplayOriginal(library);

    // IMPAKTO
    DisplayTransformed(library);

    DestroyLibrary(library);
    return 0;
}