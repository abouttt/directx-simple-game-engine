#include "pch.h"
#include "BehaviourComponent.h"
#include "GameBehaviourComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

GameObject::GameObject()
	: mState(eState::Active)
	, mName(_T("GameObject"))
	, mTag(_T("Untagged"))
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

GameObject::GameObject(const std::wstring& name)
	: mState(eState::Active)
	, mName(name)
	, mTag(_T("Untagged"))
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

GameObject::GameObject(const std::wstring& name, const std::wstring& tag)
	: mState(eState::Active)
	, mName(name)
	, mTag(tag)
	, mComponents()
	, mTransform(AddComponent<TransformComponent>())
{
}

GameObject::~GameObject()
{
	for (auto& gb : GetComponents<GameBehaviourComponent>())
	{
		gb->OnDestroy();
	}

	auto scene = SceneManager::GetActiveScene();
	for (size_t i = 0; i < mTransform->GetChildCount(); i++)
	{
		auto gameObject = mTransform->GetChild(i)->GetGameObject();
		scene->RemoveGameObject(gameObject);
	}
}

bool GameObject::IsActive() const
{
	return (mState == eState::Active);
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

	mState = bActive ? eState::Active : eState::Inactive;

	for (auto behaviour : GetComponents<BehaviourComponent>())
	{
		if (!behaviour->IsEnabled())
		{
			continue;
		}

		if (bActive)
		{
			behaviour->OnEnable();
		}
		else
		{
			behaviour->OnDisable();
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
	if (component->mbDestroyed)
	{
		return;
	}

	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if (it->get() == component)
		{
			if (auto behaviour = dynamic_cast<BehaviourComponent*>(component))
			{
				behaviour->SetEnabled(false);
			}

			(*it)->mbDestroyed = true;
			break;
		}
	}
}

void GameObject::cleanup()
{
	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if ((*it)->mbDestroyed)
		{
			if (auto gb = dynamic_cast<GameBehaviourComponent*>(it->get()))
			{
				gb->OnDestroy();
			}

			mComponents.erase(it--);
		}
	}
}
