#pragma once

#include "BehaviourComponent.h"

class UIComponent : public BehaviourComponent
{
public:
	UIComponent();
	virtual ~UIComponent();

protected:
	void OnEnable() override;
	void OnDisable() override;

public:
	virtual void Draw(IDirect3DDevice9* const device) abstract;
};

