#pragma once

#include "Object.h"

class GameObject;
class TransformComponent;

class Component : public Object
{
public:
	friend class GameObject;

public:
	Component();
	virtual ~Component() = default;

public:
	const std::wstring& GetName() const override;
	const std::wstring& GetTag() const;
	GameObject* GetGameObject();
	TransformComponent* GetTransform();

	void SetName(const std::wstring& name) override;

private:
	GameObject* mGameObject;
};

