#include "pch.h"
#include "UIComponent.h"
#include "Renderer.h"

UIComponent::UIComponent()
{
	Renderer::AddUIComponent(this);
}

UIComponent::~UIComponent()
{
	Renderer::RemoveUIComponent(this);
}
