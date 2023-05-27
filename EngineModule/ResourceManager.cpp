#include "pch.h"
#include "EngineUtil.h"
#include "RenderEngine.h"
#include "ResourceManager.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

bool ResourceManager::mbInit = false;
std::unordered_map<std::wstring, std::unique_ptr<Material>> ResourceManager::mMaterials;
std::unordered_map<std::wstring, std::unique_ptr<Mesh>> ResourceManager::mMeshes;
std::unordered_map<std::wstring, std::unique_ptr<Texture>> ResourceManager::mTextures;

Material* ResourceManager::GetMaterial(const std::wstring& name)
{
	auto it = mMaterials.find(name);
	if (it != mMaterials.end())
	{
		return it->second.get();
	}

	return nullptr;
}

Mesh* ResourceManager::GetMesh(const std::wstring& name)
{
	auto it = mMeshes.find(name);
	if (it != mMeshes.end())
	{
		return it->second.get();
	}

	return nullptr;
}

Texture* ResourceManager::GetTexture(const std::wstring& name)
{
	auto it = mTextures.find(name);
	if (it != mTextures.end())
	{
		return it->second.get();
	}

	return nullptr;
}

bool ResourceManager::AddMaterial(const std::wstring& name, const eRenderingMode mode, const D3DMATERIAL9& nativeMtrl, Texture* const texture)
{
	if (mMaterials.find(name) != mMaterials.end())
	{
		return false;
	}

	auto mtrl = std::make_unique<Material>();
	mtrl->setNativeMaterial(&name, mode, nativeMtrl, texture);
	mMaterials[name] = std::move(mtrl);
	return true;
}

bool ResourceManager::AddNativeMesh(const std::wstring& name, ID3DXMesh* d3dMesh)
{
	assert(d3dMesh);

	if (mMeshes.find(name) != mMeshes.end())
	{
		return false;
	}

	auto mesh = std::make_unique<Mesh>();
	mesh->setNativeMesh(&name, d3dMesh);
	mMeshes[name] = std::move(mesh);
	return true;
}

bool ResourceManager::LoadNativeTexture(const std::wstring& name, const std::wstring& path)
{
	if (mTextures.find(name) != mTextures.end())
	{
		return false;
	}

	IDirect3DTexture9* ntexture = nullptr;
	HRESULT hr = D3DXCreateTextureFromFile(RenderEngine::GetDevice(), (_T("../Resources/") + path).c_str(), &ntexture);

	if (FAILED(hr))
	{
		std::wstring failedStr = _T("LoadTexture() - FAILED : Not found ") + (_T("../Resources/") + path);
		::MessageBox(nullptr, failedStr.c_str(), 0, 0);
		return false;
	}

	auto texture = std::make_unique<Texture>();
	texture->setNativeTexture(&name, ntexture);
	mTextures[name] = std::move(texture);
	return true;
}

bool ResourceManager::init()
{
	if (mbInit)
	{
		return false;
	}

	// TODO : Resources 폴더에서 자동으로 바인딩 작업.

	mbInit = true;
	return true;
}
