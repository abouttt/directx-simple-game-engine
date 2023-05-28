#pragma once

#include "UIComponent.h"

class Texture;

class ImageComponent : public UIComponent
{
public:
	ImageComponent();
	~ImageComponent();

public:
	Texture* GetTexture() const;
	void SetTexture(Texture* const texture);
	void SetColor(const D3DXCOLOR& color);

	void Draw(IDirect3DDevice9* const device) override;

private:
	ID3DXSprite* mSprite;
	Texture* mTexture;
	D3DXCOLOR mColor;
};

