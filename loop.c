#include "loop.h"

void look(room* rooms)
{
	printf(rooms->name);
	printf(":\n");
	printf(rooms->areas->desc);
	printf("\n\n");
	return;
}

int gameloop(room* rooms)
{
	text* strin = alloc_text();

	look(rooms);
	while (strcmp (strin->word, "EXIT") != 0)
	{
		strin = strgett(strin);
		printf("\n");
		if (strcmp(strin->word, "LOOK") == 0)
		{
			look(rooms);
		}
		else if (strcmp(strin->word, "LISTDOOR") == 0)
		{
			printf(rooms->areas->doors->name);
			printf("\n\n");
		}
		else if (strcmp(strin->word, "EXIT") == 0)
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
			else
				printf("I don't understand that command!\n\n");
		}
	}
	return 0;
}