/** @file */ 

#include "action.h"

/**
 * Allocates a new action object and associates itself to action->first.  Does not free() before malloc. USE THIS TO ALLOCATE INITIAL OBJECT.
 * @return Returns the a newly allocated action object.
 */
action* alloc_action()	//USE THIS FOR THE FIRST INITIALIZATION
{
	action* t_action;
	t_action = (action*)malloc(sizeof(action));
	if (t_action == NULL)
		return NULL;

	t_action->name = alloc_text();
	t_action->desc = strmalloc();
	t_action->first = t_action;
	t_action->next = NULL;
	return t_action;
}

/**
 * Allocates a new action object and associates first_action to action->first.  Does not free() before malloc. WARNING: DO NOT USE THIS TO ALLOCATE INITIAL OBJECT.
 * @param[in,out] first_action -  Pointer to an action object
 * @return Returns the a newly allocated action object.
 */
action* alloc_actionFirst(action* first_action)	//USE THIS FOR THE FIRST INITIALIZATION
{
	action* t_action;
	t_action = (action*)malloc(sizeof(action));
	if (t_action == NULL)
		return NULL;

	t_action->name = alloc_text();
	t_action->desc = strmalloc();
	t_action->first = first_action;
	t_action->next = NULL;
	return t_action;
}