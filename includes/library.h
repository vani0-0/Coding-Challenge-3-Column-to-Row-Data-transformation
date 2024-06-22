#ifndef __LIBRARY_H_INCLUDED
#define __LIBRARY_H_INCLUDED 1

#define ENGLISH "en-US"
#define FILIPINO "fl-PH"
#define SPANISH "es-ES"
#define GERMAN "de-DE"
#define FRENCH "fr-FR"
#define JAPANESE "ja-JP"
#define CHINESE "zh-CN"
#define ARABIC "ar-SA"
#define RUSSIAN "ru-RU"
#define PORTUGUESE "pt-BR"
#define ITALIAN "it-IT"
#define KOREAN "ko-KR"
#define HINDI "hi-IN"
#define TURKISH "tr-TR"
#define DUTCH "nl-NL"

#define MAX_LANGUAGE_CULTURE 6 // considering '\0' as all code has short code for language and country. ie: fl-PH
#define MAX_TEXT 128

typedef struct TRANSLATION
{
    char culture[MAX_LANGUAGE_CULTURE];
    char code[MAX_TEXT];
    char value[MAX_TEXT];
} TRANSLATION;

typedef struct WORD
{
    char code[MAX_TEXT];
    char value[MAX_TEXT];
} WORD;

typedef struct Lib *LIBRARY;

void InitializeLibrary(LIBRARY *lib, ...);
void AddWord(LIBRARY *lib, WORD word);
void AddTranslation(LIBRARY *lib, TRANSLATION translation);
void DisplayOriginal(LIBRARY lib);
void DisplayTransformed(LIBRARY lib);
void DestroyLibrary(LIBRARY library);

#endif // __LIBRARY_H_INCLUDED