/** @file */ 
#include "area.h"

area* alloc_area() //USE THIS FOR THE FIRST INITIALIZATION
{
	area* t_area;
	t_area = (area*)malloc(sizeof(area));
	if (t_area == NULL)
		return NULL;
	t_area->name = strmalloc();
	t_area->desc = strmalloc();
	t_area->doors = NULL;
	t_area->actions = NULL;
	t_area->first = t_area;
	t_area->next = NULL;
	return t_area;
}

area* alloc_areaFirst(area* first_area) //DO -NOT- USE THIS FOR THE FIRST INITIALIZATION
{
	area* t_area;
	t_area = (area*)malloc(sizeof(area));
	if (t_area == NULL)
		return NULL;
	t_area->name = strmalloc();
	t_area->desc = strmalloc();
	t_area->doors = NULL;
	t_area->actions = NULL;
	t_area->first = first_area;
	t_area->next = NULL;
	return t_area;
}


area* first_area(area* t_area)
{
	t_area->first = t_area;
	return t_area;
}