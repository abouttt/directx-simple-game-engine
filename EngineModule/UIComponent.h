#pragma once

#include "BehaviourComponent.h"

class UIComponent : public BehaviourComponent
{
public:
	UIComponent();
	virtual ~UIComponent();

public:
	virtual void Draw(IDirect3DDevice9* const device) abstract;
};

