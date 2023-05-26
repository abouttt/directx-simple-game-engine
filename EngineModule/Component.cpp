#include "pch.h"
#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
}

const tstring& Component::GetName() const
{
    return nullptr;
}

const tstring& Component::GetTag() const
{
    return nullptr;
}

GameObject* Component::GetGameObject()
{
    return nullptr;
}

TransformComponent* Component::GetTransform()
{
    return nullptr;
}

void Component::SetName(const tstring& name)
{
}
