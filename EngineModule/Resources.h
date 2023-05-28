#pragma once

class Material;
class Mesh;
class Texture;
enum class eRenderingMode;

class Resources
{
public:
	friend class GameEngine;
public:
	Resources() = delete;
	Resources(const Resources&) = delete;
	Resources& operator=(Resources&&) = delete;
	~Resources() = delete;

public:
	static Material* GetMaterial(const std::wstring& name);
	static Mesh* GetMesh(const std::wstring& name);
	static Texture* GetTexture(const std::wstring& name);

	static bool AddMaterial(const std::wstring& name, const eRenderingMode mode, const D3DMATERIAL9& nativeMtrl, Texture* const texture);
	static bool AddNativeMesh(const std::wstring& name, ID3DXMesh* d3dMesh);
	static bool LoadNativeTexture(const std::wstring& name, const std::wstring& path);

private:
	static bool init();

private:
	static bool mbInit;
	static std::unordered_map<std::wstring, std::unique_ptr<Material>> mMaterials;
	static std::unordered_map<std::wstring, std::unique_ptr<Mesh>> mMeshes;
	static std::unordered_map<std::wstring, std::unique_ptr<Texture>> mTextures;
};

