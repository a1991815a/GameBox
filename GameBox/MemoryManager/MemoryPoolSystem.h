#ifndef __MEMORYPOOLSYSTEM__
#define __MEMORYPOOLSYSTEM__
#include "../SingleInstance/SingleInstance.h"
#include "MemoryPool.h"

#define _memoryPoolSystem				MemoryPoolSystem::getInstance()

class MemoryPoolSystem: public SingleInstance<MemoryPoolSystem>{
	DEFINE_PRIVATE_INSTANCE(MemoryPoolSystem);
public:
	void init();

	void push(MemoryPool* pool);
	void pop();
	MemoryPool* getCurrentPool();
private:
	std::vector<MemoryPool*> m_poolList;
};
#endif