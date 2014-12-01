///////////////////////////////////////////////////////////////////////////////
//	File:    SlabAllocator.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#ifndef __SLABALLOCATOR__
#define __SLABALLOCATOR__

#define DEFAULT_BLOCK_SIZE 32768

#include <vector>
using namespace std;

class SlabAllocator
{
private:
	int curBlockPos, blockSize;
	char* currentBlock;
	vector<char*> usedBlocks, availableBlocks;

public:
	SlabAllocator(int bs = DEFAULT_BLOCK_SIZE);
	~SlabAllocator();
	void* Alloc(int size);
	void FreeAll();
};

#endif