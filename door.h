//These are the exits for navigating between rooms

#ifndef __DOOR_H__
#define __DOOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

typedef struct
{
	char* name;
	char* room;
	struct door* first;
	struct door* next;
}door;

#endif //__DOOR_H__