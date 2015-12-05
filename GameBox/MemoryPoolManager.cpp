#include "MemoryPoolManager.h"

MemoryPoolManager* MemoryPoolManager::m_instance = nullptr;

MemoryPoolManager* MemoryPoolManager::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new MemoryPoolManager();
	return m_instance;
}

void MemoryPoolManager::destroyInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

MemoryPoolManager::MemoryPoolManager()
{
	m_vPoolVector.reserve(10);
	new MemoryPool();
}

MemoryPoolManager::~MemoryPoolManager()
{
	clear();
}

void MemoryPoolManager::push(MemoryPool* pool)
{
	m_vPoolVector.push_back(pool);
}

void MemoryPoolManager::pop()
{
	m_vPoolVector.pop_back();
}

void MemoryPoolManager::clear()
{
	auto del_front = m_vPoolVector.front();
	m_vPoolVector.clear();
	delete del_front;
}

MemoryPool* MemoryPoolManager::getCurrentPool()
{
	return m_vPoolVector.back();
}
