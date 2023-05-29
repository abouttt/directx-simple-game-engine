#include "pch.h"
#include "Texture.h"

Texture::Texture()
	: mName(nullptr)
	, mD3DTexture(nullptr)
	, mDesc()
{
	::ZeroMemory(&mDesc, sizeof(mDesc));
}

Texture::~Texture()
{
	if (mD3DTexture)
	{
		mD3DTexture->Release();
	}
}

IDirect3DTexture9* Texture::GetNativeTexture()
{
	return mD3DTexture;
}

UINT Texture::GetWidth() const
{
	return mDesc.Width;
}

UINT Texture::GetHeight() const
{
	return mDesc.Height;
}

D3DTEXTUREFILTERTYPE Texture::GetFilterMode() const
{
	return mD3DTexture->GetAutoGenFilterType();
}

const std::wstring& Texture::GetName() const
{
	return *mName;
}

void Texture::SetFilterMode(const D3DTEXTUREFILTERTYPE filterType)
{
	mD3DTexture->SetAutoGenFilterType(filterType);
}

void Texture::setNativeTexture(const std::wstring* const name, IDirect3DTexture9* const texture)
{
	if (mD3DTexture)
	{
		mD3DTexture->Release();
	}

	mName = name;
	mD3DTexture = texture;
	mD3DTexture->GetLevelDesc(0, &mDesc);
}

