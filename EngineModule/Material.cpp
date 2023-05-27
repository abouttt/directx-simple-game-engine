#include "pch.h"
#include "Material.h"

Material::Material()
	: mName(nullptr)
	, mRenderingMode(eRenderingMode::Opaque)
	, mD3DMaterial(WHITE_MTRL)
	, mTexture(nullptr)
{
}

eRenderingMode Material::GetRenderingMode() const
{
	return mRenderingMode;
}

const D3DMATERIAL9& Material::GetNativeMaterial()
{
	return mD3DMaterial;
}

Texture* Material::GetTexture() const
{
	return mTexture;
}

const D3DCOLORVALUE& Material::GetColor() const
{
	return mD3DMaterial.Diffuse;
}

const std::wstring& Material::GetName() const
{
	return *mName;
}

void Material::SetRenderingMode(const eRenderingMode mode)
{
	mRenderingMode = mode;
}

void Material::SetTexture(Texture* const texture)
{
	mTexture = texture;
}

void Material::SetColor(const D3DXCOLOR& color)
{
	mD3DMaterial.Diffuse = color;
	mD3DMaterial.Ambient = color;
	mD3DMaterial.Specular = color;
	mD3DMaterial.Emissive = COLOR_BLACK;
	mD3DMaterial.Power = 8.0f;
}

void Material::SetAlpha(const float alpha)
{
	mD3DMaterial.Diffuse.a = std::clamp(alpha, 0.f, 1.f);
}

void Material::setNativeMaterial(const std::wstring* const name, const eRenderingMode mode, const D3DMATERIAL9& nativeMtrl, Texture* const texture)
{
	mName = name;
	mRenderingMode = mode;
	mD3DMaterial = nativeMtrl;
	mTexture = texture;
}
