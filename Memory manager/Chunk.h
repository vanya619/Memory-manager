#pragma once

struct Chunk
{
	Chunk* next;
	void* ptr;
	int blockNumber;
	bool isFree;

	Chunk(int prevBlockNumber)
		: next{ nullptr }, isFree{ true }, ptr{ nullptr }, blockNumber{ ++prevBlockNumber }
	{ }
};