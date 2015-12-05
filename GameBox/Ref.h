#ifndef __REF__
#define __REF__
#include "GameHeader.h"

#pragma warning(disable:4800)

#define REF_AUTO	0x80000000
#define REF_NOAUTO	0x00000000
#define REF_MAX		REF_AUTO

#define REF_ISAUTO (m_iReferenceCount & REF_AUTO)

#define SAFE_RELEASE(p) do{if(p) p->release(); p = nullptr;} while(0)
#define SAFE_RETAIN(p) do{if(p) p->retain();} while(0)


 class Ref{
public:
	Ref() 
		:m_iReferenceCount(REF_NOAUTO)
	{};
	virtual ~Ref() {
		GASSERT(m_iReferenceCount & REF_AUTO || m_iReferenceCount & REF_NOAUTO,
			"The Ref Count is error! %d", m_iReferenceCount);
	};

	void autorelease();

	inline void release() {
		if (REF_ISAUTO && --m_iReferenceCount == REF_AUTO)
			delete this;
	};
	inline void retain() {
		if (REF_ISAUTO)
			++m_iReferenceCount;
	};
	inline bool isAutoRelease() const {
		return REF_ISAUTO;
	};
	inline size_t getReferenceCount() const {
		if (!REF_ISAUTO)
			return (size_t)(-1);
		return m_iReferenceCount & ~REF_AUTO;
	};

	inline void release_safe() {
		if (this == nullptr)
			return;
		release();
	};

	inline void retain_safe() {
		if (this == nullptr)
			return;
		retain();
	};

private:
	size_t		m_iReferenceCount;
};

#pragma warning(default:4800)

#endif