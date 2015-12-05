#ifndef __MEMORYPOOLMANAGER__
#define __MEMORYPOOLMANAGER__
#include "MemoryPool.h"

#define _memoryPoolManager MemoryPoolManager::getInstance()

 class MemoryPoolManager{
public:
	static MemoryPoolManager* getInstance();
	static void destroyInstance();
private:
	static MemoryPoolManager* m_instance;
	MemoryPoolManager();
	~MemoryPoolManager();
public:
	void push(MemoryPool* pool);
	void pop();
	void clear();
	MemoryPool* getCurrentPool();
private:
	std::vector<MemoryPool*> m_vPoolVector;
};
#endif