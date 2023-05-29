#pragma once

#include "UIComponent.h"

class TextComponent : public UIComponent
{
public:
	TextComponent();
	~TextComponent();

public:
	void SetSize(const UINT size);
	void SetItalic(const bool bItalic);
	void SetColor(const D3DXCOLOR& color);
	void SetFlag(const DWORD flag);
	void SetFont(const std::wstring& fontName);
	void SetText(const std::wstring& text);

	void Draw(IDirect3DDevice9* const device) override;

private:
	bool init(IDirect3DDevice9* const device);

private:
	ID3DXFont* mFont;
	std::wstring mTextString;
	D3DXFONT_DESC mDesc;
	D3DXCOLOR mColor;
	DWORD mFlag;
};

