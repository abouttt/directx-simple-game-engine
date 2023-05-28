#include "pch.h"
#include "Mesh.h"
#include "Material.h"
#include "Matrix.h"
#include "MeshComponent.h"
#include "RenderingEngine.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TransformComponent.h"

MeshComponent::MeshComponent()
	: mMesh(nullptr)
	, mMaterial(ResourceManager::GetMaterial(_T("Default-Material")))
{
	RenderingEngine::AddMeshComponent(this);
}

MeshComponent::MeshComponent(Mesh* const mesh)
	: mMesh(mesh)
	, mMaterial(ResourceManager::GetMaterial(_T("Default-Material")))
{
	RenderingEngine::AddMeshComponent(this);
}

MeshComponent::MeshComponent(Mesh* const mesh, Material* const material)
	: mMesh(mesh)
	, mMaterial(material)
{
	RenderingEngine::AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	RenderingEngine::RemoveMeshComponent(this);
}

Mesh* MeshComponent::GetMesh()
{
	return mMesh;
}

Material* MeshComponent::GetMaterial()
{
	return mMaterial;
}

void MeshComponent::SetMesh(Mesh* const mesh)
{
	mMesh = mesh;
}

void MeshComponent::SetMaterial(Material* const material)
{
	mMaterial = material;
}

void MeshComponent::render(IDirect3DDevice9* const device)
{
	if (!mMesh)
	{
		return;
	}

	auto matWorld = GetTransform()->GetMatrix();
	D3DXMATRIX dm;
	std::memcpy(&dm.m, &matWorld.M, sizeof(D3DXMATRIX));
	//std::copy(&matWorld.M[0][0], &matWorld.M[0][0] + 4 * 4, &dm.m[0][0]);
	device->SetTransform(D3DTS_WORLD, &dm);

	D3DMATERIAL9 nativeMtrl;
	::ZeroMemory(&nativeMtrl, sizeof(D3DMATERIAL9));
	device->SetMaterial(&nativeMtrl);
	device->SetTexture(0, nullptr);

	if (mMaterial)
	{
		switch (mMaterial->GetRenderingMode())
		{
		case eRenderingMode::Cutout:
			device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			break;
		default:
			device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
			break;
		}

		device->SetMaterial(&mMaterial->GetNativeMaterial());

		auto texture = mMaterial->GetTexture();
		if (texture)
		{
			device->SetTexture(0, texture->GetNativeTexture());
		}
	}

	mMesh->GetNativeMesh()->DrawSubset(0);
}
