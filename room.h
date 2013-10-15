//Structs/functions for areas

#ifndef __ROOM_H__
#define __ROOM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

typedef struct		//I think structs need to be declared in the h file?
{
	char* name;
	area* areas;
	struct room* first;
	struct room* next;
}room;

room* add_room(char* name, char* data);
room* load_world(room* t_room, FILE* t_world);

#endif //__ROOM_H__
