#ifndef __GEVENTDISPATCHER__
#define __GEVENTDISPATCHER__
#include "GSingleInstance.h"
#include "DXUtils.h"
#include "GEvent.h"
#include "GListener.h"

#define _eventDispatcher	GEventDispatcher::getInstance()	

class GEventDispatcher: public GSingleInstance<GEventDispatcher>{
	GSingleIns(GEventDispatcher);
	friend bool WinProcess(HWND, UINT, WPARAM, LPARAM);
	friend class GEvent;
	friend class GListener;
public:
	
	void DispatcherAll();
	void ReadyEvent();

	//������Ϣ������
	void PostEvent(int m_iEventId, DWORD m_dwParam = 0, void* m_pData = nullptr);

	void PostKeyDown(DWORD wParam);
	void PostKeyUp(DWORD wParam);
	bool getKeyState(int key);

	void addListener(GListener* listener);
	void removeListener(const std::string& name);
	void removeListener(GListener* listener);
	void removeListener_Safe(GListener* listener);

	void loop();

	void ReceiveKeyDown(unsigned char key);
	void ReceiveKeyUp(unsigned char key);
	void ReceiveMouseButton(DWORD dwType, DWORD dwData);
	void ReceiveMouseMove(DWORD dwType, DWORD dwData);
	void ReceiveMouseWheel(DWORD dwData);

private:
	ObjectPool<GEvent*>		m_opEventPool;			//��Ϣ��
	std::vector<GEvent*>	m_vEventVector;			//��Ϣ����
	std::unordered_map<std::string, GListener*>
							m_mListenerMap;			//�������б�
	std::vector<DWORD>		m_vKeyDownVector;		//����״̬(������갴��״̬)
	Point					m_piLocation;			//��굱ǰ��������
	Point					m_piMouseMove;			//�������λ��
};
#endif