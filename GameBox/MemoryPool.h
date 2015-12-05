#ifndef __MEMORYPOOL__
#define __MEMORYPOOL__
#include "Ref.h"
#include "Vector.hpp"

 class MemoryPool: nocopy{
	friend class MemoryPoolManager;
public:
	MemoryPool();
	~MemoryPool();
	void push(Ref* ref);
	void pop(Ref* ref);
	void clear();
	bool isObject(Ref* ref) const;
private:
	Vector<Ref*> m_vRefVector;
};
#endif