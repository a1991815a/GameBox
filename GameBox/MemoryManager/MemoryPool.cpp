#include "MemoryPool.h"
#include "../Ref.h"
#include "MemoryPoolSystem.h"

MemoryPool::MemoryPool()
{
	m_refList.reserve(160);
	MemoryPoolSystem::getInstance()->push(this);
}

MemoryPool::~MemoryPool()
{
	clear();
	MemoryPoolSystem::getInstance()->pop();
}

void MemoryPool::push(Ref* ref)
{
	m_refList.push_back(ref);
}

void MemoryPool::clear()
{
	auto itor = m_refList.begin();
	for (; itor != m_refList.end(); ++itor)
		(*itor)->release();
	m_refList.clear();
}
