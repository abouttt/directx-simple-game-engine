#include "pch.h"
#include "BehaviourComponent.h"
#include "GameBehaviourComponent.h"
#include "GameBehaviourEventManager.h"
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

const std::wstring& GameObject::GetName() const
{
	return mName;
}

const std::wstring& GameObject::GetTag() const
{
	return mTag;
}

TransformComponent* GameObject::GetTransform()
{
	return mTransform;
}

void GameObject::SetActive(const bool bActive)
{
	if (IsActive() == bActive)
	{
		return;
	}

	mbActive = bActive;

	for (auto gb : GetComponents<GameBehaviourComponent>())
	{
		if (bActive)
		{
			GameBehaviourEventManager::AddOnEnable(gb);
		}
		else
		{
			GameBehaviourEventManager::AddOnDisable(gb);
		}
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

void GameObject::SetTag(const std::wstring& tag)
{
	mTag = tag;
}

void GameObject::RemoveComponent(Component* const component)
{
	if (!component)
	{
		return;
	}

	auto it = std::find_if(mComponents.begin(), mComponents.end(),
		[component](auto& original)
		{
			return original.get() == component;
		});

	if (it != mComponents.end())
	{
		mComponents.erase(it);
	}
}
