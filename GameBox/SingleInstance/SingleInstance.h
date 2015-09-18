#ifndef __SINGLEINSTANCE__
#define __SINGLEINSTANCE__


/*
	单例模型定义宏
*/
#define DEFINE_PRIVATE_INSTANCE(INS)		\
private:									\
	INS();									\
	~INS();									\
	friend class SingleInstance<INS>


template<typename _INS>
class SingleInstance{
public:
	static _INS* getInstance() {
		if (m_instance == nullptr)
			m_instance = new _INS();
		return m_instance;
	};
	static void destroyInstance() {
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	};
private:
	static _INS* m_instance;
};

template<typename _INS>
_INS* SingleInstance<_INS>::m_instance = nullptr;


#endif