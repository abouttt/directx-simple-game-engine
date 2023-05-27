#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: mbActive(true)
	, mName(_T("GameObject"))
	, mTag(_T("Untagged"))
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

GameObject::GameObject(const std::wstring& name)
	: mbActive(true)
	, mName(name)
	, mTag(_T("Untagged"))
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

GameObject::GameObject(const std::wstring& name, const std::wstring& tag)
	: mbActive(true)
	, mName(name)
	, mTag(tag)
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

bool GameObject::IsActive() const
{
	return mbActive;
}

const std::wstring& GameObject::GetTag() const
{
	return mTag;
}

TransformComponent* GameObject::GetTransform()
{
	return mTransform;
}

const std::wstring& GameObject::GetName() const
{
	return mName;
}

void GameObject::SetTag(const std::wstring& tag)
{
	mTag = tag;
}

void GameObject::SetActive(const bool bActive)
{
	// 현재 상태와 매개변수 상태가 같다면 진행하지 않는다.
	if (IsActive() == bActive)
	{
		return;
	}

	for (std::size_t i = 0; i < mTransform->GetChildCount(); i++)
	{
		mTransform->GetChild(i)->GetGameObject()->SetActive(bActive);
	}
}

void GameObject::SetName(const std::wstring& name)
{
	mName = name;
}

bool GameObject::RemoveComponent(Component* const component)
{
	return false;
}
