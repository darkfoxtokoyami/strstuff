//Sub-room/descriptions of rooms

#ifndef __AREA_H__
#define __AREA_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "door.h"

typedef struct
{
	char* name;
	char* desc;
	door* doors;
	struct area* first;
	struct area* next;
}area;

area* alloc_area();
area* alloc_areaFirst(area* first_area);
area* first_area(area* t_area);
#endif //__AREA_H__
