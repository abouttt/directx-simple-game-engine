#include "pch.h"
#include "BehaviourComponent.h"
#include "GameBehaviourComponent.h"
#include "GameBehaviourEventManager.h"
#include "GameObject.h"

GameObject::GameObject()
	: mState(eState::Init)
	, mName(_T("GameObject"))
	, mTag(_T("Untagged"))
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

GameObject::GameObject(const std::wstring& name)
	: mState(eState::Init)
	, mName(name)
	, mTag(_T("Untagged"))
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

GameObject::GameObject(const std::wstring& name, const std::wstring& tag)
	: mState(eState::Init)
	, mName(name)
	, mTag(tag)
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

bool GameObject::IsActive() const
{
	return (mState == eState::Init) || (mState == eState::Active);
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
	// 현재 상태와 매개변수 상태가 같다면 진행하지 않는다.
	if (IsActive() == bActive)
	{
		return;
	}

	mState = bActive == true ? eState::Active : eState::Inactive;

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
	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if (it->get() == component)
		{
			if (auto behaviour = dynamic_cast<BehaviourComponent*>(component))
			{
				behaviour->SetEnable(false);
			}

			(*it)->mbDestroyed = true;

			break;
		}
	}
}

void GameObject::cleanup()
{
	auto it = mComponents.rbegin();
	while (it != mComponents.rend())
	{
		if ((*it)->mbDestroyed)
		{
			std::unique_ptr<Component> destroyedComponent(it->release());
			it = decltype(it)(mComponents.erase(std::next(it).base()));
		}
		else
		{
			++it;
		}
	}
}
