#include "MemoryPoolSystem.h"

MemoryPoolSystem::MemoryPoolSystem()
{}

MemoryPoolSystem::~MemoryPoolSystem()
{
	delete m_poolList.front();
	m_poolList.clear();
}

void MemoryPoolSystem::init()
{
	m_poolList.reserve(10);
	new MemoryPool();
}

void MemoryPoolSystem::push(MemoryPool* pool)
{
	m_poolList.push_back(pool);
}

void MemoryPoolSystem::pop()
{
	m_poolList.pop_back();
}

MemoryPool* MemoryPoolSystem::getCurrentPool()
{
	return m_poolList.back();
}
