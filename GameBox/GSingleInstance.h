#ifndef __GSINGLEINSTANCE__
#define __GSINGLEINSTANCE__

#define GSingleIns(TYPE) \
	friend class GSingleInstance<TYPE>; \
private: \
	TYPE(); \
	~TYPE()

template<typename _Ty>
class GSingleInstance{
public:
	static _Ty* getInstance(){
		if(m_instance == nullptr)
			m_instance = new _Ty();
		return m_instance;
	};
	static void destroyInstance(){
		if(m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	};
private:
	static _Ty* m_instance;
};

template<typename _Ty>
_Ty* GSingleInstance<_Ty>::m_instance = nullptr;



#endif