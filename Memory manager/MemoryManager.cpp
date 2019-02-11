#include "MemoryManager.h"

MemoryManager::MemoryManager(int _size)
	: size{ _size + (_size % 4)}, pool{ new char(size) }, freeChunks{ size / 4 }
{
	int bloks = freeChunks;

	chunk = new Chunk(1);
	Chunk* iterator = chunk;

	while (--bloks)
	{
		iterator->next = new Chunk(iterator->blockNumber);
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
	
	Chunk* block = GetNextFreeBlock(_size);

	if (block)
	{
		block->ptr = (char*)pool + (block->blockNumber * 4);
		SetFreeStatus(block, _size, false, block->ptr);
		return block->ptr;
	}

	return nullptr;
}

void MemoryManager::Free()
{
	SetFreeStatus(chunk, size, true, nullptr);
	freeChunks = size / 4;
}

void MemoryManager::SetFreeStatus(Chunk * block, int _size, bool free, void* ptr)
{
	int blockSize = _size / 4;

	while (blockSize--)
	{
		block->ptr = ptr;
		block->isFree = free;
		block = block->next;
	}
}

Chunk* MemoryManager::GetNextFreeBlock(int _size)
{
	Chunk* iterator = GetFreeBlock(chunk);
	Chunk* block = iterator;

	int blockSize = 0;

	while (iterator)
	{
		while (iterator && iterator->isFree)
		{
			blockSize += 4;

			if (blockSize >= _size)
			{
				return block;
			}

			iterator = iterator->next;
		}

		blockSize = 0;
		iterator = GetFreeBlock(iterator);
		block = iterator;
	}
}

Chunk* MemoryManager::GetFreeBlock(Chunk* ptr)
{
	Chunk* iterator = ptr;

	while (iterator && !(iterator->isFree))
	{
		iterator = iterator->next;
	}

	return iterator;
}

void MemoryManager::Free(void* ptr)
{
	Chunk* iterator = chunk;

	while (iterator)
	{
		if (iterator->ptr == ptr)
		{
			iterator->ptr = nullptr;
			iterator->isFree = true;
		}
	}
}