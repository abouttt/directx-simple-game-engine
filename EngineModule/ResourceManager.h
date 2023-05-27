#pragma once

class Material;
class Mesh;
class Texture;
enum class eRenderingMode;

class ResourceManager
{
public:
	friend class GameEngine;
public:
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	~ResourceManager() = delete;

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

