#include "pch.h"
#include "EngineUtil.h"
#include "Renderer.h"
#include "Resources.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

bool Resources::mbInit = false;
std::unordered_map<std::wstring, std::unique_ptr<Material>> Resources::mMaterials;
std::unordered_map<std::wstring, std::unique_ptr<Mesh>> Resources::mMeshes;
std::unordered_map<std::wstring, std::unique_ptr<Texture>> Resources::mTextures;

Material* Resources::GetMaterial(const std::wstring& name)
{
	auto it = mMaterials.find(name);
	if (it == mMaterials.end())
	{
		return nullptr;
	}

	return it->second.get();
}

Mesh* Resources::GetMesh(const std::wstring& name)
{
	auto it = mMeshes.find(name);
	if (it == mMeshes.end())
	{
		return nullptr;
	}

	return it->second.get();
}

Texture* Resources::GetTexture(const std::wstring& name)
{
	auto it = mTextures.find(name);
	if (it == mTextures.end())
	{
		return nullptr;
		
	}

	return it->second.get();
}

bool Resources::AddMaterial(const std::wstring& name, const eRenderingMode mode, const D3DMATERIAL9& nativeMtrl, Texture* const texture)
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

bool Resources::AddNativeMesh(const std::wstring& name, ID3DXMesh* d3dMesh)
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

bool Resources::LoadNativeTexture(const std::wstring& name, const std::wstring& path)
{
	if (mTextures.find(name) != mTextures.end())
	{
		return false;
	}

	IDirect3DTexture9* ntexture = nullptr;
	HRESULT hr = D3DXCreateTextureFromFile(Renderer::GetDevice(), (_T("../Resources/") + path).c_str(), &ntexture);

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

bool Resources::init()
{
	if (mbInit)
	{
		return false;
	}

	// TODO : Resources 폴더에서 자동으로 바인딩 작업.

	mbInit = true;
	return true;
}
