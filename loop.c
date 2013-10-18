/** @file */ 
#include "loop.h"

/**
 * A simple, reusable function to display the area description of the current room. Allows easy customization of "LOOK"
 * @param[in] rooms - Pointer to a room.  Look displays the currently selected room of this object
 */
void look(room* rooms)
{
	printf(rooms->name);
	printf(":\n");
	printf(rooms->areas->desc);
	printf("\n\n");
	return;
}

/**
 * This is the main loop that determines how user input is handled.
 * @param[in] rooms - Pointer to a room.  This is the room that will be looped through.
 * @return Returns 0
 */
int gameloop(room* rooms)
{
	text* strin = alloc_text();

	look(rooms);
	while (strcmp(strin->word, "EXIT"))
	{
		strin = strgett(strin);
		printf("\n");
		if (strcmp(strin->word, "LOOK") == 0)
		{
			look(rooms);
		}
		else if (!strcmp(strin->word, "LISTDOOR"))
		{
			printf(rooms->areas->doors->name);
			printf("\n\n");
		}
		else if (!strcmp(strin->word, "EXIT"))
		{
			//Exit message here, Save Y/N
		}
		else
		{
			//Check if this is a door we're being hit with by the user
			if (find_door(rooms->areas->doors,strin->word) != NULL)
			{
				rooms = change_room(rooms, find_door(rooms->areas->doors,strin->word));
				look(rooms);
			}
			else if (find_door(rooms->doors,strin->word) != NULL)
			{
				rooms = change_room(rooms, find_door(rooms->doors,strin->word));
				look(rooms);
			}
			else if (!strcmp(strin->word, "NORTH") ||
				!strcmp(strin->word, "EAST") ||
				!strcmp(strin->word, "SOUTH") ||
				!strcmp(strin->word, "WEST") ||
				!strcmp(strin->word, "LEFT") ||
				!strcmp(strin->word, "RIGHT") ||
				!strcmp(strin->word, "UP") ||
				!strcmp(strin->word, "DOWN")) //If they tried to go some generic direction that doesn't exist
				printf("You are unable to travel in that direction!\n\n");
			else
				printf("I don't understand that command!\n\n");
		}
	}
	return 0;
}