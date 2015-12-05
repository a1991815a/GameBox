#ifndef __GVERTEX__
#define __GVERTEX__
#include "DXUtils.h"

struct GVertex_p3{
	float x, y, z;
	static const DWORD fvf = D3DFVF_XYZ;

	D3DXVECTOR3* getPosition(){
		return (D3DXVECTOR3*)&x;
	};
	const D3DXVECTOR3* getPosition() const{
		return (D3DXVECTOR3*)&x;
	};
};

struct GVertex_p3_c1
	:public GVertex_p3
{
	D3DCOLOR color;
	static const DWORD fvf = GVertex_p3::fvf | D3DFVF_DIFFUSE;
};

struct GVertex_p3_n3_c1
	:public GVertex_p3
{
	float nx, ny, nz;
	D3DCOLOR color;
	static const DWORD fvf = GVertex_p3::fvf | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

	D3DXVECTOR3* getNormal(){
		return (D3DXVECTOR3*)&nx;
	};
	const D3DXVECTOR3* getNormal() const{
		return (D3DXVECTOR3*)&nx;
	};
};

struct GVertex_p3_n3_c1_t1
	:public GVertex_p3_n3_c1
{
	float u1, v1;
	static const DWORD fvf = GVertex_p3_n3_c1::fvf | D3DFVF_TEX1;
	void setUV(float u, float v){
		u1 = u;
		v1 = v;
	};
};

struct GVertex_p3_n3_c1_t2
	:public GVertex_p3_n3_c1_t1
{
	float u2, v2;
	static const DWORD fvf = GVertex_p3_n3_c1::fvf | D3DFVF_TEX2;
	void setUV(float u, float v){
		u1 = u;
		v1 = v;
		u2 = u;
		v2 = v;
	};
};

struct GVertex_p3_n3_c1_t3
	:public GVertex_p3_n3_c1_t2
{
	float u3, v3;
	static const DWORD fvf = GVertex_p3_n3_c1::fvf | D3DFVF_TEX3;
	void setUV(float u, float v){
		u1 = u;
		v1 = v;
		u2 = u;
		v2 = v;
		u3 = u;
		v3 = v;
	};
};

struct GVertex_p3_n3_c1_t4
	:public GVertex_p3_n3_c1_t3
{
	float u4, v4;
	static const DWORD fvf = GVertex_p3_n3_c1::fvf | D3DFVF_TEX4;
	void setUV(float u, float v){
		u1 = u;
		v1 = v;
		u2 = u;
		v2 = v;
		u3 = u;
		v3 = v;
		u4 = u;
		v4 = v;
	};
};

struct GVertex_p3_n3_c1_t5
	:public GVertex_p3_n3_c1_t4
{
	float u5, v5;
	static const DWORD fvf = GVertex_p3_n3_c1::fvf | D3DFVF_TEX5;
	void setUV(float u, float v){
		u1 = u;
		v1 = v;
		u2 = u;
		v2 = v;
		u3 = u;
		v3 = v;
		u4 = u;
		v4 = v;
		u5 = u;
		v5 = v;
	};
};

struct GVertex_p3_n3_c1_t6
	:public GVertex_p3_n3_c1_t5
{
	float u6, v6;
	static const DWORD fvf = GVertex_p3_n3_c1::fvf | D3DFVF_TEX6;
	void setUV(float u, float v){
		u1 = u;
		v1 = v;
		u2 = u;
		v2 = v;
		u3 = u;
		v3 = v;
		u4 = u;
		v4 = v;
		u5 = u;
		v5 = v;
		u6 = u;
		v6 = v;
	};
};

struct GVertex_p3_n3_c1_t7
	:public GVertex_p3_n3_c1_t6
{
	float u7, v7;
	static const DWORD fvf = GVertex_p3_n3_c1::fvf | D3DFVF_TEX7;
	void setUV(float u, float v){
		u1 = u;
		v1 = v;
		u2 = u;
		v2 = v;
		u3 = u;
		v3 = v;
		u4 = u;
		v4 = v;
		u5 = u;
		v5 = v;
		u6 = u;
		v6 = v;
		u7 = u;
		v7 = v;
	};
};

struct GVertex_p3_n3_c1_t8
	:public GVertex_p3_n3_c1_t7
{
	float u8, v8;
	static const DWORD fvf = GVertex_p3_n3_c1::fvf | D3DFVF_TEX8;
	void setUV(float u, float v){
		u1 = u;
		v1 = v;
		u2 = u;
		v2 = v;
		u3 = u;
		v3 = v;
		u4 = u;
		v4 = v;
		u5 = u;
		v5 = v;
		u6 = u;
		v6 = v;
		u7 = u;
		v7 = v;
		u8 = u;
		v8 = v;
	};
};
#endif