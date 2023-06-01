#include "pch.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Resources.h"
#include "Texture.h"
#include "TransformComponent.h"

MeshComponent::MeshComponent()
	: mMesh(nullptr)
	, mMaterial(Resources::GetMaterial(_T("Default-Material")))
{
	Renderer::AddMeshComponent(this);
}

MeshComponent::MeshComponent(Mesh* const mesh)
	: mMesh(mesh)
	, mMaterial(Resources::GetMaterial(_T("Default-Material")))
{
	Renderer::AddMeshComponent(this);
}

MeshComponent::MeshComponent(Mesh* const mesh, Material* const material)
	: mMesh(mesh)
	, mMaterial(material)
{
	Renderer::AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	Renderer::RemoveMeshComponent(this);
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

void MeshComponent::OnEnable()
{
}

void MeshComponent::OnDisable()
{
}

void MeshComponent::render(IDirect3DDevice9* const device)
{
	if (!mMesh)
	{
		return;
	}

	auto matWorld = GetTransform()->GetMatrix();
	device->SetTransform(D3DTS_WORLD, &matWorld);

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
