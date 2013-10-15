#include "door.h"

door* alloc_door()
{
	door* t_door;
	t_door = (door*)malloc(sizeof(door));
	if (t_door == NULL)
		return NULL;

	t_door->name = strmalloc();
	t_door->room = strmalloc();
	t_door->first = NULL;
	t_door->next = NULL;
	return t_door;
}