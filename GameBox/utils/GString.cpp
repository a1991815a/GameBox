#include "GString.h"
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>
#pragma warning(disable: 4996)

static const size_t max_length = 1024;
static char s_buf[max_length + 1] = { 0 };

//÷ÿ‘ÿ…¢¡–∫Ø ˝

 
 GString GString::FormatString(const char* str, ...)
 {
 	GString return_str = "";
 	va_list ap;
 	va_start(ap, str);
 	int buf_size = _vsnprintf(nullptr, 0, str, ap);
 	if (buf_size <= max_length) {
 		va_end(ap);
 		va_start(ap, str);
 		vsprintf_s(s_buf, max_length + 1, str, ap);
 		return_str += s_buf;
 		memset(s_buf, 0, max_length + 1);
 		va_end(ap);
 	}
 	else
 	{
 		char* tmp_buf = new char[buf_size + 1];
 		memset(tmp_buf, 0, buf_size + 1);
 		va_end(ap);
 		va_start(ap, str);
 		vsprintf_s(tmp_buf, buf_size + 1, str, ap);
 		return_str += tmp_buf;
 		delete[] tmp_buf;
 		va_end(ap);
 	}
 
 	return return_str;
 }

GString::GString()
	:_Mybase()
{}

GString::GString(const GString& str)
	: _Mybase(str)
{}

GString::GString(GString&& str)
	: _Mybase(str)
{}

GString::GString(const char* str)
	: _Mybase(str)
{}

GString::GString(int num)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%d", num);
	_Mybase::operator+=(tmp_str);
}

GString::GString(double num)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%f", num);
	_Mybase::operator+=(tmp_str);
	while(size() > 0 && back() == '0')
		pop_back();
}

GString::GString(char c)
	:_Mybase()
{
	_Mybase::operator+=(c);
}

GString::GString( const wchar_t* wstr )
{
	char* str = nullptr;
	int len= WideCharToMultiByte(CP_ACP,0,wstr,wcslen(wstr),NULL,0,NULL,NULL); 
	str=new char[len+1]; 
	WideCharToMultiByte(CP_ACP,0,wstr,wcslen(wstr),str,len,NULL,NULL); 
	str[len]='\0'; 
	_Mybase::operator+=(str);
	delete[] str;
}

GString::GString(const _Mybase& copy_obj)
	:_Mybase(copy_obj)
{}

GString::GString(const _Mybase&& move_obj)
	:_Mybase(move_obj)
{}

int GString::find(char ch, size_t offset /*= 0*/)
{
	return _Mybase::find(ch, offset);
}

int GString::find(const char* find_str, size_t offset /*= 0*/) const
{
	return _Mybase::find(find_str, offset);
}

int GString::find(const GString& find_str, size_type offset /*=0 */) const
{
	if (find_str.size() == 1)
		return this->find(find_str.c_str());

	while ((offset = find(find_str.front(), offset)) != -1)
	{
		for(size_t i = 1; i < find_str.size(); i++){
			if (find_str.at(i) != this->at(offset + i))
				break;
			else if (i == find_str.size() - 1)
				return offset;
		}
		offset += find_str.size();
		break;
	}
	return -1;
}

int GString::findFinal( char ch, size_type offset /*= 0*/ ) const
{
	int index = -1;
	for (size_t i = offset; i < size(); ++i)
		if(at(i) == ch)
			index = i;
	return index;
}

GString GString::substr(
	const GString& left,
	const GString& right,
	size_type offset /*= 0*/,
	size_type* out_index /*= nullptr*/) const
{
	if (out_index != nullptr)
		*out_index = -1;
	int left_index = -1;
	int right_index = -1;
	left_index = find(left, offset);
	if (left_index == -1)
		return "";
	left_index += left.size();
	right_index = find(right, left_index);
	if (right_index == -1)
		return "";
	if (out_index != nullptr)
		*out_index = right_index + right.size();
	return substr(left_index, right_index - left_index);
}

void GString::emplace(const GString& str, const GString& emplace_str, size_type offset /*= 0*/)
{
	int index = -1;
	while ((index = find(str, offset)) != -1)
	{
		erase(index, str.size());
		insert(index, emplace_str);
	}
}

int GString::toInt() const
{
	return atoi(this->c_str());
}

double GString::toDouble() const
{
	return atof(this->c_str());
}

long GString::toInt_hex() const
{
	long val = 0;
	int index = this->size() - 1;
	int hex = 1;

	for (size_t i = 0; i < 8; ++i, --index, hex *= 16)
	{
		if (index < 0)
			break;
		char num[3] = { 0 };
		num[0] = this->at(index);
		switch (num[0])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			break;
		case 'A':
		case 'a':
			num[0] = '1';
			num[1] = '0';
			break;
		case 'B':
		case 'b':
			num[0] = '1';
			num[1] = '1';
			break;
		case 'C':
		case 'c':
			num[0] = '1';
			num[1] = '2';
			break;
		case 'D':
		case 'd':
			num[0] = '1';
			num[1] = '3';
			break;
		case 'E':
		case 'e':
			num[0] = '1';
			num[1] = '4';
			break;
		case 'F':
		case 'f':
			num[0] = '1';
			num[1] = '5';
			break;
		case 'x':
		case 'X':
			return val;
		default:
			break;
		}
		val += (atoi(num) * hex);
	}

	return val;
}

std::basic_string<wchar_t> GString::toWString() const
{

	wchar_t* wstr = nullptr;
	int len = MultiByteToWideChar(CP_ACP, 0, c_str(), size(), NULL, 0);
	wstr = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, c_str(), size(), wstr, len);
	wstr[len] = '\0';

	std::basic_string<wchar_t> wString = wstr;
	delete[] wstr;

	return wString;
}

std::ostream& operator<<(std::ostream& os, const GString& str) {
	os << str.c_str();
	return os;
};

GString GString::operator+(const int& num) const
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%d", num);
	GString gstr = *this;
	gstr += tmp_str;
	return gstr;
}

GString GString::operator+(const float& num) const
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%f", num);
	GString gstr = *this;
	gstr += tmp_str;
	return gstr;
}

GString GString::operator+(const char* compare_obj) const
{
	return std::operator+(*this, compare_obj);
}

GString GString::operator+(const char& c) const
{
	return std::operator+(*this, c);
}

GString GString::operator+(const GString& str) const
{
	GString gs = *this;
	gs += str;
	return gs;
}

const GString& GString::operator+=(const char* compare_obj)
{
	_Mybase::operator+=(compare_obj);
	return *this;
}

const GString& GString::operator+=(const char& c)
{
	_Mybase::operator+=(c);
	return *this;
}

const GString& GString::operator+=(const int& num)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%d", num);
	*this += tmp_str;
	return *this;
}

const GString& GString::operator+=(const double& num)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%f", num);
	*this += tmp_str;
	while (size() > 0 && back() == '0')
		pop_back();
	return *this;
}

const GString& GString::operator+=(const GString& str)
{
	_Mybase::operator+=(str);
	return *this;
}

const GString& GString::operator<<(const GString& obj)
{
	*this += obj;
	return *this;
}

const GString& GString::operator<<(const int& obj)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%d", obj);
	*this += tmp_str;
	return *this;
}

const GString& GString::operator<<(const double& obj)
{
	char tmp_str[26] = { 0 };
	sprintf_s(tmp_str, "%f", obj);
	*this += tmp_str;
	while (size() > 0 && back() == '0')
		pop_back();
	return *this;
}

const GString& GString::operator<<(const char& obj)
{
	*this += obj;
	return *this;
}

const GString& GString::operator<<(const char* obj)
{
	*this += obj;
	return *this;
}

const GString& GString::operator>>(GString& obj) const
{
	obj += *this;
	return obj;
}

const int& GString::operator>>(int& obj) const
{
	obj = atoi(this->c_str());
	return obj;
}

const double& GString::operator>>(double& obj) const
{
	obj = atof(this->c_str());
	return obj;
}

const char& GString::operator>>(char& obj) const
{
	if (this->size() == 0)
	{
		obj = 0;
		return obj;
	}
	obj = this->front();
	return obj;
}

bool GString::operator==(const char* compare_obj) const
{
	return std::operator==(*this, compare_obj);
}

bool GString::operator==(const GString& str) const
{
	return std::operator==(*this, str);
}

const GString& GString::operator=(const GString& copy_obj)
{
	_Mybase::operator=(copy_obj);
	return *this;
}

const GString& GString::operator=(GString&& move_obj)
{
	_Mybase::operator=(move_obj);
	return *this;
}

std::vector<GString> GString::split(const GString& split_str) const
{
	std::vector<GString> split_text;

	for (
		int cur_index = 0, pre_index = 0;;)
	{
		cur_index = find(split_str.c_str(), pre_index);
		if (npos == cur_index)
		{
			GString gs = _Mybase::substr(pre_index, size() - pre_index);
			if (!gs.empty())
				split_text.push_back(gs);
			break;
		}
		GString gs = _Mybase::substr(pre_index, cur_index - pre_index);
		if (!gs.empty())
			split_text.push_back(gs);
		pre_index = cur_index + split_str.size();
	}

	return split_text;
}

#pragma warning(default: 4996)