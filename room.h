#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

typedef struct		//I think structs need to be declared in the h file?
{
	char* name;
	char* data;
	struct room* next;
}room;

room* add_room(char* name, char* data);
room* load_world(room* t_room, FILE* t_world);