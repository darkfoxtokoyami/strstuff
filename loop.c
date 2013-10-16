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
	char* strin = strmalloc();

	look(rooms);
	while (strcmp (strin, "EXIT") != 0)
	{
		strin = strget(strin);
		printf("\n");
		if (strcmp(strin, "LOOK") == 0)
		{
			look(rooms);
		}
		else if (strcmp(strin, "LISTDOOR") == 0)
		{
			printf(rooms->areas->doors->name);
			printf("\n\n");
		}
		else if (strcmp(strin, "EXIT") == 0)
		{
			//Exit message here, Save Y/N
		}
		else
		{
			//Check if this is a door we're being hit with by the user
			if (find_door(rooms->areas->doors,strin) != NULL)
			{
				rooms = change_room(rooms, find_door(rooms->areas->doors,strin));
				look(rooms);
			}
			else if (find_door(rooms->doors,strin) != NULL)
			{
				rooms = change_room(rooms, find_door(rooms->doors,strin));
				look(rooms);
			}
			else
				printf("I don't understand that command!\n\n");
		}
	}
	return 0;
}