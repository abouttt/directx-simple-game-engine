#pragma once

#include "Component.h"

class BehaviourComponent : public Component
{
public:
	friend class GameObject;

public:
	BehaviourComponent();
	virtual ~BehaviourComponent() = default;

public:
	bool IsActiveAndEnabled() const;
	bool IsEnabled() const;
	void SetEnabled(const bool bEnabled);

protected:
	virtual void OnEnable() abstract;
	virtual void OnDisable() abstract;

private:
	bool mbEnabled;
};

