/** @file */ 
#include "door.h"

door* alloc_door()	//USE THIS FOR THE FIRST INITIALIZATION
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

door* alloc_doorFirst(door* first_door)	//DO -NOT- USE THIS FOR THE FIRST INITIALIZATION
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

//Look for the door that the user specified. MAY RETURN NULL
char* find_door(door* t_door, char* name)
{
	door* current_door = t_door;
	if (t_door == NULL || t_door->first == NULL || current_door == NULL)
		return NULL;

	current_door = current_door->first;

	//Loops through the rooms until it finds a hit or ends
	while ((strcmp(current_door->name, name) != 0) && (current_door->next != NULL))
		current_door = current_door->next;

	
	//If we didn't find a hit, go home, you're drunk
	if (current_door == NULL || strcmp(current_door->name, name) != 0)
		return NULL;

	return current_door->room;
}