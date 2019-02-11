#pragma once

#include "Chunk.h"

class MemoryManager
{
private:
	int size;
	void* pool;
	int freeChunks;
	Chunk* chunk;

	void* GetNextFreeBlock(int _size);

public:
	MemoryManager(int _size);
	void* Malloc(int _size);
	void Free();
	void Free(void* ptr);
	~MemoryManager();
};