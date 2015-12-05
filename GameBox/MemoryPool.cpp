#include "MemoryPool.h"
#include "MemoryPoolManager.h"

MemoryPool::MemoryPool()
{
	m_vRefVector.reserve(160);
	MemoryPoolManager::getInstance()->push(this);
}

MemoryPool::~MemoryPool()
{
	m_vRefVector.clear();
	MemoryPoolManager::getInstance()->pop();
}

void MemoryPool::push(Ref* ref)
{
	m_vRefVector.push_back(ref);
}

void MemoryPool::pop(Ref* ref)
{
	m_vRefVector.erase(ref);
}

void MemoryPool::clear()
{
	auto itor = m_vRefVector.begin();
	for (; itor != m_vRefVector.end(); ++itor)
		(*itor)->release();
	m_vRefVector.clear();
}

bool MemoryPool::isObject(Ref* ref) const
{
	return m_vRefVector.find(ref) != -1;
}
