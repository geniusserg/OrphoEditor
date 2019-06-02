#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "Interface.h"
#include "Tempates.h"
#include "Dictionary.h"

void fChange(char* wrd, struct dblist* mistake, struct list* strings) { //конкретную запись в листе!
	char* newstr = (char*)malloc(sizeof(char) * 1000);
	struct dblist* pheadtmp = strings->strerrwrds;
	int i = 0;
	int s = 0;
	while(i<strlen(strings->string)){
		int cerr = 0;
		if (pheadtmp != NULL && pheadtmp->errwrd != NULL) {
			if (strings->string + i == strstr(strings->string + i, pheadtmp->errwrd)) {
				cerr = 1;
			}
		}
		if (cerr == 1) {
			if (mistake == pheadtmp) {
				for (int j = 0; j < strlen(wrd); j++) {
					*(newstr + s) = *(wrd + j);
					s++;
				}
				i += strlen(pheadtmp->errwrd);
				if (pheadtmp->prev != NULL) {
					if (pheadtmp->next != NULL) {
						pheadtmp->prev->next = pheadtmp->next;
					}
					else {
						pheadtmp->prev->next = NULL;
					}
				}
				else {
					if (pheadtmp->next != NULL) {
						strings->strerrwrds = pheadtmp->next;
						strings->strerrwrds->prev = NULL;
					}
					else {
						strings->strerrwrds = NULL;
					}
				}
			}
			else {
				for (int j = 0; j < strlen(pheadtmp->errwrd); j++) {
					*(newstr + s) = *(pheadtmp->errwrd + j);
					s++;
				}
				i += strlen(pheadtmp->errwrd);
			}
			pheadtmp = pheadtmp->next;
			cerr = 0;
		}
		else {
			*(newstr + s) = *(strings->string + i);
			s++;
			i++;
		}
	}
	*(newstr + s) = '\0';
	strings->string = newstr;
}

void fWrite_in_file(FILE* fout, struct list* strings) {
	struct list* ptmp = strings;
	do {
		if (ptmp->string != NULL) {
			fprintf(fout, ptmp->string);
		}
		ptmp = ptmp->next;
	}while (ptmp != NULL);
	fclose(fout);
}

void fOutput (HANDLE hSTDout,struct list* strings, struct dblist* current) {
	SetConsoleTextAttribute(hSTDout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE);
	system("CLS");
	struct list* pcurrlist = strings;
	while (pcurrlist) {
		struct dblist* pheadtmp = pcurrlist->strerrwrds;
		for (int i = 0; i < strlen(pcurrlist->string); i++) {
			int cerr = 0;
			if (pheadtmp != NULL && pheadtmp->errwrd != NULL) {
				if (pcurrlist->string + i == strstr(pcurrlist->string + i, pheadtmp->errwrd)) {
					cerr = 1;
				}
			}
			if (cerr == 1) {
				if (pheadtmp == current) {
					SetConsoleTextAttribute(hSTDout, FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED);
				}
				else {
					SetConsoleTextAttribute(hSTDout, FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_BLUE);
				}
				printf("%s", pheadtmp->errwrd);
				i += strlen(pheadtmp->errwrd) - 1;
				pheadtmp = pheadtmp->next;
				cerr = 0;
			}
			else {
				SetConsoleTextAttribute(hSTDout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE);
				printf("%c", *(pcurrlist->string + i));
			}
		}
		pcurrlist = pcurrlist->next;
	}
}

char* fChoose(char* wrd, char*** dictionary, int* dictionarylens) {
	int choice = 0;
	printf("please wait...");
	struct result f = fFind(wrd, &dictionary[0], &dictionarylens[0]);
	system("CLS");
	printf("0. отмена\n");
	printf("1. свой вариант\n");
	int h = 0;
	for (int i = 0; i < f.length; i++) {
		printf("%d. %s\n", i+2, *(f.arr+i));
		h++;
	}
	printf(">>> ");
	scanf("%d", &choice);
	if (choice == 0 || choice > h+1) {
		return NULL;
	}
	else if (choice == 1) {
		system("CLS");
		printf("введите свой вариант исправлени€: ");
		char* buffer = (char*)malloc(sizeof(char)*100);
		char* buffer2 = (char*)malloc(sizeof(char)*100);
		scanf("%s", buffer);
		OemToAnsi(buffer, buffer2);
		return buffer2;
	}
	else {
		return *(f.arr + choice - 2);
	}
}

struct list* fMainProc(FILE* ned, char*** dictionary, int* dictionarylens){
	char wrdl[STRTEXT];
	struct list* strings = initlist(NULL);
	char* pwrd;
	feof(ned);
	while (!feof(ned)) {
		fgets(wrdl, STRTEXT, ned);
		struct list* pcurrlist = NULL;
		if (strings->string == NULL) {
			strings = initlist(wrdl);
			pcurrlist = strings;
		}
		else {
			pcurrlist = add2list(strings, wrdl);
		}
		pwrd = strtok(wrdl, " .,\n-:\"!?}{[]><Ч");
		char* res;
		while (pwrd != NULL) {
			if (strlen(pwrd) < 37) {
				res = fCheck(pwrd, dictionary, dictionarylens);
			}
			else {
				res = NULL;
			}
			if (res == NULL) {
				struct list* pheadtmp = pcurrlist;
				if (pheadtmp->strerrwrds->errwrd == NULL) {
					pheadtmp->strerrwrds = initdblist(pwrd);
				}
				else {
					add2dblist(pheadtmp->strerrwrds, pwrd);
				}
			}
			pwrd = strtok(NULL, " .,\n-:\"!?}{[]><Ч");
		}
	}
	return strings;
}

FILE* fOpenfilew(char* arg1, char* arg2) {
	char fname[100];
	int isopen = 0;
	char* nameopen = NULL;
	FILE *ned;
	while (isopen != 1) {
		if (arg2 == NULL) {
			printf("Enter name of output file (press Q to write in %s)\n", arg1);
			scanf("%s", fname);
			if (strcmp(fname,"Q")==0 || strcmp(fname, "q")==0){
				ned = fopen(arg1, "w");
			}
			else {
				nameopen = fname;
			}
		}
		else {
			nameopen = arg2;
		}
		char* tmp=NULL;
		char* tmpstr = (char*)malloc(sizeof(char)*strlen(nameopen));
		strcpy(tmpstr, nameopen);
		tmp = strtok(tmpstr, ".");
		tmp = strtok(NULL, ".");
		if (strcmp(tmp, "txt") != 0 || (tmp = strtok(NULL, ".")) != NULL) { ned = NULL; }
		else { ned = fopen(nameopen, "w"); }
		if (ned == NULL) {
			printf("\ntry again");
			arg2 = NULL;
		}
		else {
			isopen = 1;
		}
	}
	return ned;
}

FILE* fOpenfile(char* arg, char** fname_out) {
	char fname[100];
	int isopen = 0;
	FILE *ned;
	char* tmp;
	while (isopen != 1) {
		if (arg == NULL) {
			printf("\nEnter name of file\n");
			char* buffer = (char*)malloc(sizeof(char) * 255);
			scanf("%s", buffer);
			*(fname_out) = buffer;
		}
		else {
			*(fname_out) = arg;
		}
		char* tmpstr = (char*)malloc(sizeof(char)*strlen(*(fname_out)));
		strcpy(tmpstr, *(fname_out));
		tmp = strtok(tmpstr, ".");
		tmp = strtok(NULL, ".");
		if (strcmp(tmp, "txt") != 0 || (tmp = strtok(NULL, ".")) != NULL) { ned = NULL; }
		else { ned = fopen(*(fname_out), "r"); }
		if (ned == NULL) {
			printf("\ntry again");
		}
		else {
			feof(ned);
			if (feof(ned)) {
				printf("empty file!");
				printf("do you want to go to enter new name of file? (1/0)");
				int choice;
				scanf("%d", &choice);
				if (choice == 0) { isopen = 1; }
			}
			else
			{
				isopen = 1;
			}
		}
	} 
	return ned;
}

