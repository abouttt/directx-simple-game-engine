#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component()
    : mGameObject(nullptr)
{
}

bool Component::IsActive() const
{
    return mGameObject->IsActive();
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

void Component::SetActive(bool mbActive)
{
    mGameObject->SetActive(mbActive);
}

void Component::SetName(const std::wstring& name)
{
    mGameObject->SetName(name);
}
