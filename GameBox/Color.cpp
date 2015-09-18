#include "Color.h"




Color4f::Color4f()
	:r(0), g(0), b(0), a(0)
{

}

Color4f::Color4f(float r, float g, float b, float a)
	:r(r), g(g), b(b), a(a)
{

}

Color4f::Color4f(const D3DCOLOR& color)
{
	a = ((color & 0xFF000000) >> 24) / 255.0f;
	r = ((color & 0x00FF0000) >> 16) / 255.0f;
	g = ((color & 0x0000FF00) >> 8) / 255.0f;
	b = (color & 0x000000FF) / 255.0f;
}

const Color4f& Color4f::operator+=(const Color4f& color)
{
	r += color.r;
	g += color.g;
	b += color.b;
	a += color.a;
	return *this;
}

Color4f Color4f::operator+(const Color4f& color) const
{
	Color4f ret_color = *this;
	ret_color += color;
	return ret_color;
}

const Color4f& Color4f::operator-=(const Color4f& color)
{
	r -= color.r;
	g -= color.g;
	b -= color.b;
	a -= color.a;
	return *this;
}

Color4f Color4f::operator-(const Color4f& color) const
{
	Color4f ret_color = *this;
	ret_color -= color;
	return ret_color;
}

const Color4f& Color4f::operator*=(float weight)
{
	r *= weight;
	g *= weight;
	b *= weight;
	a *= weight;
	return *this;
}

Color4f Color4f::operator*(float weight) const
{
	Color4f ret_color = *this;
	ret_color *= weight;
	return ret_color;
}

Color4f Color4f::operator*(const Color4f& color) const
{
	Color4f ret_color = *this;
	ret_color *= color;
	return ret_color;
}

const Color4f& Color4f::operator/=(float weight)
{
	r /= weight;
	g /= weight;
	b /= weight;
	a /= weight;
	return *this;
}

Color4f Color4f::operator/(float weight) const
{
	Color4f ret_color = *this;
	ret_color /= weight;
	return ret_color;
}

const Color4f& Color4f::operator*=(const Color4f& color)
{
	r *= color.r;
	g *= color.g;
	b *= color.b;
	a *= color.a;
	return *this;
}

Color4f Color4f::blend(const Color4f& color, const Color4f& src_weight, const Color4f& des_weight) const
{
	Color4f ret_color = *this;
	ret_color = (ret_color * src_weight) + (color * des_weight);
	return ret_color;
}

Color4f Color4f::blend(const Color4f& color, float src_weight, float des_weight) const
{
	Color4f ret_color = *this;
	ret_color = (ret_color * src_weight) + (color * des_weight);
	return ret_color;
}

D3DCOLOR Color4f::toD3DColor() const
{
	D3DCOLOR color = 0;
	size_t aa = ((size_t)(a * 255.0f)) << 24;
	size_t rr = ((size_t)(r * 255.0f)) << 16;
	size_t gg = ((size_t)(g * 255.0f)) << 8;
	size_t bb = ((size_t)(b * 255.0f));
	color = aa + rr + gg + bb;
	return color;
}

bool Color4f::operator!=(const Color4f& color) const
{
	return !(*this == color);
}

bool Color4f::operator==(const Color4f& color) const
{
	return (
		r == color.r &&
		g == color.g &&
		b == color.b &&
		a == color.a
		);
}

const Color4f& Color4f::operator=(const Color4f& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	return *this;
}
