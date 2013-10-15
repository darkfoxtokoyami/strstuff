// Sorry, this project is a mess at the moment
#include "strstuff.h"


int main (int argc, const char* argv[])
{
	//Super important note:
	//MSVS Doesn't allow declarations to follow statements in a block.
	//It uses an old C90 ruleset.  Support for this was added to C in the C99 standard
	room alpha;
	room* rooms = (room*)malloc(sizeof(room));
	char* strin = ""; //String from user Input
	FILE* world = fopen("WORLD.DAT","r");		//TODO: Add a parameter parser to allow users to specify different worlds.
	if (world == NULL)
	{
		printf("Could not open WORLD.DAT!\n");
		return 1;
	}

	load_world(rooms, world);	//Load our world data into the rooms
	
	// TEST ROUTINES //
	/*while (rooms != NULL)
	{
		printf(rooms->name);
		printf("\n");
		while (rooms->areas != NULL)
		{
			printf("\t");
			printf(rooms->areas->name);
			printf("\n");
			printf("\t\t");
			printf(rooms->areas->desc);
			printf("\n");
			rooms->areas = rooms->areas->next;
		}
		rooms = rooms->next;
	}*/
	while (strcmp (strin, "EXIT") != 0)
	{
		strin = strget(strin);
		printf("\n");
		if (strcmp(strin, "LOOK") == 0)
		{
			printf(rooms->areas->desc);
			printf("\n\n");
		}
	}
	printf("User Exited. Press any key to quit.");
	getchar();
	//END TEST ROUTINES //

	fclose(world);
	return 0;
}