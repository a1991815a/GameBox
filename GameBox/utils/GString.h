#ifndef __GSTRING__
#define __GSTRING__
#include <string>
#include <iosfwd>
#include <unordered_map>
#include <vector>

class GString: public std::basic_string<char, std::char_traits<char>, std::allocator<char>>{
//类型定义
public:
	typedef GString _Myt;
	typedef  std::basic_string<char, std::char_traits<char>, std::allocator<char>> _Mybase;
	typedef  _Mybase::traits_type traits_type;
	typedef  _Mybase::_Alloc allocator_type;
	typedef  _Mybase::_Alty _Alty;
	typedef  _Mybase::value_type value_type;
	typedef  _Mybase::size_type size_type;
	typedef  _Mybase::difference_type difference_type;
	typedef  _Mybase::pointer pointer;
	typedef  _Mybase::const_pointer const_pointer;
	typedef  _Mybase::reference reference;
	typedef  _Mybase::const_reference const_reference;
	typedef  _Mybase::iterator iterator;
	typedef  _Mybase::const_iterator const_iterator;
	typedef  _Mybase::reverse_iterator reverse_iterator;
	typedef  _Mybase::const_reverse_iterator const_reverse_iterator;


//静态函数工具
public:
	static GString FormatString(const char* str, ...);

public:
	GString();
	GString(const GString& str);
	GString(const _Mybase& copy_obj);
	GString(const _Mybase&& move_obj);
	GString(GString&& str);
	GString(const char* str);
	GString(int num);
	GString(double num);
	GString(char c);
	GString(const wchar_t* wstr);

public:
	const GString& operator=(const GString& copy_obj);
	const GString& operator=(GString&& move_obj);
//关系运算符
	bool operator==(const GString& str) const;
	bool operator==(const char* compare_obj) const;
//连接
	GString operator+(const GString& str) const;
	GString operator+(const char* compare_obj) const;
	GString operator+(const char& c) const;
	GString operator+(const int& num) const;
	GString operator+(const float& num) const;

//赋值运算符
	const GString& operator+=(const GString& str);
	const GString& operator+=(const char* compare_obj);
	const GString& operator+=(const char& c);
	const GString& operator+=(const int& num);
	const GString& operator+=(const double& num);

//流操作运算符
	const GString& operator<<(const GString& obj);
	const GString& operator<<(const int& obj);
	const GString& operator<<(const double& obj);
	const GString& operator<<(const char& obj);
	const GString& operator<<(const char* obj);

	const GString& operator>>(GString& obj) const;
	const int& operator>>(int& obj) const;
	const double& operator>>(double& obj) const;
	const char& operator>>(char& obj) const;

//输入输出运算符
	friend std::ostream& operator<<(std::ostream& os, const GString& str);
//API
public:
	//查找
	int find(char ch, size_t offset = 0);
	int find(const char* find_str, size_t offset = 0) const;
	int find(const GString& find_str, size_type offset = 0) const;
	int findFinal(char ch, size_type offset = 0) const;

	GString substr(
		const GString& left, 
		const GString& right, 
		size_type offset = 0, 
		size_type* out_index = nullptr) const;
	//将所有str替换为emplace_str
	void emplace(const GString& str, const GString& emplace_str, size_type offset = 0);

	std::vector<GString> split(const GString& split_str) const;

	//返回index位置上的字符
	std::basic_string<wchar_t> toWString() const;

	//各类转换
	int toInt() const;
	double toDouble() const;
	long toInt_hex() const;

};

#ifdef MSV_100
template<>
class std::tr1::hash<GString>
	: public std::unary_function<GString, size_t>
{	// hash functor
public:
	typedef GString _Kty;

	size_t operator()(const _Kty& _Keyval) const
	{	// hash _Keyval to size_t value by pseudorandomizing transform
		size_t _Val = 2166136261U;
		size_t _First = 0;
		size_t _Last = _Keyval.size();
		size_t _Stride = 1 + _Last / 10;

		for (; _First < _Last; _First += _Stride)
			_Val = 16777619U * _Val ^ (size_t)_Keyval.at(_First);
		return (_Val);
	}
};

typedef std::tr1::hash<GString> gstring_hash;

#else

namespace std {
	template<>
	struct hash<GString>
	{	// hash functor for basic_string
		typedef GString argument_type;
		typedef size_t result_type;
		typedef GString::value_type _Elem;

		size_t operator()(const argument_type& _Keyval) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
			return (_Hash_seq((const unsigned char *)_Keyval.c_str(),
				_Keyval.size() * sizeof(_Elem)));
		}
	};

};

typedef std::hash<GString> gstring_hash;
#endif
#endif