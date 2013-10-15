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

//This will be our getline function.  We'll probably add a struct object to parse multiple words more effectively later on
char* strget (char* str)
{
	char c = 0;
	str = "";
	
	printf(">");	//Prompt user for input with 'cursor'
	while (c != '\n')
	{
		c =  getchar();
		if (c != '\n')
			str = strccat(str, toupper(c));
	}

	return str;
}