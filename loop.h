//Main parsing loop to determin what default commands do what

#ifndef __LOOP_H__
#define __LOOP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "room.h"
#include "door.h"
#include "text.h"

void look(room* rooms);	//Function for just displaying the room we're in
int gameloop(room* rooms);
#endif //__LOOP_H__