#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: mName(_T("GameObject"))
	, mTag(_T("Untagged"))
	, mTransform(AddComponent<TransformComponent>())
	, mComponents()
{
}

GameObject::GameObject(const std::wstring& name)
	: mName(name)
	, mTag(_T("Untagged"))
	, mTransform(AddComponent<TransformComponent>())
	, mComponents()
{
}

GameObject::GameObject(const std::wstring& name, const std::wstring& tag)
	: mName(name)
	, mTag(tag)
	, mTransform(AddComponent<TransformComponent>())
	, mComponents()
{
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

	Object::SetActive(bActive);

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
