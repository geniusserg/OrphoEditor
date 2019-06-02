#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define STRDICT 50
#define STRTEXT 1000
#define DICT 37
#include "Dictionary.h"

struct result fFind(char* word, char*** dictionary, int* dictionarylen) {
	int length = strlen(word);
	char** arrReturn = (char**)malloc(sizeof(char*) * 100 * length);
	int iter = 0;
	struct couple* splits = (struct couple*)malloc(sizeof(struct couple)*(length + 1));
	for (int i = 0; i < length + 1; i++) {
		if (i == 0) { (splits)->first = (char*)malloc(sizeof(char) * 2); strcpy((splits)->first, ""); }
		else { (splits + i)->first = (char*)malloc(sizeof(char)*(i + 1)); for (int j = 0; j < i; j++) { *((splits + i)->first + j) = *(word + j); } *((splits + i)->first + i) = '\0'; }
		if (i == length) { (splits + i)->second = (char*)malloc(sizeof(char)); strcpy((splits + i)->second, " "); }
		else { (splits + i)->second = (char*)malloc(sizeof(char)*(length - i + 1)); for (int j = 0; j < length - i; j++) { *((splits + i)->second + j) = *(word + i + j); } *((splits + i)->second + (length - i)) = '\0'; }
	}
	char* bufferA = (char*)malloc(sizeof(char)*length);
	char* bufferB = (char*)malloc(sizeof(char)*length);
	for (int i = 0; i < length; i++) {
		strcpy(bufferA, (splits + i)->first);
		strcpy(bufferB, (splits + i)->second);
		if (strcmp(bufferB, "") != 0) { strcat(bufferA, bufferB + 1); }
		char* tmp;
		if ((tmp = fCheck(bufferA, dictionary, dictionarylen)) != NULL) {
			*(arrReturn + iter) = tmp;
			iter++;
		}
	}
	char chars[35] = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
	for (int i = 0; i < length; i++) {
		strcpy(bufferA, (splits + i)->first);
		strcpy(bufferB, (splits + i)->second);
		for (int j = 0; j < 35; j++) {
			strcpy(bufferA, (splits + i)->first);
			char insert[2];
			insert[0] = *(chars + j);
			insert[1] = '\0';
			strcat(bufferA, insert);
			strcat(bufferA, bufferB);
			char* tmp;
			if ((tmp = fCheck(bufferA, dictionary, dictionarylen)) != NULL) {
				*(arrReturn + iter) = tmp;
				iter++;
			}
		}
	}
	for (int i = 0; i < length; i++) {
		strcpy(bufferA, (splits + i)->first);
		strcpy(bufferB, (splits + i)->second);
		for (int j = 0; j < 35; j++) {
			if (strcmp(bufferB, "") != 0) {
				strcpy(bufferA, (splits + i)->first);
				char insert[2];
				insert[0] = *(chars + j);
				insert[1] = '\0';
				strcat(bufferA, insert);
				strcat(bufferA, bufferB + 1);
				char* tmp;
				if((tmp = fCheck(bufferA, dictionary, dictionarylen)) != NULL){
					*(arrReturn + iter) = tmp;
					iter++;
				}
			}
		}
	}
	return { arrReturn,iter };
}
void fInit(char*** dictionary, int* dictionarylens) {
	FILE *fin = fopen("russian.txt", "r");
	char wrdl[STRTEXT];
	char wrds[STRTEXT];
	char* pwrd = NULL;
	long long i = 0;
	*(dictionary) = NULL;
	for (int i = 1; i <= DICT - 1; i++) {
		*(dictionary+i) = (char**)malloc(sizeof(char*) * 250000);
		*(dictionarylens+i) = 0;
	}
	
	long long count = 0;
	while (!feof(fin)) {
		fgets(wrds, STRDICT, fin);
		count++;
		wrds[strlen(wrds) - 1] = '\0';
		*(*(dictionary + strlen(wrds)) + *(dictionarylens + strlen(wrds))) = (char*)malloc(sizeof(char)*(int)strlen(wrds));
		strcpy(*(*(dictionary + strlen(wrds)) + *(dictionarylens + strlen(wrds))), wrds);
		*(dictionarylens + strlen(wrds)) += 1;
	}

}


char* fCheck(char* word, char*** dictionary, int* dictionarylens) {
	char wrds[37]; 
	const char* nums = "0123456789\0";
	strcpy(wrds, word);
	for (int i = 0; i < (int)strlen(word); i++) {
		wrds[i] = tolower(wrds[i]);
		for (int j = 0; j < 10; j++) {
			if (wrds[i] == nums[j]) {
				return 0;
			}
		}
	}
	for (int j = 0; j < *(dictionarylens+strlen(wrds)); j++) {
		if (strcmp(*(*(dictionary+strlen(wrds)) + j), wrds) == 0) {
			return *(*(dictionary + strlen(wrds)) + j);
		}
	}
	return 0;
}