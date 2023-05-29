#pragma once

class GameObject;
class TransformComponent;

class Component
{
public:
	friend class GameObject;

public:
	Component();
	virtual ~Component() = default;

public:
	bool IsActive() const;

	GameObject* GetGameObject();
	TransformComponent* GetTransform();
	const std::wstring& GetTag() const;
	const std::wstring& GetName() const;

	void SetActive(bool mbActive);
	void SetName(const std::wstring& name);

private:
	bool mbDestroyed;
	GameObject* mGameObject;
};

