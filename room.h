//Structs/functions for areas

#ifndef __ROOM_H__
#define __ROOM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "area.h"
#include "door.h"
#include "action.h"

typedef struct		//I think structs need to be declared in the h file?
{
	char* name;
	area* areas;
	door* doors;
	action* actions;
	//item* items;	//Not yet implemented
	struct room* first;
	struct room* next;
}room;

room* alloc_room();
room* alloc_roomFirst(room* first_room);
room* add_room(char* name, char* data);
room* change_room(room* t_room, char* name);
room* load_world(room* t_room, FILE* t_world);


#endif //__ROOM_H__
