#ifndef __FLAG_H__
#define __FLAG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"

typedef struct
{
	char* name; // Name of the flag we're setting
	char value;	// Numeric value of flag, generally 1 or 0
}flag;

#endif //__FLAG_H__