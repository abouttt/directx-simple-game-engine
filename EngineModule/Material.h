#pragma once

#include "EngineUtil.h"

class Texture;

class Material
{
public:
	friend class ResourceManager;
public:
	Material();

public:
	const std::wstring& GetName() const;
	eRenderingMode GetRenderingMode() const;
	const D3DMATERIAL9& GetNativeMaterial();
	Texture* GetTexture() const;
	const D3DCOLORVALUE& GetColor() const;

	void SetRenderingMode(const eRenderingMode mode);
	void SetTexture(Texture* const texture);
	void SetColor(const D3DXCOLOR& color);
	void SetAlpha(const float alpha);

private:
	void setNativeMaterial(const std::wstring* const name, const eRenderingMode mode, const D3DMATERIAL9& nativeMtrl, Texture* const texture);

private:
	const std::wstring* mName;
	eRenderingMode mRenderingMode;
	D3DMATERIAL9 mD3DMaterial;
	Texture* mTexture;
};

