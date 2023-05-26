#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component()
    : mGameObject(nullptr)
{
}

const std::wstring& Component::GetTag() const
{
    return mGameObject->GetTag();
}

GameObject* Component::GetGameObject()
{
    return mGameObject;
}

TransformComponent* Component::GetTransform()
{
    return mGameObject->GetTransform();
}

const std::wstring& Component::GetName() const
{
    return mGameObject->GetName();
}

void Component::SetName(const std::wstring& name)
{
    mGameObject->SetName(name);
}
