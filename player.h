#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "flag.h"

typedef struct
{
	char* name;
	flag* actions;	//Which actions have we experienced, and what are their values?
}player;

#endif //__PLAYER_H__