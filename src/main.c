#include "../includes/library.h"
#include <stdio.h>

int main()
{
    // CREATE LIBRARY
    LIBRARY library = NULL;
    InitializeLibrary(&library, CHINESE, ENGLISH, JAPANESE, KOREAN, NULL);

    AddWord(&library, (WORD){"001", "HELLO"});

    WORD word = {"002", "GOOD"};
    AddWord(&library, word);
    AddWord(&library, (WORD){"69", "OK"});

    AddWord(&library, (WORD){"003", "BYE"});

    AddTranslation(&library, (TRANSLATION){ENGLISH, "001", "HELLO"});
    AddTranslation(&library, (TRANSLATION){FILIPINO, "001", "KUMUSTA"});
    AddTranslation(&library, (TRANSLATION){CHINESE, "002", "hao"});
    AddTranslation(&library, (TRANSLATION){CHINESE, "003", "huai"});
    AddTranslation(&library, (TRANSLATION){JAPANESE, "001", "OHAYO"});
    AddTranslation(&library, (TRANSLATION){KOREAN, "69", "GWENCHANA"});
    AddTranslation(&library, (TRANSLATION){FILIPINO, "69", "AYOS"});

    // ORIGINAL
    DisplayOriginal(library);

    // IMPAKTO
    DisplayTransformed(library);

    DestroyLibrary(library);
    return 0;
}