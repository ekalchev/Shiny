///////////////////////////////////////////////////////////////////////////////
//	File:    Mem.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////



#ifndef __MEMORY__
#define __MEMORY__

#include <GlobalDefs.h>

#define L1_CACHE_LINE_SIZE 64

class Mem
{
public:
	static void* AllocAligned(int size,int align = L1_CACHE_LINE_SIZE);
	static void FreeAligned(void* ptr);
};

#endif
