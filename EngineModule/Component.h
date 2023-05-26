#pragma once

class GameObject;
class TransformComponent;

class Component
{
public:
	friend class GameObject;

public:
	Component();
	virtual ~Component();

public:
	const tstring& GetName() const;
	const tstring& GetTag() const;
	GameObject* GetGameObject();
	TransformComponent* GetTransform();
	void SetName(const tstring& name);

private:
	GameObject* mGameObjectPtr;
};

