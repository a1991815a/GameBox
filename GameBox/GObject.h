#ifndef __GOBJECT__
#define __GOBJECT__
#include "Ref.h"
#include "DXUtils.h"
#include "GObjectTypes.h"

#pragma warning(disable:4800)

class GObject: public Ref{
protected:
	GObject(GObjectTypes type)
		:m_eType(type)
	{};
public:
	GObject()
		:m_eType(GT_NONE)
	{};

	inline const std::string& getName() const{ return m_sName; };
	inline int getTag() const{ return m_iTag; };
	inline bool isVisiable() const{ return m_bVisiable; };
	inline bool isEnable() const{ return m_bEnable; };
	inline GObjectTypes getType() const{ return m_eType; };
	inline int getFlag() const{ return m_iFlag; };

	inline void setName(const std::string& _name){ m_sName = _name; };
	inline void setTag(int _tag){ m_iTag = _tag; };
	inline void setVisiable(bool _visiable){ m_bVisiable = _visiable; };
	inline void setEnabel(bool _enable){ m_bEnable = _enable; };

	inline void setFlag(int _flag){ m_iFlag = _flag; };
	inline bool isEnableFlag(int _flag) { return (bool)(m_iFlag & _flag); };
	inline void TurnOnFlag(int _flag) { m_iFlag |= _flag; };
	inline void TurnOffFlag(int _flag) { m_iFlag &= ~_flag; };

private:
	std::string				m_sName;		//名字
	int						m_iTag;			//Tag索引
	const GObjectTypes		m_eType;		//short类型(为了4字节对齐)
	bool					m_bVisiable;	//可见性
	bool					m_bEnable;		//可用性
	int						m_iFlag;		//备用flag
};



#pragma warning(default:4800)

#endif