#include "pch.h"
#include "EngineUtil.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

D3DMATERIAL9 InitMtrl(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXCOLOR emissive, const float power)
{
	D3DMATERIAL9 mtrl{};
	mtrl.Ambient = ambient;
	mtrl.Diffuse = diffuse;
	mtrl.Specular = specular;
	mtrl.Emissive = emissive;
	mtrl.Power = power;
	return mtrl;
}

ID3DXMesh* GetCubeMesh(IDirect3DDevice9* const device)
{
	ID3DXMesh* mesh = nullptr;
	D3DXCreateBox(device, 1, 1, 1, &mesh, 0);
	SetNormalFVF(device, &mesh);
	SetTextureFVF(device, &mesh);

	Vertex* vertices = nullptr;
	mesh->LockVertexBuffer(0, (void**)&vertices);

	DWORD dwVertices = mesh->GetNumVertices();
	int cnt = 0;
	for (DWORD i = 0; i < dwVertices; i++)
	{
		if (cnt == 0)
		{
			vertices->U = 0;
			vertices->V = 0;
		}
		else if (cnt == 1)
		{
			vertices->U = 1;
			vertices->V = 0;
		}
		else if (cnt == 2)
		{
			vertices->U = 1;
			vertices->V = 1;
		}
		else
		{
			vertices->U = 0;
			vertices->V = 1;
		}

		cnt++;
		if (cnt == 4)
		{
			cnt = 0;
		}

		vertices++;
	}

	mesh->UnlockVertexBuffer();

	return mesh;
}

ID3DXMesh* GetSphereMesh(IDirect3DDevice9* const device)
{
	ID3DXMesh* mesh = nullptr;
	D3DXCreateSphere(device, 0.5f, 50, 50, &mesh, 0);
	SetNormalFVF(device, &mesh);
	SetTextureFVF(device, &mesh);

	Vertex* vertices = nullptr;
	mesh->LockVertexBuffer(0, (void**)&vertices);

	DWORD dwVertices = mesh->GetNumVertices();
	for (DWORD i = 0; i < dwVertices; i++)
	{
		vertices->U = -asinf(vertices->NX) / D3DX_PI + 0.5f;
		vertices->V = -asinf(vertices->NY) / D3DX_PI + 0.5f;
		vertices++;
	}

	mesh->UnlockVertexBuffer();

	return mesh;
}

ID3DXMesh* GetQuadMesh(IDirect3DDevice9* const device)
{
	ID3DXMesh* mesh = nullptr;
	D3DXCreateMeshFVF(
		2,
		4,
		D3DXMESH_MANAGED,
		Vertex::FVF,
		device,
		&mesh);

	Vertex* vertices = nullptr;
	mesh->LockVertexBuffer(0, (void**)&vertices);
	vertices[0] = Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[1] = Vertex(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertices[2] = Vertex(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	mesh->UnlockVertexBuffer();

	// 인덱스 버퍼 채우기.
	WORD* i = nullptr;
	mesh->LockIndexBuffer(0, (void**)&i);
	i[0] = 0; i[1] = 1;  i[2] = 2;
	i[3] = 0; i[4] = 2;  i[5] = 3;
	mesh->UnlockIndexBuffer();

	return mesh;
}

void SetNormalFVF(IDirect3DDevice9* const device, ID3DXMesh** const outMesh)
{
	if (!((*outMesh)->GetFVF() & D3DFVF_NORMAL))
	{
		ID3DXMesh* tempMesh = nullptr;
		(*outMesh)->CloneMeshFVF(
			(*outMesh)->GetOptions(),
			(*outMesh)->GetFVF() | D3DFVF_NORMAL,
			device,
			&tempMesh);

		// 법선 계산.
		D3DXComputeNormals(tempMesh, nullptr);

		(*outMesh)->Release();
		*outMesh = tempMesh;
	}
}

void SetTextureFVF(IDirect3DDevice9* const device, ID3DXMesh** const outMesh)
{
	if (!((*outMesh)->GetFVF() & D3DFVF_TEX1))
	{
		ID3DXMesh* tempMesh = nullptr;
		(*outMesh)->CloneMeshFVF(
			(*outMesh)->GetOptions(),
			(*outMesh)->GetFVF() | D3DFVF_TEX1,
			device,
			&tempMesh);

		(*outMesh)->Release();
		*outMesh = tempMesh;
	}
}
