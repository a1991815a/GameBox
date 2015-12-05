#ifndef __GEVENT__
#define __GEVENT__
#include "GameHeader.h"
#include "GEventTypes.h"

class GEvent{
	friend class GEventDispatcher;
public:
	GEvent();
	inline int getEventId() const { return m_iEventId; };
	inline DWORD getParam() const { return m_dwParam; };
	inline void* getData() const { return m_pData; };


	const Point& getLocation() const;
	const Point& getMouseMove() const;
	bool getKeyState(int key);

private:
	int			m_iEventId;		//事件Id(用于标记类型)
	DWORD		m_dwParam;		//int 参数
	void*		m_pData;		//其他数据 参数
};
#endif