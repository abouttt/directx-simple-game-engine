#include "pch.h"
#include "EngineUtil.h"
#include "ImageComponent.h"
#include "Texture.h"
#include "TransformComponent.h"

ImageComponent::ImageComponent()
	: mSprite(nullptr)
	, mTexture(nullptr)
	, mColor(COLOR_WHITE)
{
}

ImageComponent::~ImageComponent()
{
	if (mSprite)
	{
		mSprite->Release();
	}
}

Texture* ImageComponent::GetTexture() const
{
    return mTexture;
}

void ImageComponent::SetTexture(Texture* const texture)
{
	mTexture = texture;
}

void ImageComponent::SetColor(const D3DXCOLOR& color)
{
	mColor = color;
}

void ImageComponent::Draw(IDirect3DDevice9* const device)
{
	if (!mSprite)
	{
		if(!init(device))
		{
			return;
		}
	}

	auto position = GetTransform()->GetPosition();
	auto matrix = GetTransform()->GetMatrix();

	mSprite->SetTransform(&matrix);
	mSprite->Begin(D3DXSPRITE_ALPHABLEND);
	mSprite->Draw(mTexture->GetNativeTexture(), nullptr, nullptr, &position, mColor);
	mSprite->End();
}

bool ImageComponent::init(IDirect3DDevice9* const device)
{
	if (FAILED(D3DXCreateSprite(device, &mSprite)))
	{
		::MessageBox(nullptr, _T("Image/init/D3DXCreateSprite : FAILED"), 0, 0);
		return false;
	}

	return true;
}

