#pragma once

class Mesh
{
public:
	Mesh();
	~Mesh();

public:
	const std::wstring& GetName() const;

private:
	void setNativeMesh(const std::wstring* const name, ID3DXMesh* const d3dMesh);

private:
	const std::wstring* mName;
	ID3DXMesh* mD3DMesh;
};

