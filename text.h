// Text manipulation tools
/** @file */ 

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

// C String Algorithms //
char* strccat (char* str, char c);
char* strget (char* str);
char* strmalloc();

// Text Algorithms //
text* alloc_text();
text* alloc_textFirst(text* first_text);
void free_text(text* t_text);
text* clear_text(text* t_text);
void print_text(text* str);
int txtcnt(text* str);
int txtlen(text* str);
int txtcmp(text* str1, text* str2);
int txtncmp(text* str1, text* str2);
text* atot (char* str);
text* strgett (text* str);

#endif //__TEXT_H__
