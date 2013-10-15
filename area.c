#include "area.h"

area* alloc_area()
{
	area* t_area;
	t_area = (area*)malloc(sizeof(area));
	if (t_area == NULL)
		return NULL;
	t_area->name = strmalloc();
	t_area->desc = strmalloc();
	t_area->doors = NULL;
	t_area->first = NULL;
	t_area->next = NULL;
	return t_area;
}