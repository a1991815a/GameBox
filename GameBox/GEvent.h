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
	int			m_iEventId;		//�¼�Id(���ڱ������)
	DWORD		m_dwParam;		//int ����
	void*		m_pData;		//�������� ����
};
#endif