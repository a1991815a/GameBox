#ifndef __GLISTENER__
#define __GLISTENER__
#include "GameHeader.h"
#include "GameMacro.h"
#include "GEvent.h"

#define LISTENER_SAFE_TRIGGER(FUNC, EVENT) if(FUNC) return FUNC(EVENT);

typedef std::function<bool(GEvent*)> ListenerFunc_t;

class GListener{
public:
	virtual ~GListener();
	virtual bool Trigger(GEvent* e) = 0;
	void setName(const std::string& name);
	inline const std::string& getName() const { return m_sName; };
private:
	std::string m_sName;
};
#endif