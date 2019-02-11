#pragma once

#include "Chunk.h"

class MemoryManager
{
private:
	int size;
	void* pool;
	int freeChunks;
	Chunk* chunk;

	void SetFreeStatus(Chunk* block, int _size, bool free, void* ptr);
	Chunk* GetNextFreeBlock(int _size);
	Chunk* GetFreeBlock(Chunk* ptr);

public:
	MemoryManager(int _size);
	void* Malloc(int _size);
	void Free();
	void Free(void* ptr);
	~MemoryManager();
};