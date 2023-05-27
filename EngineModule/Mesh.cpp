#include "pch.h"
#include "Mesh.h"

Mesh::Mesh()
	: mName(nullptr)
	, mD3DMesh(nullptr)
{
}

Mesh::~Mesh()
{
	if (mD3DMesh)
	{
		mD3DMesh->Release();
	}
}

const std::wstring& Mesh::GetName() const
{
	return *mName;
}

void Mesh::setNativeMesh(const std::wstring* const name, ID3DXMesh* const d3dMesh)
{
	mName = name;
	mD3DMesh = d3dMesh;
}
