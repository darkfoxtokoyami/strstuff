/** @file */ 

#include "text.h"

/**
 * Dynamically allocates strings so we can free everything in a clean fashion later
 * @return Returns a newly allocated C String.
 */
char* strmalloc ()
{
	char* t_str;

	t_str = (char*)malloc(1);
	*t_str = 0;

	return t_str;
}

/**
 * Similar to strncat-> This concatenates a character to a c string instead of a const char* to a c string.
 * @param[in,out] str - Pointer to a C String.
 * @param[in] c - Character to be appended to str.
 * @return Returns the C String str.
 */
char* strccat (char* str, char c)
{
	char* t_str;

	t_str = (char*)malloc(strlen(str)+2);
	strcpy(t_str, str);
	strncat(t_str, &c, 1);
	free(str);

	return t_str;
}

/**
 * This gets a line from stdin and allocates it to the specified C String.
 * @param[in,out] str - Pointer to a C String.
 * @return Returns str, filled with stdin up to \n
 */
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

// Text Algorithms //

/**
 * Allocates a new text object and associates itself to text->first.  Does not free() before malloc. USE THIS TO ALLOCATE INITIAL OBJECT.
 * @param[in,out] first_text -  Pointer to a text object
 * @return Returns the a newly allocated text object.
 * @see free_text()
 */
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
 * @see free_text()
 */
text* alloc_textFirst(text* first_text)
{
	text* t_text = (text*)malloc(sizeof(text));
	t_text->word = strmalloc();
	t_text->first = first_text;
	t_text->next = NULL;

	return t_text;
}

/**
 * Frees the text object and frees all items within it.  The item will need to be allocated to be used again.
 * @param[in] t_text - Pointer to a text. Destroys/Frees all data within this object.
 * @return VOID
 * @see alloc_text
 */
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

/**
 * Frees memory in the text and allocates new memory to the text and initializes default values.
 * @param[in,out] str - Pointer to a text.  Items in this object will be destroyed
 * @return Returns the newly allocated text.
 * @see free_text(text* t_text)
 * @see alloc_text()
 */
text* clear_text(text* str)
{
	free_text(str);
	str = alloc_text();
	return str;
}

/**
 * Prints a text object to stdout.  Loops through all words in text object and prints them, delimited by commas.
 * @param[in] str - Pointer to a text.
 * @return Returns void.
 */
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
 * @param[in] str - Pointer to a text.
 * @return Returns a count of how many word elements are in a text object. Returns 0 if str contains no words or if str is NULL.
 */
int txtcnt(text* str)
{
	//  Initialization  //
	text* t_str = str;
	int count = 0;

	//  NULL Validation  //
	if (str == NULL || str->first == NULL)
		return 0;

	// Primary Function //
	t_str = t_str->first;

	while (t_str != NULL)
	{
		if (t_str->word != NULL && strlen(t_str->word) > 0)	//Just make sure that this word is for realzies. Don't count invalid chars. 
			count++;										//	This also prevents users from typing one invalid char and incorrectly counting it.
		t_str = t_str->next;
	}

	if (count > 0)	//Only return positive numbers, regardless of laws of physics changing.
		return count;

	// Default Return //
	return 0;
}

/**
 * Returns a count of the length of the words in a text object, added together.
 * @param[in] str - Pointer to a text.
 * @return Returns a count of the length of the words in a text object, added together. Returns 0 if str contains no words or if str is NULL.
 */
int txtlen(text* str)
{
	//  Initialization  //
	text* t_str = str;
	int count = 0;

	//  NULL Validation  //
	if (str == NULL || str->first == NULL)
		return 0;

	// Primary Function //
	t_str = t_str->first;

	while (t_str != NULL)
	{
		if (t_str->word != NULL)	//Just make sure that this word is for realzies
			count += strlen(t_str->word);
		t_str = t_str->next;
	}

	// Return Success //
	if (count > 0)	//Only return positive numbers, regardless of laws of physics changing.
		return count;

	// Return Default //
	return 0;
}

/**
 * Compares two text objects in the same fashion strcmp() compares char*'s. 
 * @param[in] str1 - Pointer to a text.  Compared against str2.
 * @param[in] str2 - Pointer to a text.  Compared against str1.
 * @return Returns an integral value indicating the relationshp between the text objects. A zero value indicates both text objects are equal.  A value greater than zero indicates that the first character that does not match has a greater value in str1 than in str2; And a value less than zero indicates the opposite.
 */
int txtcmp(text* str1, text* str2)
{
	// Initialization //
	text* t_str1;
	text* t_str2; 
	int compare = 0;

	//  NULL Validation  //
	if (str1 == NULL || str2 == NULL || str1->first == NULL || str2->first == NULL)
		return 0;

	// Primary Function //
	t_str1 = str1->first;
	t_str2 = str2->first;

	while (t_str1 != NULL && t_str2 != NULL && t_str1->word != NULL && t_str2->word != NULL && !compare)
	{
		compare = strcmp(t_str1->word, t_str2->word);

		t_str1 = t_str1->next;
		t_str2 = t_str2->next;
	}

	// Return Default //
	return compare;
}

/**
 * Returns a count of the number of words that match between two texts, regardless of how the words are ordered. Does NOT return count of UNIQUE items.
 * @param[in] str1 - Pointer to a text.  To be compared against str2.
 * @param[in] str2 - Pointer to a text.  To be compared against str1.
 * @return Returns the count of the number of words that match between str1 and str2, regardless of word worder.  Returns 0 if str1 or str2 are NULL.
 */
int txtncmp(text* str1, text* str2)
{
	// Initialization //
	text* t_str1;
	text* t_str2; 
	int count = 0;

	//  NULL Validation  //
	if (str1 == NULL || str2 == NULL || str1->first == NULL || str2->first == NULL)
		return 0;

	// Primary Function //
	t_str1 = str1->first;
	t_str2 = str2->first;

	while (t_str1 != NULL)
	{
		while (t_str2 != NULL && strcmp(t_str1->word, t_str2->word) != 0)
		{
			t_str2 = t_str2->next;
		}

		if (t_str2 != NULL && !strcmp(t_str1->word, t_str2->word))
			count++;

		t_str1 = t_str1->next;
		t_str2 = str2->first;
	}

	// Return Success //
	if (count > 0)	//Only return positive numbers, regardless of laws of physics changing.
		return count;

	// Return Default //
	return 0;
}

/**
 * Converts a C String to a text object.
 * @param[in] str - Pointer to a C String.
 * @return Returns a newly allocated text object, populated with contents of str.
 */
text* atot (char* str)
{
	//  Initialization  //
	text* t_str = NULL;
	char c = 0;			//This is the character we get from stdin 
	char p_char = ' ';	//This is a parsing character that'll determine whether the last character was 'whitespace' or not
	int alloc_new = 0;  //Determines if we should create a new word when the next character is entered.
	int i = 0;			//Current position at str.

	t_str = clear_text(t_str);	//Allocate a new, empty string.

	//  NULL Validation  //
	if (t_str == NULL)
		printf("Failed to alloc atot\n");
	else if (t_str->first == NULL)
		printf("Failed to alloc atot first\n");

	if (t_str == NULL || t_str->first == NULL)
		return NULL;

	// Primary Function //
	while (c != '\n')
	{
		c =  str[i];
		switch (c)
		{
			//Kill garbage characters/Treat as whitespace
			case '.':
			case ';':
			case ',':
			case '\'':
			case '\\':
			case '?':
			case '!':
			case '\n':
			case ' ':		//This parses/breaks up the words appropriately
				if (p_char != ' ')
				{
					alloc_new = 1;
					p_char = ' ';
				}
				break;
			case '\0':
				c = '\n';
				break;
			default:
				if (alloc_new == 1)
				{
					t_str->next = alloc_textFirst((text*)t_str->first);
					t_str = t_str->next;
					alloc_new = 0;
				}
				p_char = c;
				t_str->word = strccat(t_str->word, toupper(c));
				break;
		}
		i++;
	}

	t_str = t_str->first;

	/// TEST ROUTINES //
	
	/// END TEST ROUTINES //

	// Default Return //
	return t_str;
}

text* txtccat (text* str, char c)
{
	text* t_str;

	if (str == NULL || str->first == NULL)
		return NULL;

	t_str = str;

	switch (c)
	{
		//Kill garbage characters/Treat as whitespace
		case '.':
		case ':':
		case ';':
		case ',':
		case '\'':
		case '\\':
		case '?':
		case '!':
		case ' ':
			//This parses/breaks up the words appropriately
			if (strlen(t_str->word) > 0)
			{
				t_str->next = alloc_textFirst((text*)t_str->first);
				t_str = t_str->next;
			}
			break;

		//If this is an EOL char, discard it, because that's the end of the action
		case '\0':
		case '\n':
			break;
		default:
			//Add the char to the word
			t_str->word = strccat(t_str->word, toupper(c));
			break;
	}

	return t_str;
}

/**
 * Gets user input from stdin and parses it into a newly allocated text.  This destroys any data in the passed in text. May return NULL if allocation fails!
 * @param[in,out] str - Pointer to a text.  Will be destroyed and reallocated in function.
 * @return Returns str with contents of parsed stdin.  May return NULL.
 */
text* strgett (text* str)
{
	//  Initialization  //
	char c = 0;			//This is the character we get from stdin 
	char p_char = ' ';	//This is a parsing character that'll determine whether the last character was 'whitespace' or not
	int alloc_new = 0;  //Determines if we should create a new word when the next character is entered.

	clear_text(str);	//Allocate a new, empty string.

	//  NULL Validation  //
	if (str == NULL || str->first == NULL)
		return NULL;

	// Primary Function //
	printf(">");	//Prompt user for input with 'cursor'
	while (c != '\n')
	{
		c =  getchar();
		switch (c)
		{
			//Kill garbage characters/Treat as whitespace
			case '.':
			case ';':
			case ',':
			case '\'':
			case '\\':
			case '?':
			case '!':
			case '\n':
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
					str->next = alloc_textFirst((text*)str->first);
					str = str->next;
					alloc_new = 0;
				}
				p_char = c;
				str->word = strccat(str->word, toupper(c));
				break;
		}
	}

	str = str->first;

	/// TEST ROUTINES //
	//print_text(str);
	//printf("Word count: %d\n", txtcnt(str));
	//printf("Text length: %d\n", txtlen(str));
	//printf("Compare A BC DEF: %d\n", txtncmp(str, atot("A BC DEF\n"))); //atot is kind of buggy
	//printf("\n");
	/// END TEST ROUTINES //

	// Default Return //
	return str;
}

// End Text Stuff //
