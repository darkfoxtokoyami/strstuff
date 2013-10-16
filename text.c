#include "text.h"

//Dynamically allocates strings so we can free everything in a clean fashion later
char* strmalloc ()
{
	char* t_str;

	t_str = (char*)malloc(1);
	*t_str = 0;

	return t_str;
}

//Similar to strncat-> This concatenates a character to a c string instead of a const char* to a c string
char* strccat (char* str, char c)
{
	char* t_str;

	t_str = (char*)malloc(strlen(str)+2);
	strcpy(t_str, str);
	strncat(t_str, &c, 1);
	free(str);

	return t_str;
}

//This will be our getline function.  We'll probably add a struct object to parse multiple words more effectively later on
char* strget (char* str)
{
	char c = 0;
	str = strmalloc();
	
	printf(">");	//Prompt user for input with 'cursor'
	while (c != '\n')
	{
		c =  getchar();
		if (c != '\n')
			str = strccat(str, toupper(c));
	}

	return str;
}

// Text Stuff //

text* alloc_text()
{
	text* t_text = (text*)malloc(sizeof(text));
	t_text->word = strmalloc();
	t_text->first = t_text;
	t_text->next = NULL;

	return t_text;
}

text* alloc_textFirst(text* first_text)
{
	text* t_text = (text*)malloc(sizeof(text));
	t_text->word = strmalloc();
	t_text->first = first_text;
	t_text->next = NULL;

	return t_text;
}

void free_text(text* t_text)
{
	text* n_text;	//Helps free nodes;
	text* f_text;	//First node to recycle first node;

	if (t_text == NULL)
		return;
	f_text = t_text->first;
	t_text = t_text->first;

	while (t_text->next != NULL);
	{
			free(t_text->word);
	}

	t_text = t_text->first;
	while(t_text != NULL)
	{
		n_text = t_text;
		t_text = t_text->next;
		free(n_text);
	}
}

void clear_text(text* t_text)
{
	free_text(t_text);
	t_text = alloc_text();
	return;
}

text* strgett (text* str)
{
	char c = 0;
	clear_text(str);
	printf(">");	//Prompt user for input with 'cursor'
	while (c != '\n')
	{
		c =  getchar();
		if (c != '\n')
			str->word = strccat(str->word, toupper(c));
	}

	return str;
}

// End Text Stuff //
