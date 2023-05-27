#include "pch.h"
#include "CameraComponent.h"
#include "EngineUtil.h"
#include "LightComponent.h"
#include "Material.h"
#include "MeshComponent.h"
#include "RenderingEngine.h"
#include "TransformComponent.h"

bool RenderingEngine::mbInit = false;
int RenderingEngine::mWidth = 0;
int RenderingEngine::mHeight = 0;
IDirect3DDevice9* RenderingEngine::mD3DDevice = nullptr;
D3DCOLOR RenderingEngine::mBackgroundColor = D3DCOLOR_XRGB(128, 128, 128);
CameraComponent* RenderingEngine::mCurrentCamera = nullptr;
std::unordered_map<eRenderingMode, std::vector<MeshComponent*>> RenderingEngine::mMeshComponents;
std::vector<LightComponent*> RenderingEngine::mLightComponents;
DWORD RenderingEngine::mCurrentLightCount = 0;

int RenderingEngine::GetWidth()
{
	return mWidth;
}

int RenderingEngine::GetHeight()
{
	return mHeight;
}

IDirect3DDevice9* RenderingEngine::GetDevice()
{
	return mD3DDevice;
}

D3DCOLOR RenderingEngine::GetBackgroundColor()
{
	return mBackgroundColor;
}

void RenderingEngine::SetBackgroundColor(const D3DCOLOR color)
{
	mBackgroundColor = color;
}

void RenderingEngine::SetCurrentCamera(CameraComponent* camera)
{
	mCurrentCamera = camera;
}

void RenderingEngine::AddMeshComponent(MeshComponent* const mesh)
{
	assert(mesh);

	auto mode = mesh->GetMaterial()->GetRenderingMode() == eRenderingMode::Opaque ?
		eRenderingMode::Opaque : eRenderingMode::Transparency;
	auto& meshComponents = mMeshComponents[mode];

	if (std::find(meshComponents.begin(), meshComponents.end(), mesh) == meshComponents.end())
	{
		meshComponents.emplace_back(mesh);

		if (mode == eRenderingMode::Transparency)
		{
			sortTransparencyMeshes();
		}
	}
}

void RenderingEngine::AddLightComponent(LightComponent* const light)
{
	assert(light);

	if (std::find(mLightComponents.begin(), mLightComponents.end(), light) == mLightComponents.end())
	{
		light->mIndex = mCurrentLightCount++;
		mD3DDevice->LightEnable(light->mIndex, true);
		mD3DDevice->SetLight(light->mIndex, &light->mD3DLight);
		mLightComponents.emplace_back(light);
	}
}

void RenderingEngine::RemoveMeshComponent(MeshComponent* const mesh)
{
	assert(mesh);

	auto mode = mesh->GetMaterial()->GetRenderingMode() == eRenderingMode::Opaque ?
		eRenderingMode::Opaque : eRenderingMode::Transparency;
	auto& meshComponents = mMeshComponents[mode];

	auto it = std::find(meshComponents.begin(), meshComponents.end(), mesh);
	if (it != meshComponents.end())
	{
		meshComponents.erase(it);
	}
}

void RenderingEngine::RemoveLightComponent(LightComponent* const light)
{
	assert(light);

	auto it = std::find(mLightComponents.begin(), mLightComponents.end(), light);
	if (it != mLightComponents.end())
	{
		mD3DDevice->LightEnable(light->mIndex, false);
		mD3DDevice->SetLight(light->mIndex, nullptr);
		mLightComponents.erase(it);
	}
}

CameraComponent* RenderingEngine::GetCurrentCamera()
{
	return mCurrentCamera;
}

void RenderingEngine::preRender()
{
	if (mCurrentCamera)
	{
		updateCamera();
	}

	updateLights();

	// 배경 지우기 / 렌더 시작.
	if (mD3DDevice)
	{
		mD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, mBackgroundColor, 1.f, 0);
		mD3DDevice->BeginScene();
	}
}

void RenderingEngine::render()
{
	if (mD3DDevice)
	{
		// 불투명 렌더링.
		mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		renderMeshes(mMeshComponents[eRenderingMode::Opaque]);

		// 투명 렌더링.
		mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		renderMeshes(mMeshComponents[eRenderingMode::Transparency]);
	}
}

void RenderingEngine::postRender()
{
	// 렌더 마무리 / 백 버퍼 스왑.
	if (mD3DDevice)
	{
		mD3DDevice->EndScene();
		mD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void RenderingEngine::updateCamera()
{
	mD3DDevice->SetTransform(D3DTS_VIEW, &mCurrentCamera->getViewMatrix());
	mD3DDevice->SetTransform(D3DTS_PROJECTION, &mCurrentCamera->getProjectionMatrix(mWidth, mHeight));
}

void RenderingEngine::updateLights()
{
	for (auto light : mLightComponents)
	{
		if (!light->IsActiveAndEnabled())
		{
			continue;
		}

		light->updatePositionAndDirection();
	}
}

// 카메라와의 거리에 따라 정렬.
void RenderingEngine::sortTransparencyMeshes()
{
	auto camPos = mCurrentCamera->GetTransform()->GetPosition();
	auto& meshComponents = mMeshComponents[eRenderingMode::Transparency];
	std::sort(meshComponents.begin(), meshComponents.end(),
		[&](MeshComponent* a, MeshComponent* b)
		{
			auto gapA = camPos - a->GetTransform()->GetPosition();
			auto gapB = camPos - b->GetTransform()->GetPosition();
			return gapA.GetSizeSq() > gapB.GetSizeSq();
		});
}

void RenderingEngine::renderMeshes(std::vector<MeshComponent*>& meshComponents)
{
	for (auto meshComponent : meshComponents)
	{
		if (!meshComponent->IsActiveAndEnabled())
		{
			continue;
		}

		meshComponent->render(mD3DDevice);
	}
}

bool RenderingEngine::init(const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	mWidth = width;
	mHeight = height;

	if (!initDevice(hWnd, bWindowed))
	{
		return false;
	}

	mMeshComponents.insert({ eRenderingMode::Opaque, std::vector<MeshComponent*>() });
	mMeshComponents.insert({ eRenderingMode::Transparency, std::vector<MeshComponent*>() });

	mbInit = true;
	return true;
}

bool RenderingEngine::initDevice(const HWND hWnd, const bool bWindowed)
{
	IDirect3D9* d3d9;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		::MessageBox(nullptr, _T("RenderingEngine/Init/Direct3DCreate9 : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// 하드웨어 버텍스 프로세싱을 확인한다.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	long vp = caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ?
		D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp{};
	d3dpp.BackBufferWidth = mWidth;
	d3dpp.BackBufferHeight = mHeight;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // 32비트 픽셀 포맷
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = bWindowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &mD3DDevice);
	if (FAILED(hr))
	{
		// 16 비트 깊이 버퍼로 다시 시도한다.
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &mD3DDevice);
		if (FAILED(hr))
		{
			::MessageBox(nullptr, _T("RenderingEngine/Init/CreateDevice : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
	}

	d3d9->Release();

	return true;
}

void RenderingEngine::clear()
{
	mCurrentCamera = nullptr;
	mMeshComponents.clear();
	mLightComponents.clear();
	for (DWORD i = 0; i < mCurrentLightCount; i++)
	{
		mD3DDevice->LightEnable(mCurrentLightCount, false);
		mD3DDevice->SetLight(mCurrentLightCount, nullptr);
	}
	mCurrentLightCount = 0;
}

void RenderingEngine::release()
{
	if (!mbInit)
	{
		return;
	}

	if (mD3DDevice)
	{
		mD3DDevice->Release();
		mD3DDevice = nullptr;
		mbInit = false;
	}
}
