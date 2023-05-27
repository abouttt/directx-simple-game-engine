#pragma once

class CameraComponent;
class MeshComponent;
class LightComponent;
enum class eRenderingMode;

class RenderingEngine
{
public:
	friend class GameEngine;

public:
	RenderingEngine() = delete;
	RenderingEngine(const RenderingEngine&) = delete;
	RenderingEngine& operator=(RenderingEngine&&) = delete;
	~RenderingEngine() = delete;

public:
	static int GetWidth();
	static int GetHeight();
	static IDirect3DDevice9* GetDevice();
	static D3DCOLOR GetBackgroundColor();
	static CameraComponent* GetCurrentCamera();

	static void SetBackgroundColor(const D3DCOLOR color);
	static void SetCurrentCamera(CameraComponent* camera);

	static void AddMeshComponent(MeshComponent* const mesh);
	static void AddLightComponent(LightComponent* const light);
	
	static void RemoveMeshComponent(MeshComponent* const mesh);
	static void RemoveLightComponent(LightComponent* const light);

private:
	static void preRender();
	static void render();
	static void postRender();

	static void updateCamera();
	static void updateLights();
	static void sortTransparencyMeshes();
	static void renderMeshes(std::vector<MeshComponent*>& meshComponents);

	static bool init(const HWND hWnd, const int width, const int height, const bool bWindowed);
	static bool initDevice(const HWND hWnd, const bool bWindowed);
	static void clear();
	static void release();

private:
	static bool mbInit;
	static int mWidth;
	static int mHeight;
	static IDirect3DDevice9* mD3DDevice;
	static D3DCOLOR mBackgroundColor;

	static CameraComponent* mCurrentCamera;
	static std::unordered_map<eRenderingMode, std::vector<MeshComponent*>> mMeshComponents;
	static std::vector<LightComponent*> mLightComponents;
	static DWORD mCurrentLightCount;
};

