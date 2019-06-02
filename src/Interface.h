#pragma once
#include <windows.h>
#include "Dictionary.h"
#ifndef INTER_H
#define INTER_H
struct list* fMainProc(FILE* ned, char*** dictionary, int* dictionarylens);
void fOutput(HANDLE hSTDout, struct list*, struct dblist*);
FILE* fOpenfile(char*, char**);
FILE* fOpenfilew(char*, char*);
void fWrite_in_file(FILE*, struct list*);
void fChange(char*, struct dblist*, struct list*);
char* fChoose(char* wrd, char*** dictionary, int* dictionarylens);
//void fMemfree(char*** dict, int* dictlens, struct list* strings);
#endif