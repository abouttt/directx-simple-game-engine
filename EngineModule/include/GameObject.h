#pragma once

#include "TransformComponent.h"

class GameObject
{
public:
	enum class eState
	{
		Init,
		Active,
		Inactive,
		Destroyed,
	};

public:
	friend class Scene;

public:
	GameObject();
	GameObject(const std::wstring& name);
	GameObject(const std::wstring& name, const std::wstring& tag);

public:
	bool IsActive() const;
	const std::wstring& GetName() const;
	const std::wstring& GetTag() const;
	TransformComponent* GetTransform();

	void SetActive(const bool bActive);
	void SetName(const std::wstring& name);
	void SetTag(const std::wstring& tag);

public: // Component
	template<typename T, typename ...Args>
	T* AddComponent(Args&& ...args);
	template<typename T>
	T* GetComponent();
	template<typename T>
	T* GetComponentInChildren();
	template<typename T>
	T* GetComponentInParent();
	template<typename T>
	std::vector<T*> GetComponents();
	template<typename T>
	std::vector<T*> GetComponentsInChildren();
	template<typename T>
	std::vector<T*> GetComponentsInParent();
	void RemoveComponent(Component* const component);

private:
	void cleanup();

private:
	eState mState;
	std::wstring mName;
	std::wstring mTag;
	std::vector<std::unique_ptr<Component>> mComponents;
	TransformComponent* mTransform;
};

template<typename T, typename ...Args>
inline T* GameObject::AddComponent(Args && ...args)
{
	static_assert(std::is_base_of<Component, T>::value);

	// 트랜스폼 컴포넌트는 1개이상 생성 불가능.
	if (std::is_same<TransformComponent, T>::value)
	{
		if (mTransform)
		{
			return (T*)mTransform;
		}
	}

	auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
	newComponent->mGameObject = this;
	mComponents.emplace_back(std::move(newComponent));

	return static_cast<T*>(mComponents.back().get());
}

template<typename T>
inline T* GameObject::GetComponent()
{
	static_assert(std::is_base_of<Component, T>::value);

	for (auto& component : mComponents)
	{
		if (component->mbDestroyed)
		{
			continue;
		}

		if (auto t = dynamic_cast<T*>(component.get()))
		{
			return t;
		}
	}

	return nullptr;
}

template<typename T>
inline T* GameObject::GetComponentInChildren()
{
	static_assert(std::is_base_of<Component, T>::value);

	for (std::size_t i = 0; i < mTransform->GetChildCount(); i++)
	{
		auto child = mTransform->GetChild(i);

		if (!child->IsActive())
		{
			continue;
		}

		if (auto component = mTransform->GetChild(i)->GetGameObject().GetComponent<T>())
		{
			return component;
		}
	}

	return nullptr;
}

template<typename T>
inline T* GameObject::GetComponentInParent()
{
	static_assert(std::is_base_of<Component, T>::value);

	if (mTransform->HasParent())
	{
		return mTransform->GetParent()->GetGameObject().GetComponent<T>();
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> GameObject::GetComponents()
{
	static_assert(std::is_base_of<Component, T>::value);

	std::vector<T*> result;

	for (auto& component : mComponents)
	{
		if (component->mbDestroyed)
		{
			continue;
		}

		if (auto t = dynamic_cast<T*>(component.get()))
		{
			result.emplace_back(t);
		}
	}

	return result;
}

template<typename T>
inline std::vector<T*> GameObject::GetComponentsInChildren()
{
	static_assert(std::is_base_of<Component, T>::value);

	std::vector<T*> result;

	for (std::size_t i = 0; i < mTransform->GetChildCount(); i++)
	{
		auto components = mTransform->GetChild(i)->GetGameObject().GetComponents<T>();
		if (!components.empty())
		{
			result.insert(components.begin(), components.end());
		}
	}

	return result;
}

template<typename T>
inline std::vector<T*> GameObject::GetComponentsInParent()
{
	static_assert(std::is_base_of<Component, T>::value);

	std::vector<T*> result;

	if (mTransform->HasParent())
	{
		result = mTransform->GetParent()->GetGameObject().GetComponents<T>();
	}

	return result;
}
