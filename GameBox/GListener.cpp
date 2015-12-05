#include "GListener.h"
#include "GEventDispatcher.h"

GListener::~GListener()
{
	GEventDispatcher::getInstance()->removeListener_Safe(this);
}

void GListener::setName(const std::string& name)
{
	auto& listenerMap = GEventDispatcher::getInstance()->m_mListenerMap;
	auto itor = listenerMap.find(m_sName);
	m_sName = name;
	if (itor == listenerMap.end())
		return;
	listenerMap.erase(itor);
	listenerMap.insert(std::unordered_map<std::string, GListener*>::value_type(m_sName, this));
}
