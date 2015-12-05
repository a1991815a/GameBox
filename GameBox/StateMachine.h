#ifndef __STATEMACHINE__
#define __STATEMACHINE__
#include <unordered_map>


class StateMachine;
typedef void(StateMachine::* StateFunc_t)(void* pData);

/**
*	有限状态机
*	version:1.0
*/

#define STATE_NONE UINT_MAX
#define BIND_STATE_FUNC(FUNC) (StateFunc_t)&FUNC

class StateMachine{
public:
	StateMachine();
	~StateMachine();

	//状态转换
	void SetState(int state);
	//注册状态
	void RegisteState(int state, StateFunc_t func);
	//注销状态
	void UnRegisterState(int state);
	//执行状态
	void RunMachine(void* pData);
	//得到状态
	int getState() const;

	//设置和获得参数
	bool getStateFlag(int state);
	void enableStateFlag(int flag);
	void disableStateFlag(int flag);
private:
	std::unordered_map<int, StateFunc_t> 
					m_mStateMap;				//状态列表
	int				m_iCurState;				//当前状态
	StateFunc_t		m_pfnCallback;				//当前执行动作
	int				m_iFlag;					//设置参数
};
#endif