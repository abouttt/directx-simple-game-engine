#pragma once

//
// Enum
//

enum class eRenderingMode
{
	Opaque,
	Transparency,
	Cutout,
};

// Util Func

std::wstring StringToWString(const std::string& str);
std::string WStringToString(const std::wstring& wstr);

//
// Color
//

const D3DXCOLOR COLOR_WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR COLOR_BLACK(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR COLOR_GRAY(D3DCOLOR_XRGB(128, 128, 128));
const D3DXCOLOR COLOR_RED(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR COLOR_GREEN(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR COLOR_BLUE(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR COLOR_YELLOW(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR COLOR_CYAN(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR COLOR_MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

//
// Materials
//

D3DMATERIAL9 InitMtrl(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXCOLOR emissive, const float power);

const D3DMATERIAL9 WHITE_MTRL = InitMtrl(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_BLACK, 8.0f);
const D3DMATERIAL9 RED_MTRL = InitMtrl(COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, 8.0f);
const D3DMATERIAL9 GREEN_MTRL = InitMtrl(COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_BLACK, 8.0f);
const D3DMATERIAL9 BLUE_MTRL = InitMtrl(COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLACK, 8.0f);
const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK, 8.0f);

//
// Mesh
//

ID3DXMesh* GetCubeMesh(IDirect3DDevice9* const device);
ID3DXMesh* GetSphereMesh(IDirect3DDevice9* const device);
ID3DXMesh* GetQuadMesh(IDirect3DDevice9* const device);
void SetNormalFVF(IDirect3DDevice9* const device, ID3DXMesh** const outMesh);
void SetTextureFVF(IDirect3DDevice9* const device, ID3DXMesh** const outMesh);

//
// Vertex
//

struct Vertex
{
	Vertex()
		: X(0), Y(0), Z(0)
		, NX(0), NY(0), NZ(0)
		, U(0), V(0)
	{}

	Vertex(float x, float y, float z,
		float nx, float ny, float nz,
		float u, float v)
		: X(x), Y(y), Z(z)
		, NX(nx), NY(ny), NZ(nz)
		, U(u), V(v)
	{}

	float X, Y, Z;
	float NX, NY, NZ;
	float U, V;

	static const DWORD FVF;
};
