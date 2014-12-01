///////////////////////////////////////////////////////////////////////////////
//	File:    SlabAllocator.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "SlabAllocator.h"
#include "Mem.h"

SlabAllocator::SlabAllocator(int bs)
{
	blockSize = bs;
	curBlockPos = 0;
	currentBlock = (char*)Mem::AllocAligned(blockSize);
}

SlabAllocator::~SlabAllocator()
{
	FreeAll();
	while(availableBlocks.size())
	{
		Mem::FreeAligned(availableBlocks.back());
		availableBlocks.pop_back();
	}
}

void* SlabAllocator::Alloc(int size)
{
	size = ((size + 7) & (-7));
	if(curBlockPos + size > blockSize)
	{
		usedBlocks.push_back(currentBlock);
		if(availableBlocks.size() && size <= blockSize)
		{
			currentBlock = availableBlocks.back();
			availableBlocks.pop_back();
		}
		else
		{
			currentBlock = (char*)Mem::AllocAligned(max(size,blockSize));
		}
		curBlockPos = 0;
	}

	void* ret = currentBlock + curBlockPos;
	curBlockPos += size;
	return ret;
}

void SlabAllocator::FreeAll()
{
	curBlockPos = 0;
	while(usedBlocks.size())
	{
		availableBlocks.push_back(usedBlocks.back());
		usedBlocks.pop_back();
	}
}