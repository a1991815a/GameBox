#include "GTerrian.h"
#include "GVertex.h"


bool GTerrian::init(
	float cx, float cz, 
	size_t xCount, size_t zCount, 
	size_t texFactor,
	float xOffset /*= 0*/, float zOffset /*= 0*/,
	float height /*= 0*/)
{
	ID3DXMesh* mesh = nullptr;
	float unit_x = cx / xCount;
	float unit_z = cz / zCount;
	float x_offset = -cx / 2 + xOffset;
	float z_offset = -cz / 2 + zOffset;
	D3DXCreateMeshFVF(
		xCount * zCount * 2,
		(xCount + 1) * (zCount + 1),
		D3DXMESH_32BIT | D3DXMESH_MANAGED,
		GVertex_p3_n3_c1_t3::fvf,
		dxGetDevice(),
		&mesh
		);
	setMesh(mesh);
	GVertex_p3_n3_c1_t3*	vertexes = nullptr;
	DWORD*					indexes = nullptr;
	MESH_LOCK(vertexes, indexes);
	//顶点初始化
	{
		size_t array_index = 0;
		for (size_t row_index = 0; row_index < zCount + 1; ++row_index)
		{
			float zz = row_index * unit_z + z_offset;
			float vv = (1 - (float)row_index / zCount) * texFactor;
			for (size_t col_index = 0; col_index < xCount + 1; ++col_index)
			{
				float uu = (float)col_index / xCount * texFactor;
				float xx = col_index * unit_x + x_offset;
				float yy = height;
				*vertexes[array_index].getPosition() = D3DXVECTOR3(xx, yy, zz);
				vertexes[array_index].color = D3DCOLOR_XRGB(255, 255, 255);
				vertexes[array_index++].setUV(uu, vv);
			}
		}
	}

	//索引初始化
	{
		size_t array_index = 0;
		for (size_t row_index = 0; row_index < zCount; ++row_index)
		{
			for (size_t col_index = 0; col_index < xCount; ++col_index)
			{
				DWORD bottom_left = row_index * (xCount + 1) + col_index;
				DWORD bottom_right = bottom_left + 1;
				DWORD top_left = (row_index + 1) * (xCount + 1) + col_index;
				DWORD top_right = top_left + 1;

				indexes[array_index++] = bottom_left;
				indexes[array_index++] = top_left;
				indexes[array_index++] = bottom_right;

				indexes[array_index++] = bottom_right;
				indexes[array_index++] = top_left;
				indexes[array_index++] = top_right;
			}
		}
	}

	MESH_UNLOCK();
	setAttributeCount(1);
	return true;
}
