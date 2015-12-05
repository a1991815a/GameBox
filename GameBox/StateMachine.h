#ifndef __STATEMACHINE__
#define __STATEMACHINE__
#include <unordered_map>


class StateMachine;
typedef void(StateMachine::* StateFunc_t)(void* pData);

/**
*	����״̬��
*	version:1.0
*/

#define STATE_NONE UINT_MAX
#define BIND_STATE_FUNC(FUNC) (StateFunc_t)&FUNC

class StateMachine{
public:
	StateMachine();
	~StateMachine();

	//״̬ת��
	void SetState(int state);
	//ע��״̬
	void RegisteState(int state, StateFunc_t func);
	//ע��״̬
	void UnRegisterState(int state);
	//ִ��״̬
	void RunMachine(void* pData);
	//�õ�״̬
	int getState() const;

	//���úͻ�ò���
	bool getStateFlag(int state);
	void enableStateFlag(int flag);
	void disableStateFlag(int flag);
private:
	std::unordered_map<int, StateFunc_t> 
					m_mStateMap;				//״̬�б�
	int				m_iCurState;				//��ǰ״̬
	StateFunc_t		m_pfnCallback;				//��ǰִ�ж���
	int				m_iFlag;					//���ò���
};
#endif