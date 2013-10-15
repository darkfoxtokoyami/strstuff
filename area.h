//Sub-room/descriptions of rooms

#ifndef __AREA_H__
#define __AREA_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

typedef struct
{
	char* name;
	char* desc;
	struct area* next;
}area;


#endif //__AREA_H__
