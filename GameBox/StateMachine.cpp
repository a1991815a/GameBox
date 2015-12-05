#include "StateMachine.h"
#include <assert.h>

#pragma warning(push)
#pragma warning(disable:4800)

StateMachine::StateMachine()
	:m_iCurState(STATE_NONE),
	m_pfnCallback(nullptr),
	m_iFlag(0)
{
}

StateMachine::~StateMachine()
{

}

void StateMachine::SetState(int state)
{
	m_iCurState = state;
	if (m_iCurState == STATE_NONE)
		m_pfnCallback = nullptr;
	else
	{
		auto itor = m_mStateMap.find(state);
		if (itor != m_mStateMap.end())
			m_pfnCallback = itor->second;
		else
			m_pfnCallback = nullptr;
	}
}

void StateMachine::RegisteState(int state, StateFunc_t func)
{
	m_mStateMap[state] = func;
}

void StateMachine::UnRegisterState(int state)
{
	auto itor = m_mStateMap.find(state);
	if (itor != m_mStateMap.end())
		m_mStateMap.erase(itor);
	if (state == m_iCurState)
		SetState(STATE_NONE);
}

void StateMachine::RunMachine(void* pData)
{
	if(m_pfnCallback)
		(this->*m_pfnCallback)(pData);
	else if(m_iCurState != STATE_NONE)
	{
		auto itor = m_mStateMap.find(m_iCurState);
		if (itor != m_mStateMap.end())
		{
			m_pfnCallback = itor->second;
			(this->*m_pfnCallback)(pData);
		}
	}
}

int StateMachine::getState() const
{
	return m_iCurState;
}

bool StateMachine::getStateFlag(int state)
{
	return m_iFlag & state;
}

void StateMachine::enableStateFlag(int flag)
{
	m_iFlag |= flag;
}

void StateMachine::disableStateFlag(int flag)
{
	m_iFlag &= ~flag;
}

#pragma warning(pop)