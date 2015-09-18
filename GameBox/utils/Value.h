#ifndef __VALUE__
#define __VALUE__
#include <vector>
#include <unordered_map>
#include "GString.h"
#include <ostream>

#define ValueVector std::vector<Value>
#define ValueMap std::unordered_map<GString, Value>

#ifndef _DOUBLE
typedef float real;
#else
typedef double real;
#endif

class Value{
//联合体
private:
	union ValueUnion
	{
		ValueUnion();
		char _char;
		int _int;
		real _real;
		void* _data;
		GString* _string;
		ValueVector* _vvector;
		ValueMap* _vmap;
	};
public:
	enum ValueTypes
	{
		NONE = 0,
		CHAR,
		INT,
		REAL,
		STRING,
		VVECTOR,
		VMAP,
		DATA
	};

//构造函数
public:
	~Value();
	Value();
	Value(const Value& copy_obj);
	Value(Value&& move_obj);
	Value(char ch);
	Value(int value);
	Value(real Real);
	Value(const GString& str);
	Value(const ValueVector& vvec);
	Value(const ValueMap& vmap);
	Value(void* _data);
	Value(GString&& str);
	Value(ValueVector&& vvec);
	Value(ValueMap&& vmap);
//运算符
public:
	//赋值运算符
	const Value& operator=(const Value& copy_obj);
	const Value& operator=(Value&& copy_obj);
	const Value& operator=(char ch);
	const Value& operator=(int value);
	const Value& operator=(real Real);
	const Value& operator=(const GString& str);
	const Value& operator=(const ValueVector& vvec);
	const Value& operator=(const ValueMap& vmap);
	const Value& operator=(void* data);

	const Value& operator=(GString&& str);
	const Value& operator=(ValueVector&& vvec);
	const Value& operator=(ValueMap&& vmap);
	//关系运算符
	bool operator==(const Value& compare_obj) const;
//API
public:
	void reset();

	char asChar() const;
	int asInt() const;
	real asReal() const;
	const GString& asString() const;
	const ValueVector& asVVector() const;
	const ValueMap& asVMap() const;
	const void* asData() const;

	char& asChar();
	int& asInt();
	real& asReal();
	GString& asString();
	ValueVector& asVVector();
	ValueMap& asVMap();
	void* asData();

	ValueTypes getType() const;

	friend std::ostream& operator<<(std::ostream& os, const Value& val);
	void outputString(GString& out_text) const;
private:
	ValueTypes m_type;
	ValueUnion m_value;
};
#endif