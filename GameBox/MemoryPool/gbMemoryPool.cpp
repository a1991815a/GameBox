#include "gbMemoryPool.h"
#include <assert.h>

#undef _DEBUG

using namespace gbContainer;

MemoryPoolManager* MemoryPoolManager::m_instance = nullptr;

MemoryChunk::MemoryChunk(size_t size)
{
	start = malloc(size);
	if(start == nullptr)
		throw std::runtime_error("Alloc failure! Memory maybe is not enough!");
	end = (byte*)start + size;
}

MemoryChunk::~MemoryChunk()
{
	free(start);
	start = end = 0;
}

bool MemoryChunk::inChunk(void* pointer) const
{
	return pointer >= start && pointer <= end;
}


MemoryPool::MemoryPool(size_t size)
{
	m_size = size;
	m_capacity = MemoryPoolManager::getInstance()->getAllocSize();
	size_t size_end = m_capacity % size;
	if (size_end != 0)
		m_capacity += size - size_end;
	allocMemory();
}

MemoryPool::~MemoryPool()
{
	for (size_t i = 0; i < m_chunkList.size(); ++i)
		delete m_chunkList.at(i);
	m_chunkList.clear();
}

size_t MemoryPool::size() const
{
	return m_size;
}

size_t MemoryPool::capacity() const
{
	return m_capacity;
}

bool MemoryPool::inThisPool(void* object) const
{
	for (size_t i = 0; i < m_chunkList.size(); ++i)
		if(m_chunkList.at(i)->inChunk(object))
			return true;
	return false;
}

void MemoryPool::allocMemory()
{
	m_capacity += MemoryPoolManager::getInstance()->getAllocSize();		//得到分配容量
	size_t size_end = m_capacity % m_size;
	m_capacity += m_size - size_end;									//倍数化

	MemoryChunk* chunk = new MemoryChunk(m_capacity);					//内存块分配
	m_chunkList.push_back(chunk);										//添加
	m_start = (MemoryObj*)chunk->start;									//头指针指定
	new (m_start) MemoryObj;											//头指针构造

	byte* itor = (byte*)m_start;										//迭代指针
	byte* chunk_end = (byte*)chunk->end;								//
	for(; itor < chunk_end - m_size; itor += m_size)					//
	{
		MemoryObj* obj_next = (MemoryObj*)(itor + size());				//赋值下一个指针
		new (obj_next) MemoryObj;										//构造下一个指针
		((MemoryObj*)itor)->next = obj_next;							//链接指针
	}
#ifdef _DEBUG
	char debug_text[1024] = { 0 };
	sprintf_s(debug_text, "分配内存块: %d字节, size: %d\n", (size_t)((byte*)chunk->end - (byte*)chunk->start), m_size);
	OutputDebugStringA(debug_text);
#endif
}


MemoryPoolManager* MemoryPoolManager::getInstance()
{
	if(m_instance == nullptr)
		m_instance = new MemoryPoolManager();
	return m_instance;
}

void MemoryPoolManager::destroyInstance()
{
	if(m_instance){
		delete m_instance;
		m_instance = nullptr;
	}
}

MemoryPoolManager::MemoryPoolManager()
{}

MemoryPoolManager::~MemoryPoolManager()
{
	for (size_t i = 0; i < m_poolList.size(); ++i)
		delete m_poolList.at(i);
	m_poolList.clear();
}

void MemoryPoolManager::init(size_t minSize/*= MIN_SIZE*/, size_t maxSize /*= MAX_SIZE*/, AllocSize a_size /*= ALLOC_SIZE_2048*/)
{
	assert(maxSize % ALIGN_SIZE == 0);
	this->m_minSize = minSize;
	this->m_maxSize = maxSize;
	this->m_alloc_size = a_size;


	if (minSize < ALIGN_SIZE)
	{
		MemoryPool* pool = new MemoryPool(minSize);
		m_poolList[minSize] = pool;
	}
	for (size_t i = 1; i <= maxSize / ALIGN_SIZE; ++i)
	{
		size_t pool_size = 8 * i;
		MemoryPool* pool = new MemoryPool(pool_size);
		m_poolList[pool_size] = pool;
	}
}

size_t MemoryPoolManager::getAllocSize() const
{
	return m_alloc_size;
}

size_t MemoryPoolManager::searchPool(size_t size) const
{
	return (((size) + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1));
}

#define _DEBUG