#ifndef __GAMEMACRO__
#define __GAMEMACRO__


#define SAFE_RELEASE_COM(p) do{if(p) p->Release(); p = nullptr;} while(0)
#define SAFE_DELETE(p) do{if(p) delete p; p = nullptr; } while(0)
#define SAFE_DELETE_ARRAY(p) do{if(p) delete[] p; p = nullptr; } while(0)

#define CREATE_FUNC(TYPE) \
static TYPE* create(){ \
	TYPE* ret = new TYPE(); \
	if(ret && ret->init()){ \
		ret->autorelease(); \
		return ret; \
	} \
	delete ret; \
	return ret; \
};

#define GASSERT(cond, msg, ...) \
	if(!(cond)) \
	_CrtDbgReport(\
	_CRT_ASSERT, \
	__FILE__, \
	__LINE__, \
	nullptr, \
	msg, ##__VA_ARGS__)
#define GSTATICASSERT(cond, msg) static_assert(cond, msg) 
#define GTHROW_RUNTIME(cond, msg) while(!(cond)) throw std::runtime_error(msg)

#endif