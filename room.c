#include "room.h"


// Adds a room if we know what data we want in it //
room* add_room(char* name, char* data)
{
	room* t_room = (room*)malloc(sizeof(room));
	if (t_room == NULL)
	{
		printf(">Error: Room node creation failed!");
		return NULL;
	}

	t_room->name = name;
	t_room->data = data;

	return t_room;
}

//Loads all the data into the rooms at once (sort of makes add_room obsolete)//
room* load_world(room* t_room, FILE* t_world)
{
	room* current_room;
	int initial = 1;		//Hate this variable name. Must change it later
	char last_keyword = 0;
	char current_char = 0;
	char* t_name;

	if (t_world == NULL)
	{
		printf(">Error: Unable to load world- World is NULL!");
		return NULL;
	}
	

	//This loop reads in one character at a time and parses the different data types.
	//See WORLD.TXT for description of the keyword characters
	while ((current_char = fgetc(t_world)) != EOF)
	{
		switch (current_char)	//Is this a keyword?
		{
			case '[':
				last_keyword = current_char;
				if (initial == 1)	//First run initialization
				{
					current_room = t_room;
					current_room->name = "";
					current_room->data = "";
					initial = 0;
				}
				else
				{
					current_room->next = (room*)malloc(sizeof(room));	//'new' room
					if (current_room == NULL)
						return NULL;
					current_room = current_room->next;	//Cycle to the next room
					current_room->next = NULL;
					current_room->name = "";
					current_room->data = "";
				}
				break;
			case ']':
				last_keyword = current_char;
				break;
			default:
				switch (last_keyword)	//If not, parse the non-keyword items
				{
					case '[':
							t_name = (char*)malloc(strlen(current_room->name)+2);
							strcpy(t_name, current_room->name);
							strncat(t_name, &current_char, 1);
							current_room->name = t_name;
						break;
					case ']':
							t_name = (char*)malloc(strlen(current_room->data)+2);
							strcpy(t_name, current_room->data);
							strncat(t_name, &current_char, 1);
							current_room->data = t_name;
						break;
				}
				break;
		}
	}

	//return t_room;
	return NULL;
}
