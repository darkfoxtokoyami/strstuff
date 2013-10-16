#include "door.h"

door* alloc_door()
{
	door* t_door;
	t_door = (door*)malloc(sizeof(door));
	if (t_door == NULL)
		return NULL;

	t_door->name = strmalloc();
	t_door->room = strmalloc();
	t_door->first = t_door;
	t_door->next = NULL;
	return t_door;
}

door* alloc_doorFirst(door* first_door)
{
	door* t_door;
	t_door = (door*)malloc(sizeof(door));
	if (t_door == NULL)
		return NULL;

	t_door->name = strmalloc();
	t_door->room = strmalloc();
	t_door->first = first_door;
	t_door->next = NULL;
	return t_door;
}


//Assigns the door to itself for its first link
door* first_door(door* t_door)
{
	t_door->first = t_door;
	return t_door;
}