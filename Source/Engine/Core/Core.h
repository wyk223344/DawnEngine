#pragma once


#define _INTERNAL_MACRO_TO_STR(x) #x
#define MACRO_TO_STR(x) _INTERNAL_MACRO_TO_STR(x)


// Static array size
#define ARRAY_COUNT(array) (sizeof(array) / sizeof(array[0]))