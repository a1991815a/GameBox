#ifndef __MEMORYPOOL__
#define __MEMORYPOOL__
#include <vector>

class Ref;

class MemoryPool{
public:
	MemoryPool();
	~MemoryPool();
	void push(Ref* ref);
	void clear();
private:
	std::vector<Ref*> m_refList;
};
#endif