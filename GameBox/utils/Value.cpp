#include "Value.h"

#include <windows.h>

#pragma warning(disable: 4244)

Value::ValueUnion::ValueUnion()
	:_real(NULL)
{}

Value::~Value()
{
	reset();
}

Value::Value()
	: m_type(NONE)
{

}

Value::Value(const Value& copy_obj)
{
	*this = copy_obj;
}

Value::Value(Value&& move_obj)
{
	*this = move_obj;
}

Value::Value(char ch)
{
	*this = ch;
}

Value::Value(int value)
{
	*this = value;
}

Value::Value(real Real)
{
	*this = Real;
}

Value::Value(const GString& str)
{
	*this = str;
}

Value::Value(const ValueVector& vvec)
{
	*this = vvec;
}

Value::Value(const ValueMap& vmap)
{
	*this = vmap;
}

Value::Value(GString&& str)
{
	*this = str;
}

Value::Value(ValueVector&& vvec)
{
	*this = vvec;
}

Value::Value(ValueMap&& vmap)
{
	*this = vmap;
}

Value::Value(void* _data)
{
	reset();
	m_value._data = _data;
	m_type = DATA;
}

const Value& Value::operator=(GString&& str)
{
	reset();
	m_value._string = new GString();
	*m_value._string = std::move(str);
	m_type = STRING;
	return *this;
}

const Value& Value::operator=(ValueVector&& vvec)
{
	reset();
	m_value._vvector = new ValueVector();
	*m_value._vvector = std::move(vvec);
	m_type = VVECTOR;
	return *this;
}

const Value& Value::operator=(ValueMap&& vmap)
{
	reset();
	m_value._vmap = new ValueMap();
	*m_value._vmap = std::move(vmap);
	m_type = VMAP;
	return *this;
}

const Value& Value::operator=(void* data)
{
	reset();
	m_value._data = data;
	m_type = DATA;
	return *this;
}

void Value::reset()
{
	switch (m_type)
	{
	case Value::NONE:
	case Value::CHAR:
	case Value::INT:
	case Value::REAL:
	case Value::DATA:
		break;
	case Value::STRING:
		delete m_value._string;
		break;
	case Value::VVECTOR:
		delete m_value._vvector;
		break;
	case Value::VMAP:
		delete m_value._vmap;
		break;
	default:
		break;
	}
	m_value._real = NULL;
	m_type = NONE;
}

char Value::asChar() const
{
	return m_value._char;
}

char& Value::asChar()
{
	return m_value._char;
}

int Value::asInt() const
{
	if (m_type == STRING)
		return m_value._string->toInt();
	else if (m_type == REAL)
		return (int)m_value._real;
	return m_value._int;
}

int& Value::asInt()
{
	return m_value._int;
}

real Value::asReal() const
{
	if (m_type == STRING)
		return m_value._string->toDouble();
	else if (m_type == INT)
		return (real)m_value._int;
	return m_value._real;
}

real& Value::asReal()
{
	return m_value._real;
}

const GString& Value::asString() const
{
	return *m_value._string;
}

GString& Value::asString()
{
	return *m_value._string;
}

const ValueVector& Value::asVVector() const
{
	return *m_value._vvector;
}

ValueVector& Value::asVVector()
{
	return *m_value._vvector;
}

const ValueMap& Value::asVMap() const
{
	return *m_value._vmap;
}

ValueMap& Value::asVMap()
{
	return *m_value._vmap;
}

const void* Value::asData() const
{
	return m_value._data;
}

void* Value::asData()
{
	return m_value._data;
}

Value::ValueTypes Value::getType() const
{
	return m_type;
}

void Value::outputString(GString& out_text) const
{
	switch (m_type)
	{
	case Value::NONE:
		out_text += "NULL";
		break;
	case Value::CHAR:
		out_text += asChar();
		break;
	case Value::INT:
		out_text +=  asInt();
		break;
	case Value::REAL:
		out_text += asReal();
		break;
	case Value::STRING:
		out_text += asString();
		break;
	case Value::VMAP:
	{
		out_text += "ValueMap: {";

		auto itor = asVMap().begin();
		for (; itor != asVMap().end(); ++itor)
		{
			out_text += "\n";
			out_text += itor->first;
			out_text += " : ";
			itor->second.outputString(out_text);
		}
		out_text += "\n}";
	}
	break;
	case Value::VVECTOR:
	{
		out_text += "ValueVector: {";
		auto itor = asVVector().begin();
		for (; itor != asVVector().end(); ++itor)
		{
			out_text += "\n";
			(*itor).outputString(out_text);
		}
		out_text += "\n}";
	}
	break;
	case Value::DATA:
		out_text += "Data: 0x \n";
		break;
	default:
		break;
	}
}

bool Value::operator==(const Value& compare_obj) const
{
	if (m_type != compare_obj.m_type)
		return false;
	switch (m_type)
	{
	case Value::NONE:
		return true;
	case Value::CHAR:
		return m_value._char == compare_obj.m_value._char;
	case Value::INT:
		return m_value._int == compare_obj.m_value._int;
	case Value::REAL:
		return m_value._real == compare_obj.m_value._real;
	case Value::STRING:
		return *m_value._string == *compare_obj.m_value._string;
	case Value::VVECTOR:
		return *m_value._vvector == *compare_obj.m_value._vvector;
	case Value::VMAP:
		return *m_value._vmap == *compare_obj.m_value._vmap;
	case Value::DATA:
		return m_value._data == compare_obj.m_value._data;
	}
	return false;
}

const Value& Value::operator=(const ValueMap& vmap)
{
	reset();
	m_value._vmap = new ValueMap();
	*m_value._vmap = vmap;
	m_type = VMAP;
	return *this;
}

const Value& Value::operator=(const ValueVector& vvec)
{
	reset();
	m_value._vvector = new ValueVector();
	*m_value._vvector = vvec;
	m_type = VVECTOR;
	return *this;
}

const Value& Value::operator=(const GString& str)
{
	reset();
	m_value._string = new GString();
	*m_value._string = str;
	m_type = STRING;
	return *this;
}

const Value& Value::operator=(real Real)
{
	reset();
	m_value._real = Real;
	m_type = REAL;
	return *this;
}

const Value& Value::operator=(int value)
{
	reset();
	m_value._int = value;
	m_type = INT;
	return *this;
}

const Value& Value::operator=(char ch)
{
	reset();
	m_value._char = ch;
	m_type = CHAR;
	return *this;
}

const Value& Value::operator=(Value&& copy_obj)
{
	reset();
	m_value = copy_obj.m_value;
	m_type = copy_obj.m_type;
	copy_obj.m_type = NONE;
	copy_obj.m_value._real = NULL;
	return *this;
}

const Value& Value::operator=(const Value& copy_obj)
{
	reset();
	switch (copy_obj.m_type)
	{
	case Value::NONE:
	case Value::CHAR:
	case Value::INT:
	case Value::REAL:
	case Value::DATA:
		m_value = copy_obj.m_value;
		break;
	case Value::STRING:
		m_value._string = new GString();
		*m_value._string = *copy_obj.m_value._string;
		break;
	case Value::VVECTOR:
		m_value._vvector = new ValueVector();
		*m_value._vvector = *copy_obj.m_value._vvector;
		break;
	case Value::VMAP:
		m_value._vmap = new ValueMap();
		*m_value._vmap = *copy_obj.m_value._vmap;
		break;
	}
	m_type = copy_obj.m_type;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Value& val) {
	switch (val.m_type)
	{
	case Value::NONE:
		os << "NULL";
		break;
	case Value::CHAR:
		os << val.asChar();
		break;
	case Value::INT:
		os << val.asInt();
		break;
	case Value::REAL:
		os << val.asReal();
		break;
	case Value::STRING:
		os << val.asString();
		break;
	case Value::VMAP:
	{
		os << "ValueMap: {";

		auto itor = val.asVMap().begin();
		for (; itor != val.asVMap().end(); ++itor)
			os << std::endl << itor->first << " : " << itor->second;
		os << std::endl << "}";
	}
		break;
	case Value::VVECTOR:
	{
		os << "ValueVector: {";
		auto itor = val.asVVector().begin();
		for (; itor != val.asVVector().end(); ++itor)
			os << std::endl << *itor;
		os << std::endl << "}";
	}
		break;
	case Value::DATA:
		os << "Data: 0x" << val.m_value._data << std::endl;
		break;
	default:
		break;
	}

	return os;
}
#pragma warning(default: 4244)