#include "Ref.h"
#include "MemoryPoolManager.h"

void Ref::autorelease()
{
	++m_iReferenceCount;
	MemoryPoolManager::getInstance()->getCurrentPool()->push(this);
}
