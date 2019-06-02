#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H
#define STRDICT 50
#define STRTEXT 10000
#define DICT 37 
struct incs {
	int num;
	int count;
};
struct couple {
	char* first;
	char* second;
};
struct result {
	char** arr;
	int length;
};
void fInit(char***, int*);
char* fCheck(char* word, char***, int*);
void fChange(char* word);
struct result fFind(char* word, char*** dictionary, int* dictionarylen);
#endif