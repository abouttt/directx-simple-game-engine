#include "pch.h"
#include "EngineUtil.h"
#include "LightComponent.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include "Renderer.h"
#include "TransformComponent.h"

LightComponent::LightComponent(const D3DLIGHTTYPE lightType)
	: mD3DLight()
{
	SetLightType(lightType);
	SetColor(COLOR_WHITE);
	Renderer::AddLightComponent(this);
}

LightComponent::~LightComponent()
{
	Renderer::RemoveLightComponent(this);
}

void LightComponent::SetLightType(const D3DLIGHTTYPE lightType)
{
	::ZeroMemory(&mD3DLight, sizeof(D3DLIGHT9));
	switch (lightType)
	{
	case D3DLIGHT_DIRECTIONAL:
		initDirectionLight();
		break;
	case D3DLIGHT_POINT:
		initPointLight();
		break;
	case D3DLIGHT_SPOT:
		initSpotLight();
		break;
	}
}

void LightComponent::SetColor(const D3DXCOLOR& color)
{
	mD3DLight.Ambient = color * 0.6f;
	mD3DLight.Diffuse = color;
	mD3DLight.Specular = color * 0.6f;
}

void LightComponent::SetRange(const float range)
{
	mD3DLight.Range = range;
}

void LightComponent::initDirectionLight()
{
	mD3DLight.Type = D3DLIGHT_DIRECTIONAL;
}

void LightComponent::initPointLight()
{
	mD3DLight.Type = D3DLIGHT_POINT;
	mD3DLight.Range = 1000.0f;
	mD3DLight.Falloff = 1.0f;
	mD3DLight.Attenuation0 = 1.0f;
	mD3DLight.Attenuation1 = 0.0f;
	mD3DLight.Attenuation2 = 0.0f;
}

void LightComponent::initSpotLight()
{
	mD3DLight.Type = D3DLIGHT_SPOT;
	mD3DLight.Range = 1000.0f;
	mD3DLight.Falloff = 1.0f;
	mD3DLight.Attenuation0 = 1.0f;
	mD3DLight.Attenuation1 = 0.0f;
	mD3DLight.Attenuation2 = 0.0f;
	mD3DLight.Theta = 0.5f;
	mD3DLight.Phi = 0.7f;
}

void LightComponent::updatePositionAndDirection()
{
	mD3DLight.Position = GetTransform()->GetPosition();
	D3DXQUATERNION rotation = GetTransform()->GetRotation();
	D3DXVECTOR3 axis;
	float angle;
	D3DXQuaternionToAxisAngle(&rotation, &axis, &angle);
	D3DXVec3Normalize(static_cast<D3DXVECTOR3*>(&mD3DLight.Direction), &axis);
}