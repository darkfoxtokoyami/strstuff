/** @file */ 

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

/**
 * Allocates a new text object and associates first_text to text->first.  Does not free() before malloc. WARNING: DO NOT USE THIS TO ALLOCATE INITIAL OBJECT.
 * @param[in,out] first_text -  Pointer to a text object
 * @return Returns the first_text object as a newly allocated object.
 */
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
	n_text = t_text;

	t_text = f_text;
	while(t_text != NULL)
	{
		n_text = t_text;
		t_text = t_text->next;
		free(n_text->word);
		free(n_text);
	}
	t_text = f_text;
}

void clear_text(text* t_text)
{
	free_text(t_text);
	t_text = alloc_text();
	return;
}

void print_text(text* str)
{
	text* t_text = str;
	str = str->first;

	printf("\n");

	while (str != NULL)
	{
		printf(str->word);
		str = str->next;
		if (str != NULL)
			printf(",");
	}

	printf("\n");
	str = t_text;
	return;
}

/**
 * Returns a count of how many words are in a text object.
 * @param str - Pointer to a text.
 * @return Returns a count of how many word elements are in a text object. Returns 0 if str contains no words or if str is NULL.
 */
int txtcnt(text* str)
{
	if (str == NULL)
		return 0;

	return 0;
}

int txtlen(text* str)
{
	if (str == NULL)
		return 0;

	return 0;
}

//int txtcmp(text* str)	//TODO

text* strgett (text* str)
{
	char c = 0;
	char p_char = ' ';	//This is a parsing character that'll determine whether the last character was 'whitespace' or not
	int alloc_new = 0;  //Determines if we should create a new word when the next character is entered.
	clear_text(str);
	printf(">");	//Prompt user for input with 'cursor'
	while (c != '\n')
	{
		c =  getchar();
		switch (c)
		{
			//Kill garbage characters
			case '.':
			case ';':
			case ',':
			case '\'':
			case '\\':
			case '?':
			case '!':
			case '\n':
				break;
			case ' ':		//This parses/breaks up the words appropriately
				if (p_char != ' ')
				{
					alloc_new = 1;
					p_char = ' ';
				}
				break;
			default:
				if (alloc_new == 1)
				{
					str->next = alloc_textFirst(str->first);
					str = str->next;
					alloc_new = 0;
				}
				p_char = c;
				str->word = strccat(str->word, toupper(c));
				break;
		}
	}

	print_text(str);
	str = str->first;
	return str;
}

// End Text Stuff //
