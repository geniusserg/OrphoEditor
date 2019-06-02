#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include "Dictionary.h"
#include "Interface.h"
#include "Tempates.h"

struct list* strings;
char* arg1;
char* arg2;
FILE* fout;
char* fname;
FILE* fin;
char** dictionary[DICT]; 
int dictionarylens[DICT];
struct list* ptmpstr;
struct dblist* ptmperr;
int main(int argc, char** argv) {
	arg1 = NULL;
	arg2 = NULL;
	if (argc >= 2) {
		arg1 = *(argv + 1);
		if (argc >= 3) {
			arg2 = *(argv + 2);
		}
	}
	setlocale(LC_ALL, "Russian");
	
	HANDLE hSTDout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO SCRN_INFO; // о курсоре и окне инфа
	GetConsoleScreenBufferInfo(hSTDout, &SCRN_INFO);
	char* fname = NULL;
	FILE* fin = fOpenfile(arg1, &fname);
	system("CLS");
	printf("LOAD...");
	fInit(&dictionary[0], &dictionarylens[0]); //загружаем словарь
	system("CLS");
	strings = initlist(NULL); // список строк с неправильными словами
	strings = fMainProc(fin, &dictionary[0], &dictionarylens[0]);  // здесь хранятся все строчки с неправильными словами в структурах	
	ptmpstr = strings;
	ptmperr = strings->strerrwrds;
	fOutput(hSTDout, strings, ptmperr);  //выводятся на экран
	SetConsoleCursorPosition(hSTDout, { 0,0 });
	fclose(fin);
	while (true) {
		int a = _getch();
		int e = _getch();
		if (e == 77) {
			next(&ptmpstr, &ptmperr, strings);
			system("CLS");
			fOutput(hSTDout, strings, ptmperr);
			SetConsoleCursorPosition(hSTDout, { 0,0 });
		}
		if (e == 75) {
			prev(&ptmpstr, &ptmperr, strings);
			system("CLS");
			fOutput(hSTDout, strings, ptmperr);
			SetConsoleCursorPosition(hSTDout, { 0,0 });
		}
		if (e == 0) {
			if (a == 13) {
				system("CLS");
				char* choice_wrd = fChoose(ptmperr->errwrd, &dictionary[0], &dictionarylens[0]);
				if (choice_wrd != NULL) {
					fChange(choice_wrd, ptmperr, ptmpstr);
				}
				system("CLS");
				next(&ptmpstr, &ptmperr, strings);
				fOutput(hSTDout, strings, ptmperr);
				SetConsoleCursorPosition(hSTDout, { 0,0 });
			}
			if (a == 27) {
				system("CLS");
				arg1 = fname;
				fout = fOpenfilew(arg1, arg2);
				fWrite_in_file(fout, strings);
				system("CLS");
				fOutput(hSTDout, strings, ptmperr);
				SetConsoleCursorPosition(hSTDout, { 0,0 });

			}
		}

	}
	return 0;
}

