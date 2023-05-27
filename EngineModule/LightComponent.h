#pragma once

#include "BehaviourComponent.h"

enum class eLightType;

class LightComponent : public BehaviourComponent
{
public:
	LightComponent(const D3DLIGHTTYPE lightType);
	~LightComponent();

public:
	void SetLightType(const D3DLIGHTTYPE lightType);
	void SetColor(const D3DXCOLOR& color);
	void SetRange(const float range);

private:
	void initDirectionLight();
	void initPointLight();
	void initSpotLight();
	void updateTransform();

private:
	D3DLIGHT9 mD3DLight;
};

