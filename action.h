#ifndef __ACTION_H__
#define __ACTION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

typedef struct
{
	text* name;		//The action, without the preceding ~
	char* desc;		//The description/response to the action
	struct action* first;
	struct action* next;
}action;

action* alloc_action();
action* alloc_actionFirst(action* first_action);
#endif //__ACTION_H__