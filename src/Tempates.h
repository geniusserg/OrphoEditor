#pragma once
#ifndef TEMPLATES_H
#define TEMPLATES_H
struct list {
	struct list* next;
	struct list* prev;
	char* string;
	struct dblist* strerrwrds;
};
struct dblist {
	struct dblist* prev;
	struct dblist* next;
	char* errwrd;
};
struct list* initlist(char* string);
struct dblist* initdblist(char* string);
struct list* add2list(struct list* phead, char* string);
void add2dblist(struct dblist* phead, char* string);
void next(struct list** ptmpstr, struct dblist** ptmperr, struct list* strings);
void prev(struct list** ptmpstr, struct dblist** ptmperr, struct list* strings);
#endif