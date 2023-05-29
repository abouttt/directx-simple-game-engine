#pragma once

class CameraComponent;
class MeshComponent;
class LightComponent;
class UIComponent;
enum class eRenderingMode;

class Renderer
{
public:
	friend class GameEngine;
	friend class Resources;

public:
	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	~Renderer() = delete;

public:
	static int GetWidth();
	static int GetHeight();
	static D3DCOLOR GetBackgroundColor();
	static CameraComponent* GetCurrentCamera();

	static void SetBackgroundColor(const D3DCOLOR color);
	static void SetCurrentCamera(CameraComponent* camera);

	static void AddMeshComponent(MeshComponent* const mesh);
	static void AddLightComponent(LightComponent* const light);
	static void AddUIComponent(UIComponent* const ui);

	static void RemoveMeshComponent(MeshComponent* const mesh);
	static void RemoveLightComponent(LightComponent* const light);
	static void RemoveUIComponent(UIComponent* const ui);

private:
	static IDirect3DDevice9* getDevice();

	static void preRender();
	static void render();
	static void drawUI();
	static void postRender();

	static void updateCamera();
	static void updateLights();
	static void partitionMeshes();
	static void sortTransparencyMeshes();
	static void renderMeshes(std::vector<MeshComponent*>::iterator begin, std::vector<MeshComponent*>::iterator end);

	static bool init(const HWND hWnd, const int width, const int height, const bool bWindowed);
	static bool initDevice(const HWND hWnd, const bool bWindowed);
	static void initPipeline();
	static void clear();
	static void release();

private:
	static bool mbInit;
	static int mWidth;
	static int mHeight;
	static IDirect3DDevice9* mD3DDevice;
	static D3DCOLOR mBackgroundColor;

	static CameraComponent* mCurrentCamera;
	static std::vector<MeshComponent*> mMeshComponents;
	static std::vector<LightComponent*> mLightComponents;
	static std::vector<UIComponent*> mUIComponents;

	static std::vector<MeshComponent*>::iterator mAlphaRenderBegin;
	static DWORD mCurrentLightCount;
};

