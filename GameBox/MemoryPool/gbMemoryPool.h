#ifndef __GBMEMORYPOOL__
#define __GBMEMORYPOOL__
#include <vector>
#include <unordered_map>
#ifdef _DEBUG
#include <windows.h>
#endif
#include <assert.h>

#undef _DEBUG
#define MIN_SIZE 1
#define MAX_SIZE 128

#define ALIGN_SIZE 8
#define MemoryChunkPoolInit gbContainer::MemoryPoolManager::getInstance()->init()
#define gbAlloc(p) gbContainer::MemoryPoolManager::getInstance()->alloc(p)
#define gbConstruct(p, CLS,...) gbAlloc(p);p->CLS::CLS(__VA_ARGS__)
#define gbDealloc(p) gbContainer::MemoryPoolManager::getInstance()->dealloc(p)
#define gbAllocArray(p, _Size) gbContainer::MemoryPoolManager::getInstance()->alloc_array(p, _Size)
#define gbDeallocArray(p, _Size) gbContainer::MemoryPoolManager::getInstance()->dealloc_array(p, _Size)

namespace gbContainer {


	typedef unsigned char byte;

	/*
	内存池: 三类内聚

	*/

	enum AllocSize : unsigned int {
		ALLOC_SIZE_128 = 128,
		ALLOC_SIZE_256 = 256,
		ALLOC_SIZE_512 = 512,
		ALLOC_SIZE_1024 = 1024,
		ALLOC_SIZE_2048 = 2048
	};

	struct MemoryChunk
	{
		MemoryChunk(size_t size);
		~MemoryChunk();
		bool inChunk(void* pointer) const;
		void* start;
		void* end;
	};

	class MemoryPool {
		friend class MemoryPoolManager;
	private:
		MemoryPool(size_t size);
		~MemoryPool();
	private:
		union MemoryObj {
			MemoryObj() : next(nullptr) {}
			MemoryObj* next;
			byte* object;
		};
	public:
		size_t size() const;
		size_t capacity() const;
		bool inThisPool(void* object) const;
		template<typename _pTy>
		void alloc(_pTy*& pointer);
		/*
		数组分配:未开发完成*/
		template<typename _pTy>
		void alloc_array(_pTy*& pointer, int size) {
			pointer = new _pTy[size];
		};

		template<typename _pTy>
		bool dealloc(_pTy* pointer);

		/*
		数组分配:未开发完成*/
		template<typename _pTy>
		bool dealloc_array(_pTy* pointer) {
			delete[] pointer;
		};

	private:
		void allocMemory();

	private:
		MemoryObj* m_start;
		size_t m_size;
		size_t m_capacity;
		std::vector<MemoryChunk*> m_chunkList;
	};

	//次级分配器
	template<typename _pTy>
	void MemoryPool::alloc(_pTy*& pointer)
	{
		if (m_start == nullptr)
			allocMemory();
		MemoryObj* obj = m_start;
		m_start = m_start->next;
		obj->~MemoryObj();
		pointer = (_pTy*)(obj);
		new (pointer) _pTy;
#ifdef _DEBUG
		char debug_text[1024] = { 0 };
		sprintf_s(debug_text, "分配内存: %x, 大小为:%d \n", (size_t)pointer, m_size);
		OutputDebugStringA(debug_text);
#endif
	}

	//次级回收器
	template<typename _pTy>
	bool MemoryPool::dealloc(_pTy* pointer)
	{
		if (!inThisPool(pointer))
			return false;
		pointer->~_pTy();
		MemoryObj* obj = (MemoryObj*)pointer;
		new (obj) MemoryObj;
		obj->next = m_start;
		m_start = obj;

#ifdef _DEBUG
		char debug_text[1024] = { 0 };
		sprintf_s(debug_text, "回收内存: %x, size: %d \n", (size_t)pointer, m_size);
		OutputDebugStringA(debug_text);
#endif

		return true;
	}

	class MemoryPoolManager {
	public:
		static MemoryPoolManager* getInstance();
		static void destroyInstance();
	private:
		static MemoryPoolManager* m_instance;

	public:
		MemoryPoolManager();
		~MemoryPoolManager();

		void init(size_t minSize = MIN_SIZE, size_t maxSize = MAX_SIZE, AllocSize a_size = ALLOC_SIZE_1024);

		size_t getAllocSize() const;
		size_t searchPool(size_t size) const;

		template<typename _pTy>
		void alloc(_pTy*& pointer);
		template<typename _pTy>
		void dealloc(_pTy* pointer);

		/*
		数组分配:未开发完成*/
		template<typename _pTy>
		void alloc_array(_pTy*& pointer, int size) {
			pointer = new _pTy[size];
		};
		/*
		数组分配:未开发完成*/
		template<typename _pTy>
		bool dealloc_array(_pTy* pointer) {
			delete[] pointer;
		};

	private:
		std::unordered_map<size_t, MemoryPool*> m_poolList;	//次级分配 内存池
		size_t m_minSize;									//次级分配的最小内存尺寸
		size_t m_maxSize;									//次级分配的最大内存尺寸
		size_t m_alloc_size;								//每个内存池所应具有的最小内存容量
	};

	template<typename _pTy>
	void MemoryPoolManager::alloc(_pTy*& pointer)
	{
		assert(pointer == nullptr);
		size_t alloc_size = searchPool(sizeof(_pTy));
		auto find_pool = m_poolList.find(alloc_size);
		if (find_pool == m_poolList.end())
		{
			//执行一级分配(在内存池中没有找到合适的 次级分配器时)
			pointer = new _pTy();
			return;
		}
		//执行次级分配
		find_pool->second->alloc(pointer);
	}

	template<typename _pTy>
	void MemoryPoolManager::dealloc(_pTy* pointer)
	{
		//迭代执行次级回收
		auto itor = m_poolList.begin();
		for (; itor != m_poolList.end(); ++itor)
			if (itor->second->dealloc(pointer))
				return;

		//执行一级回收(在内存池中没有找 该内存的次级回收器时)
		delete pointer;
	}


};



#define _DEBUG

#endif