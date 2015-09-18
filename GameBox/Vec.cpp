#include "Vec.h"

Vec2::Vec2()
	:x(0), y(0)
{

}

Vec2::Vec2(float x, float y)
	:x(x), y(y)
{

}

Vec2::Vec2(const Size& size)
	:x(size.width), y(size.height)
{

}

const Vec2& Vec2::operator/=(float factor)
{
	x /= factor;
	y /= factor;
	return *this;
}

Vec2 Vec2::operator/(const Vec2& obj) const
{
	Vec2 vec;
	vec.x = x / obj.x;
	vec.y = y / obj.y;
	return vec;
}

Vec2 Vec2::operator/(float factor) const
{
	Vec2 vec;
	vec.x = x / factor;
	vec.y = y / factor;
	return vec;
}

const Vec2& Vec2::operator+=(const Vec2& obj)
{
	x += obj.x;
	y += obj.y;
	return *this;
}

Vec2 Vec2::operator+(const Vec2& obj) const
{
	Vec2 vec;
	vec.x = x + obj.x;
	vec.y = y + obj.y;
	return vec;
}

Vec2 Vec2::operator+(float factor) const
{
	Vec2 vec;
	vec.x = x + factor;
	vec.y = y + factor;
	return vec;
}

const Vec2& Vec2::operator-=(const Vec2& obj)
{
	x -= obj.x;
	y -= obj.y;
	return *this;
}

Vec2 Vec2::operator-(const Vec2& obj) const
{
	Vec2 vec;
	vec.x = x - obj.x;
	vec.y = y - obj.y;
	return vec;
}

Vec2 Vec2::operator-(float factor) const
{
	Vec2 vec;
	vec.x = x - factor;
	vec.y = y - factor;
	return vec;
}

bool Vec2::operator!=(const Vec2& obj) const
{
	return !(*this == obj);
}

bool Vec2::operator==(const Vec2& obj) const
{
	return x == obj.x && y == obj.y;
}

const Vec2& Vec2::operator+=(float factor)
{
	x += factor;
	y += factor;
	return *this;
}

const Vec2& Vec2::operator-=(float factor)
{
	x -= factor;
	y -= factor;
	return *this;
}

const Vec2& Vec2::operator*=(float factor)
{
	x *= factor;
	y *= factor;
	return *this;
}

Vec2 Vec2::operator*(const Vec2& obj) const
{
	Vec2 vec;
	vec.x = x * obj.x;
	vec.y = x * obj.y;
	return vec;
}

Vec2 Vec2::operator*(float factor) const
{
	Vec2 vec;
	vec.x = x * factor;
	vec.y = y * factor;
	return vec;
}

const Vec2& Vec2::operator/=(const Vec2& obj)
{
	x /= obj.x;
	y /= obj.y;
	return *this;
}

const Vec2& Vec2::operator*=(const Vec2& obj)
{
	x *= obj.x;
	y *= obj.y;
	return *this;
}

const Vec2& Vec2::operator=(const Vec2& obj)
{
	x = obj.x;
	y = obj.y;
	return *this;
}

/*
	ÈýÎ¬ÏòÁ¿
*/
Vec3::Vec3()
	:x(0), y(0), z(0)
{

}

Vec3::Vec3(float x, float y, float z)
	:x(x), y(y), z(z)
{

}

const Vec3& Vec3::operator/=(float factor)
{
	x /= factor;
	y /= factor;
	return *this;
}

Vec3 Vec3::operator/(const Vec3& obj) const
{
	Vec3 vec;
	vec.x = x / obj.x;
	vec.y = y / obj.y;
	vec.z = z / obj.z;
	return vec;
}

Vec3 Vec3::operator/(float factor) const
{
	Vec3 vec;
	vec.x = x / factor;
	vec.y = y / factor;
	vec.z = z / factor;
	return vec;
}

const Vec3& Vec3::operator+=(const Vec3& obj)
{
	x += obj.x;
	y += obj.y;
	z += obj.z;
	return *this;
}

Vec3 Vec3::operator+(const Vec3& obj) const
{
	Vec3 vec;
	vec.x = x + obj.x;
	vec.y = y + obj.y;
	vec.z = z + obj.z;
	return vec;
}

Vec3 Vec3::operator+(float factor) const
{
	Vec3 vec;
	vec.x = x + factor;
	vec.y = y + factor;
	vec.z = z + factor;
	return vec;
}

const Vec3& Vec3::operator-=(const Vec3& obj)
{
	x -= obj.x;
	y -= obj.y;
	z -= obj.z;
	return *this;
}

Vec3 Vec3::operator-(const Vec3& obj) const
{
	Vec3 vec;
	vec.x = x - obj.x;
	vec.y = y - obj.y;
	vec.z = z - obj.z;
	return vec;
}

Vec3 Vec3::operator-(float factor) const
{
	Vec3 vec;
	vec.x = x - factor;
	vec.y = y - factor;
	vec.z = z - factor;
	return vec;
}

bool Vec3::operator!=(const Vec3& obj) const
{
	return !(*this == obj);
}

bool Vec3::operator==(const Vec3& obj) const
{
	return x == obj.x && y == obj.y && z == obj.z;
}

const Vec3& Vec3::operator+=(float factor)
{
	x += factor;
	y += factor;
	z += factor;
	return *this;
}

const Vec3& Vec3::operator-=(float factor)
{
	x -= factor;
	y -= factor;
	z -= factor;
	return *this;

}

const Vec3& Vec3::operator*=(float factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

Vec3 Vec3::operator*(const Vec3& obj) const
{
	Vec3 vec;
	vec.x = x * obj.x;
	vec.y = y * obj.y;
	vec.z = z * obj.z;
	return vec;
}

Vec3 Vec3::operator*(float factor) const
{
	Vec3 vec;
	vec.x = x * factor;
	vec.y = y * factor;
	vec.z = z * factor;
	return vec;
}

const Vec3& Vec3::operator/=(const Vec3& obj)
{
	x /= obj.x;
	y /= obj.y;
	z /= obj.z;
	return *this;
}

const Vec3& Vec3::operator*=(const Vec3& obj)
{
	x *= obj.x;
	y *= obj.y;
	z *= obj.z;
	return *this;
}

const Vec3& Vec3::operator=(const Vec3& obj)
{
	x = obj.x;
	y = obj.y;
	z = obj.z;
	return *this;
}



Size::Size()
	:width(0), height(0)
{

}

Size::Size(float width, float height)
	:width(width), height(height)
{

}

Size::Size(const Vec2& vec)
	:width(vec.x), height(vec.y)
{
	
}

const Size& Size::operator/=(float factor)
{
	width /= factor;
	height /= factor;
	return *this;
}

Size Size::operator/(float factor) const
{
	Size size;
	size.width = width / factor;
	size.height = height / factor;

	return size;
}

const Size& Size::operator+=(const Size& obj)
{
	width += obj.width;
	height += obj.height;
	return *this;
}

Size Size::operator+(const Size& obj) const
{
	Size size;
	size.width = width + obj.width;
	size.height = height + obj.height;

	return size;
}

const Size& Size::operator-=(const Size& obj)
{
	width -= obj.width;
	height -= obj.height;
	return *this;
}

Size Size::operator-(const Size& obj) const
{
	Size size;
	size.width = width - obj.width;
	size.height = height - obj.height;

	return size;
}

bool Size::operator!=(const Size& obj) const
{
	return !(*this == obj);
}

bool Size::operator==(const Size& obj) const
{
	return width == obj.width && height == obj.height;
}

const Size& Size::operator*=(float factor)
{
	width *= factor;
	height *= factor;
	return *this;
}

Size Size::operator*(float factor) const
{
	Size size;
	size.width = width * factor;
	size.height = height * factor;

	return size;
}

const Size& Size::operator=(const Size& obj)
{
	width = obj.width;
	height = obj.height;
	return *this;
}

Rect::Rect(float x, float y, float width, float height)
	:x(x), y(y), width(width), height(height)
{
}

Rect::Rect(const Vec2& pos, const Size& size)
	: x(pos.x), y(pos.y), width(size.width), height(size.height)
{

}

const Rect& Rect::operator-=(const Vec2& obj)
{
	x -= obj.x;
	y -= obj.y;
	return *this;
}

Rect Rect::operator-(const Vec2& obj) const
{
	Rect rect = *this;
	rect.x -= obj.x;
	rect.y -= obj.y;
	return rect;
}

const Rect& Rect::operator-=(const Size& obj)
{
	width -= obj.width;
	height -= obj.height;
	return *this;
}

Rect Rect::operator-(const Size& obj) const
{
	Rect rect = *this;
	rect.width -= obj.width;
	rect.height -= obj.height;
	return rect;
}

bool Rect::operator!=(const Rect& obj) const
{
	return !(*this == obj);
}

bool Rect::operator==(const Rect& obj) const
{
	return (
		x == obj.x &&
		y == obj.y &&
		width == obj.width &&
		height == obj.height
		);
}

const Rect& Rect::operator+=(const Size& obj)
{
	width += obj.width;
	height += obj.height;
	return *this;
}

const Rect& Rect::operator+=(const Vec2& obj)
{
	x += obj.x;
	y += obj.y;
	return *this;
}

Rect Rect::operator+(const Vec2& obj) const
{
	Rect rect = *this;
	rect.x += obj.x;
	rect.y += obj.y;
	return rect;
}

Rect Rect::operator+(const Size& obj) const
{
	Rect rect = *this;
	rect.width += obj.width;
	rect.height += obj.height;
	return rect;
}

const Rect& Rect::operator=(const Rect& obj)
{
	x = obj.x;
	y = obj.y;
	width = obj.width;
	height = obj.height;
	return *this;
}

bool Rect::ContainsPoint(const Vec2& point) const
{
	return (
		point.x >= x &&
		point.y >= y &&
		point.x <= x + width &&
		point.y <= y + height
		);
}

