#pragma once

struct Chunk
{
	Chunk* next;
	void* ptr;
	int size;
	bool isFree;

	Chunk()
		: next{ nullptr }, ptr{ nullptr }, size{ 0 }, isFree{ true }
	{ }
};