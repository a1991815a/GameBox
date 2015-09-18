#ifndef __COLOR__
#define __COLOR__
#include <d3d9.h>
#include <d3dx9.h>

struct Color4f{
public:
	Color4f();
	Color4f(float r, float g, float b, float a);
	Color4f(const D3DCOLOR& color);

	const Color4f& operator=(const Color4f& color);

	bool operator==(const Color4f& color) const;
	bool operator!=(const Color4f& color) const;

	const Color4f& operator+=(const Color4f& color);
	Color4f operator+(const Color4f& color) const;

	const Color4f& operator-=(const Color4f& color);
	Color4f operator-(const Color4f& color) const;

	const Color4f& operator*=(float weight);
	Color4f operator*(float weight) const;
	const Color4f& operator/=(float weight);
	Color4f operator/(float weight) const;

	const Color4f& operator*=(const Color4f& color);
	Color4f operator*(const Color4f& color) const;

	Color4f blend(const Color4f& color, const Color4f& src_weight, const Color4f& des_weight) const;
	Color4f blend(const Color4f& color, float src_weight, float des_weight) const;

	D3DCOLOR toD3DColor() const;

	float r, g, b, a;
};

#endif