/** @file */ 

#include "room.h"


/**
 * Allocates a new room object and associates NULL to room->first.  Does not free() before malloc. USE THIS TO ALLOCATE INITIAL OBJECT.
 * @return Returns the room* object as a newly allocated object.
 */
room* alloc_room() //USE THIS FOR THE FIRST INITIALIZATION
{
	room* t_room;
	t_room = (room*)malloc(sizeof(room));
	if (t_room == NULL)
		return NULL;
	t_room->name = strmalloc();
	t_room->areas = NULL;
	t_room->doors = alloc_door();
	t_room->first = NULL;
	t_room->next = NULL;
	return t_room;
}

/**
 * Allocates a new room object and associates first_room to room->first.  Does not free() before malloc. WARNING: DO NOT USE THIS TO ALLOCATE INITIAL OBJECT.
 * @param[in,out] first_room -  Pointer to a room object
 * @return Returns the first_room object as a newly allocated object.
 */
room* alloc_roomFirst(room* first_room) //DO -NOT- USE THIS FOR THE FIRST INITIALIZATION
{
	room* t_room;
	t_room = (room*)malloc(sizeof(room));
	if (t_room == NULL)
		return NULL;
	t_room->name = strmalloc();
	t_room->areas = NULL;
	t_room->doors = alloc_door();
	t_room->first = first_room;
	t_room->next = NULL;
	return t_room;
}

// Adds a room if we know what data we want in it //
room* add_room(char* name, char* data)
{
	room* t_room = alloc_room();
	if (t_room == NULL)
	{
		printf(">Error: Room node creation failed!");
		return NULL;
	}

	t_room->name = name;
	t_room->areas->name = data;

	return t_room;
}


/**
 * Tries to change the room for the player.  If it fails to find the room, it will remain in the same room
 * @param[in,out] t_room - Pointer to a room object.
 * @return Returns the t_room object, set to the changed or original room.
 */
room* change_room(room* t_room, char* name)
{
	room* current_room;	//This is the current room the user is in. If changing room fails,
						//	 the t_room gets assigned back to the original (current) room.
	
	if (name == NULL || t_room == NULL || t_room->first == NULL)
		return t_room;
	
	current_room = t_room;
	t_room = t_room->first;

	//Loops through the rooms until it finds a hit or ends
	while ((strcmp(t_room->name, name) != 0) && (t_room->next != NULL))
		t_room = t_room->next;

	//If we didn't find a hit, go home, you're drunk
	if (t_room == NULL || strcmp(t_room->name, name) != 0)
	{
		printf("Failed to change rooms.\n");
		t_room = current_room;
	}
	return t_room;
}

/**
 * Loads all the data into the rooms at once (sort of makes add_room obsolete)
 * @param[in,out] t_room - Pointer to a room object. This room should be allocated with alloc_room before it is passed in.
 * @param[in] t_world - Pointer to a FILE.  This is the WORLD.DAT file that we want to load into our game.
 * @return Returns the t_room object, filled with parsed world data.
 * @see alloc_room()
 */
room* load_world(room* t_room, FILE* t_world)
{
	room* current_room;
	//area* first_area;
	int initial = 1;		// Hate this variable name. Must change it later
	int colon_count = 0;	//Used to count the current word position in multi-word objects, like Doors and Actions
	char last_keyword = 0;  //Keeps track of the last major keyword
	char text_keyword = 0;  //Keeps track of which block of text we should be writing to
	char current_char = 0;

	if (t_world == NULL)
	{
		printf(">Error: Unable to load world- World is NULL!");
		return NULL;
	}
	

	//This loop reads in one character at a time and parses the different data types.
	//See WORLD.TXT for description of the keyword characters
	while (((current_char = fgetc(t_world)) != EOF) && !feof(t_world))
	{
		switch (current_char)	//Is this a keyword?
		{
			case '#':	//Comment character. Ignore this shit.
				last_keyword = current_char;
				break;
			case '[':
				last_keyword = current_char;
				if (initial == 1)	//First run initialization
				{
					current_room = t_room;
					current_room->first = t_room;
					initial = 0;

					current_room->areas = alloc_area();	//'new' area
					if (current_room->areas == NULL)
						return NULL;

					current_room->areas = first_area((area*)current_room->areas);

					current_room->areas->doors = alloc_door();	//'new' door
					if (current_room->areas->doors == NULL)
						return NULL;
				}
				else
				{
					current_room->areas = (area*)current_room->areas->first;
					current_room->next = alloc_roomFirst((room*)current_room->first);	//'new' room
					if (current_room->next == NULL)
						return NULL;
					current_room = current_room->next;	//Cycle to the next room
					current_room->first = t_room;

					current_room->areas = alloc_area();	//'new' area
					if (current_room->areas == NULL)
						return NULL;

					current_room->areas->doors = alloc_door();	//'new' door
					if (current_room->areas->doors == NULL)
						return NULL;
				}
				break;
			case ']':
				last_keyword = current_char;
				break;
			case '^':
				text_keyword = last_keyword = current_char;
				if (strlen(current_room->areas->name) != 0)
				{
					current_room->areas->next = alloc_areaFirst((area*)current_room->areas->first);	//'new' room
					if (current_room->areas->next == NULL)
						return NULL;
					current_room->areas = current_room->areas->next;

					current_room->areas->doors = alloc_door();	//'new' door
					if (current_room->areas->doors == NULL)
						return NULL;
				}

				break;
			case '>':
				text_keyword = last_keyword = current_char;
				if (strlen(current_room->areas->doors->name) != 0)
				{
					current_room->areas->doors->next = alloc_doorFirst((door*)current_room->areas->doors->first);	//'new' room
					if (current_room->areas->doors->next == NULL)
						return NULL;
					current_room->areas->doors = current_room->areas->doors->next;
				}
				break;
			case '~':
				text_keyword = last_keyword = current_char;
				break;
			default:
				switch (last_keyword)	//If not, parse the non-keyword items
				{
					case '[':
						if (current_char != '\n')
							current_room->name = strccat(current_room->name, current_char);
						break;
					case ']':
						if (current_char != '\n')
							//current_room->areas->desc = strccat(current_room->areas->desc, current_char);
						break;
					case '^':
						if (current_char == '\n')
							last_keyword = '\n';
						else
							current_room->areas->name = strccat(current_room->areas->name, current_char);
						break;
					case '>':	//Not yet implemented
						if (current_char == '\n')
						{
							last_keyword = '\n';
							colon_count = 0;
						}
						else if (current_char == ':')
							colon_count = 1;
						else if (text_keyword == 0)	//Are we putting this in an area or the standard Room pool?
							if (colon_count == 1)
								current_room->doors->room = strccat(current_room->doors->room, current_char);
							else
								current_room->doors->name = strccat(current_room->doors->name, current_char);
						else if (colon_count == 1)
								current_room->areas->doors->room = strccat(current_room->areas->doors->room, current_char);
						else
							current_room->areas->doors->name = strccat(current_room->areas->doors->name, current_char);
						break;
					case '~':	//Not yet implemented
						if (current_char == '\n')
							last_keyword = '\n';
						break;
					default:
						if (current_char != '\n')
						{
							switch (text_keyword)
							{
								case '^':
									current_room->areas->desc = strccat(current_room->areas->desc, current_char);
									break;
							}
						}
						break;
				}
				break;
		}
	}

	t_room = current_room->first;
	//t_room->areas = first_area;	//Assigns the first area to the room so we get a freshly started linked list to mess with
	//return t_room;
	return t_room;
}
