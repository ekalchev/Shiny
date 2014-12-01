///////////////////////////////////////////////////////////////////////////////
//	File:    Mem.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Mem.h"
#include <malloc.h>


void* Mem::AllocAligned(int size,int align)
{
	return malloc(size);
}

void Mem::FreeAligned(void* ptr)
{
	free(ptr);
}