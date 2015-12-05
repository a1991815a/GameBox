#include "GListener.h"
#include "GEventDispatcher.h"

GListener::~GListener()
{
	GEventDispatcher::getInstance()->removeListener_Safe(this);
}

void GListener::setName(const std::string& name)
{
	m_sName = name;
}
