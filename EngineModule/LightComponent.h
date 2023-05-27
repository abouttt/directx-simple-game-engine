#pragma once

#include "BehaviourComponent.h"

class LightComponent : public BehaviourComponent
{
public:
	friend class RenderingEngine;

public:
	LightComponent(const D3DLIGHTTYPE lightType);

public:
	void SetLightType(const D3DLIGHTTYPE lightType);
	void SetColor(const D3DXCOLOR& color);
	void SetRange(const float range);
	void SetEnable(const bool bEnable) override;

private:
	void initDirectionLight();
	void initPointLight();
	void initSpotLight();
	void updatePositionAndDirection();

private:
	D3DLIGHT9 mD3DLight;
	DWORD mIndex;
};

