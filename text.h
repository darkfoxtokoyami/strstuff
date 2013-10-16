// Text manipulation tools

#ifndef __TEXT_H__
#define __TEXT_H__

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//#include "area.h" // Breaks door.h

typedef struct
{
	char* word;
	struct text* first;
	struct text* next;
}text;

char* strccat (char* str, char c);
char* strget (char* str);
char* strmalloc();
text* alloc_text();
text* alloc_textFirst(text* first_text);
void free_text(text* t_text);
void clear_text(text* t_text);
void print_text(text* str);
text* strgett (text* str);
#endif //__TEXT_H__
