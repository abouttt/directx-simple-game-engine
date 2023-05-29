#include "pch.h"
#include "CameraComponent.h"
#include "EngineUtil.h"
#include "LightComponent.h"
#include "Material.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "UIComponent.h"

bool Renderer::mbInit = false;
int Renderer::mWidth = 0;
int Renderer::mHeight = 0;
IDirect3DDevice9* Renderer::mD3DDevice = nullptr;
D3DCOLOR Renderer::mBackgroundColor = D3DCOLOR_XRGB(128, 128, 128);
CameraComponent* Renderer::mCurrentCamera = nullptr;
std::vector<MeshComponent*> Renderer::mMeshComponents;
std::vector<LightComponent*> Renderer::mLightComponents;
std::vector<UIComponent*> Renderer::mUIComponents;
std::vector<MeshComponent*>::iterator Renderer::mAlphaRenderBegin;
DWORD Renderer::mCurrentLightCount = 0;

int Renderer::GetWidth()
{
	return mWidth;
}

int Renderer::GetHeight()
{
	return mHeight;
}

IDirect3DDevice9* Renderer::getDevice()
{
	return mD3DDevice;
}

D3DCOLOR Renderer::GetBackgroundColor()
{
	return mBackgroundColor;
}

void Renderer::SetBackgroundColor(const D3DCOLOR color)
{
	mBackgroundColor = color;
}

void Renderer::SetCurrentCamera(CameraComponent* camera)
{
	mCurrentCamera = camera;
}

void Renderer::AddMeshComponent(MeshComponent* const mesh)
{
	assert(mesh);

	if (std::find(mMeshComponents.begin(), mMeshComponents.end(), mesh) == mMeshComponents.end())
	{
		mMeshComponents.emplace_back(mesh);
	}
}

void Renderer::AddLightComponent(LightComponent* const light)
{
	assert(light);

	if (std::find(mLightComponents.begin(), mLightComponents.end(), light) == mLightComponents.end())
	{
		light->mIndex = mCurrentLightCount++;
		mLightComponents.emplace_back(light);
	}
}

void Renderer::AddUIComponent(UIComponent* const ui)
{
	assert(ui);

	if (std::find(mUIComponents.begin(), mUIComponents.end(), ui) == mUIComponents.end())
	{
		mUIComponents.emplace_back(ui);
	}
}

void Renderer::RemoveMeshComponent(MeshComponent* const mesh)
{
	assert(mesh);

	auto it = std::find(mMeshComponents.begin(), mMeshComponents.end(), mesh);
	if (it != mMeshComponents.end())
	{
		mMeshComponents.erase(it);
	}
}

void Renderer::RemoveLightComponent(LightComponent* const light)
{
	assert(light);

	auto it = std::find(mLightComponents.begin(), mLightComponents.end(), light);
	if (it != mLightComponents.end())
	{
		mD3DDevice->LightEnable(light->mIndex, false);
		mLightComponents.erase(it);
	}
}

void Renderer::RemoveUIComponent(UIComponent* const ui)
{
	assert(ui);

	auto it = std::find(mUIComponents.begin(), mUIComponents.end(), ui);
	if (it != mUIComponents.end())
	{
		mUIComponents.erase(it);
	}
}

CameraComponent* Renderer::GetCurrentCamera()
{
	return mCurrentCamera;
}

void Renderer::preRender()
{
	if (mCurrentCamera)
	{
		updateCamera();
		updateLights();
		partitionMeshes();
		sortTransparencyMeshes();
	}

	// 배경 지우기 / 렌더 시작.
	if (mD3DDevice)
	{
		mD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, mBackgroundColor, 1.f, 0);
		mD3DDevice->BeginScene();
	}
}

void Renderer::render()
{
	if (mD3DDevice)
	{
		std::vector<MeshComponent*> it;

		// 불투명 렌더링.
		mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		renderMeshes(mMeshComponents.begin(), mAlphaRenderBegin);

		// 투명 렌더링.
		mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		renderMeshes(mAlphaRenderBegin, mMeshComponents.end());
	}
}

void Renderer::drawUI()
{
	for (auto ui : mUIComponents)
	{
		if (ui->IsActiveAndEnabled())
		{
			ui->Draw(mD3DDevice);
		}
	}
}

void Renderer::postRender()
{
	// 렌더 마무리 / 백 버퍼 스왑.
	if (mD3DDevice)
	{
		mD3DDevice->EndScene();
		mD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void Renderer::updateCamera()
{
	mD3DDevice->SetTransform(D3DTS_VIEW, &mCurrentCamera->getViewMatrix());
	mD3DDevice->SetTransform(D3DTS_PROJECTION, &mCurrentCamera->getProjectionMatrix(mWidth, mHeight));
}

void Renderer::updateLights()
{
	for (auto light : mLightComponents)
	{
		bool activeAndEnabled = light->IsActiveAndEnabled();
		if (activeAndEnabled)
		{
			light->updatePositionAndDirection();
			mD3DDevice->SetLight(light->mIndex, &light->mD3DLight);
		}

		mD3DDevice->LightEnable(light->mIndex, activeAndEnabled);
	}
}

void Renderer::partitionMeshes()
{
	// 투명, 불투명 나누기.
	mAlphaRenderBegin = std::partition(mMeshComponents.begin(), mMeshComponents.end(),
		[&](MeshComponent* meshComponent)
		{
			return meshComponent->GetMaterial()->GetRenderingMode() == eRenderingMode::Opaque;
		});
}

// 카메라와의 거리에 따라 정렬.
void Renderer::sortTransparencyMeshes()
{
	auto camPos = mCurrentCamera->GetTransform()->GetPosition();
	std::sort(mAlphaRenderBegin, mMeshComponents.end(),
		[&](MeshComponent* a, MeshComponent* b)
		{
			auto gapA = camPos - a->GetTransform()->GetPosition();
			auto gapB = camPos - b->GetTransform()->GetPosition();
			return D3DXVec3LengthSq(&gapA) > D3DXVec3LengthSq(&gapB);
		});
}

void Renderer::renderMeshes(std::vector<MeshComponent*>::iterator begin, std::vector<MeshComponent*>::iterator end)
{
	for (auto& it = begin; it != end; ++it)
	{
		if ((*it)->IsActiveAndEnabled())
		{
			(*it)->render(mD3DDevice);
		}
	}
}

bool Renderer::init(const HWND hWnd, const int width, const int height, const bool bWindowed)
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
	else
	{
		initPipeline();
	}

	mbInit = true;
	return true;
}

bool Renderer::initDevice(const HWND hWnd, const bool bWindowed)
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

void Renderer::initPipeline()
{
	if (mD3DDevice)
	{
		// 기본.
		mD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		mD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		mD3DDevice->SetRenderState(D3DRS_ZENABLE, true);
		mD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

		// 라이트.
		mD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		mD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, false);	// 정반사광.	
		mD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);	// 법선 정리.

		// 텍스처.
		mD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		mD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		mD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

		mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		// 밉맵.
		mD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

		mD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		mD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

void Renderer::clear()
{
	mCurrentCamera = nullptr;
	mMeshComponents.clear();
	mLightComponents.clear();
	for (DWORD i = 0; i < mCurrentLightCount; i++)
	{
		mD3DDevice->LightEnable(mCurrentLightCount, false);
	}
	mCurrentLightCount = 0;
}

void Renderer::release()
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
