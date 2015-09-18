#ifndef __VEC__
#define __VEC__
#include <d3d9.h>
#include <d3dx9.h>

struct Size;
struct Vec2;
struct Vec3;
struct Rect;

struct Vec2{
	Vec2();
	Vec2(const Size& size);
	Vec2(float x, float y);
	
	const Vec2& operator=(const Vec2& obj);

	const Vec2& operator*=(const Vec2& obj);
	const Vec2& operator/=(const Vec2& obj);
	const Vec2& operator*=(float factor);
	const Vec2& operator/=(float factor);

	const Vec2& operator+=(const Vec2& obj);
	const Vec2& operator-=(const Vec2& obj);
	const Vec2& operator+=(float factor);
	const Vec2& operator-=(float factor);

	Vec2 operator*(const Vec2& obj) const;
	Vec2 operator/(const Vec2& obj) const;
	Vec2 operator*(float factor) const;
	Vec2 operator/(float factor) const;

	Vec2 operator+(const Vec2& obj) const;
	Vec2 operator-(const Vec2& obj) const;
	Vec2 operator+(float factor) const;
	Vec2 operator-(float factor) const;
	
	bool operator==(const Vec2& obj) const;
	bool operator!=(const Vec2& obj) const;

	inline D3DXVECTOR2* getD3DVector() { return (D3DXVECTOR2*)&x; };
	inline const D3DXVECTOR2* getD3DVector() const { return (D3DXVECTOR2*)&x; };

	float x, y;
};

struct Vec3{
	Vec3();
	Vec3(float x, float y, float z);


	const Vec3& operator=(const Vec3& obj);

	const Vec3& operator*=(const Vec3& obj);
	const Vec3& operator/=(const Vec3& obj);
	const Vec3& operator*=(float factor);
	const Vec3& operator/=(float factor);

	const Vec3& operator+=(const Vec3& obj);
	const Vec3& operator-=(const Vec3& obj);
	const Vec3& operator+=(float factor);
	const Vec3& operator-=(float factor);

	Vec3 operator*(const Vec3& obj) const;
	Vec3 operator/(const Vec3& obj) const;
	Vec3 operator*(float factor) const;
	Vec3 operator/(float factor) const;

	Vec3 operator+(const Vec3& obj) const;
	Vec3 operator-(const Vec3& obj) const;
	Vec3 operator+(float factor) const;
	Vec3 operator-(float factor) const;

	bool operator==(const Vec3& obj) const;
	bool operator!=(const Vec3& obj) const;

	inline D3DXVECTOR3* getD3DVector() { return (D3DXVECTOR3*)&x; };
	inline const D3DXVECTOR3* getD3DVector() const { return (D3DXVECTOR3*)&x; };

	float x, y, z;
};

struct Size{
	Size();
	Size(const Vec2& vec);
	Size(float width, float height);
	
	
	const Size& operator=(const Size& obj);

	const Size& operator*=(float factor);
	const Size& operator/=(float factor);
	const Size& operator+=(const Size& obj);
	const Size& operator-=(const Size& obj);

	Size operator*(float factor) const;
	Size operator/(float factor) const;
	Size operator+(const Size& obj) const;
	Size operator-(const Size& obj) const;

	bool operator==(const Size& obj) const;
	bool operator!=(const Size& obj) const;

	float width;
	float height;
};

struct Rect {
	Rect();
	Rect(float x, float y, float width, float height);
	Rect(const Vec2& pos, const Size& size);

	const Rect& operator=(const Rect& obj);
	
	const Rect& operator+=(const Vec2& obj);
	const Rect& operator-=(const Vec2& obj);
	Rect operator+(const Vec2& obj) const;
	Rect operator-(const Vec2& obj) const;

	const Rect& operator+=(const Size& obj);
	const Rect& operator-=(const Size& obj);
	Rect operator+(const Size& obj) const;
	Rect operator-(const Size& obj) const;

	bool operator==(const Rect& obj) const;
	bool operator!=(const Rect& obj) const;

	Vec2& getPos(){
		return *(Vec2*)&x;
	};
	const Vec2& getPos() const{
		return *(const Vec2*)&x;
	};
	Size& getSize(){
		return *(Size*)&width;
	};
	const Size& getSize() const{
		return *(const Size*)&width;
	};
public:
	bool ContainsPoint(const Vec2& point) const;

public:
	float x;
	float y;
	float width;
	float height;
};


#endif