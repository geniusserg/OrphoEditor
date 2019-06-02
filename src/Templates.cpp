#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "Tempates.h"
void next(struct list** ptmpstr, struct dblist** ptmperr, struct list* strings) {
	if ((*(ptmperr))->next != NULL) {
		(*(ptmperr)) = (*(ptmperr))->next;
	}
	else {
		if ((*(ptmpstr))->next != NULL) {
			*(ptmpstr) = (*(ptmpstr))->next;
			while ((*(ptmpstr))->strerrwrds->errwrd == NULL) {
				*(ptmpstr) = (*(ptmpstr))->next;
			}
			(*(ptmperr)) = (*(ptmpstr))->strerrwrds;
		}
		else {
			*ptmpstr = strings;
			*ptmperr = strings->strerrwrds;
		}
	}
}
void prev(struct list** ptmpstr, struct dblist** ptmperr, struct list* strings) {
	if ((*(ptmperr))->prev != NULL) {
		(*(ptmperr)) = (*(ptmperr))->prev;
	}
	else {
		if ((*(ptmpstr))->prev != NULL) {
			*(ptmpstr) = (*(ptmpstr))->prev;
			while ((*(ptmpstr))->strerrwrds->errwrd == NULL) {
				*(ptmpstr) = (*(ptmpstr))->prev;
			}
			(*(ptmperr)) = (*(ptmpstr))->strerrwrds;
		}
		else {
			*ptmpstr = strings;
			*ptmperr = strings->strerrwrds;
		}
	}
}
struct list* initlist(char* string) {
	struct list* listreturn = (struct list*)malloc(sizeof(struct list));
	if (string != NULL) {
		listreturn->string = (char*)malloc(sizeof(char)*strlen(string));
		strcpy(listreturn->string, string);
	}
	else {
		listreturn->string = NULL;
	}
	struct dblist* qerrwrds = (struct dblist*)malloc(sizeof(struct dblist));
	listreturn->strerrwrds = qerrwrds;
	listreturn->strerrwrds->errwrd = NULL;
	listreturn->strerrwrds->prev = NULL;
	listreturn->strerrwrds->next = NULL;
	listreturn->next = NULL;
	listreturn->prev = NULL;
	return listreturn;
}
struct dblist* initdblist(char* string) {
	struct dblist* dblistreturn = (struct dblist*)malloc(sizeof(struct dblist));
	dblistreturn->next = NULL;
	if (string != NULL) {
		dblistreturn->errwrd = (char*)malloc(sizeof(char)*strlen(string));
		strcpy(dblistreturn->errwrd, string);
	}
	else {
		dblistreturn->errwrd = NULL;
	}
	dblistreturn->prev = NULL;
	return dblistreturn;
}
struct list* add2list(struct list* phead, char* string)
{
	struct list* pheadtmp = phead;
	while (pheadtmp->next) {
		pheadtmp = pheadtmp->next;
	}
	pheadtmp->next = (struct list*)malloc(sizeof(struct list));
	pheadtmp->next->next = NULL;
	pheadtmp->next->prev = pheadtmp;
	pheadtmp->next->string = (char*)malloc(sizeof(char)*strlen(string));
	strcpy(pheadtmp->next->string, string);
	struct dblist* qerrwrds = (struct dblist*)malloc(sizeof(struct dblist));
	pheadtmp->next->strerrwrds = qerrwrds;
	pheadtmp->next->strerrwrds->errwrd = NULL;
	pheadtmp->next->strerrwrds->prev = NULL;
	pheadtmp->next->strerrwrds->next = NULL;
	return pheadtmp->next;
}

void add2dblist(struct dblist* phead, char* string)
{
	struct dblist* pheadtmp = phead;
	while (pheadtmp->next) {
		pheadtmp = pheadtmp->next;
	}
	pheadtmp->next = (struct dblist*)malloc(sizeof(struct dblist));
	pheadtmp->next->next = NULL;
	pheadtmp->next->prev = pheadtmp;
	pheadtmp->next->errwrd = (char*)malloc(sizeof(char)*strlen(string));
	strcpy(pheadtmp->next->errwrd, string);
}
