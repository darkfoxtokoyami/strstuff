#include "text.h"

//Similar to strncat-> This concatenates a character to a c string instead of a const char* to a c string
char* strccat (char* str, char c)
{
	char* t_str;

	t_str = (char*)malloc(strlen(str)+2);
	strcpy(t_str, str);
	strncat(t_str, &c, 1);
	str = t_str;

	return str;
}