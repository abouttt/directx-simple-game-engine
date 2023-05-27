#include "pch.h"
#include "MeshComponent.h"
#include "RenderEngine.h"
#include "ResourceManager.h"

MeshComponent::MeshComponent()
	: mMesh(nullptr)
	, mMaterial(ResourceManager::GetMaterial(_T("Default-Material")))
{
	RenderEngine::AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	RenderEngine::RemoveMeshComponent(this);
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
}
