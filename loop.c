#include "loop.h"


int gameloop(room* rooms)
{
	char* strin = strmalloc();

	while (strcmp (strin, "EXIT") != 0)
	{
		strin = strget(strin);
		printf("\n");
		if (strcmp(strin, "LOOK") == 0)
		{
			printf(rooms->areas->desc);
			printf("\n\n");
		}
		else if (strcmp(strin, "EXIT") == 0)
		{
			//Exit message here,
		}
		else
		{
			printf("I don't understand that command!\n");
		}
	}
	return 0;
}