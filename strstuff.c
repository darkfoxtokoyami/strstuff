// Sorry, this project is a mess at the moment
#include "strstuff.h"


int main (int argc, const char* argv[])
{
	//Super important note:
	//MSVS Doesn't allow declarations to follow statements in a block.
	//It uses an old C90 ruleset.  Support for this was added to C in the C99 standard
	room alpha;
	room* rooms = (room*)malloc(sizeof(room));
	FILE* world = fopen("WORLD.DAT","r");		//TODO: Add a parameter parser to allow users to specify different worlds.
	if (world == NULL)
	{
		printf("Could not open WORLD.DAT!\n");
		return 1;
	}

	load_world(rooms, world);	//Load our world data into the rooms
	
	// TEST ROUTINES //
	while (rooms != NULL)
	{
		printf(rooms->name);
		printf("\n");
		printf(rooms->data);
		printf("\n");
		rooms = rooms->next;
	}
	
	
	alpha.next = add_room("Test3\n", "fagballs");
	
	
	alpha.name = (char*)malloc(5+strlen("\n"));
	strcpy(alpha.name, "Test\n");
	alpha.data = "test";
	printf(alpha.name);
	free(alpha.name);
	getchar();
	//END TEST ROUTINES //

	fclose(world);
	return 0;
}