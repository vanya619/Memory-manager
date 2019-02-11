#include "MemoryManager.h"

MemoryManager::MemoryManager(int _size)
	: size{ _size + (_size % 4)}, pool{ new char(size) }, freeChunks{ size / 4 }
{
	int bloks = freeChunks;

	chunk = new Chunk();
	Chunk* iterator = chunk;

	while (--bloks)
	{
		iterator->next = new Chunk();
		iterator = iterator->next;
	}
}

MemoryManager::~MemoryManager()
{
	Chunk* iterator = chunk;

	while (chunk)
	{
		chunk = chunk->next;
		delete iterator;
		iterator = chunk;
	}

	delete[] pool;
}

void* MemoryManager::Malloc(const int _size)
{
	if (_size > freeChunks * 4)
	{
		return nullptr;
	}



	return (char*)pool + (offset - _size);
}

void MemoryManager::Free()
{
	freeChunks = size / 4;
}

void* MemoryManager::GetNextFreeBlock(int _size)
{
	Chunk* iterator = chunk;

	while (iterator && iterator->isFree)
	{
		iterator = iterator->next;
	}
}

void MemoryManager::Free(void* ptr)
{

}