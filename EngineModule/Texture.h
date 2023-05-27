#pragma once

class Texture
{
public:
	Texture();
	~Texture();

public:
	IDirect3DTexture9* GetNativeTexture();
	UINT GetWidth() const;
	UINT GetHeight() const;
	D3DTEXTUREFILTERTYPE GetFilterMode() const;
	const std::wstring& GetName() const;

	void SetFilterMode(const D3DTEXTUREFILTERTYPE filterType);

private:
	void setNativeTexture(const std::wstring* const name, IDirect3DTexture9* const texture);

private:
	const std::wstring* mName;
	IDirect3DTexture9* mD3DTexture;
	D3DSURFACE_DESC mDesc;
};

