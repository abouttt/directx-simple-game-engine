#pragma once

#include "Component.h"

class BehaviourComponent : public Component
{
public:
	BehaviourComponent();
	virtual ~BehaviourComponent() = default;

public:
	bool IsActiveAndEnabled() const;
	bool IsEnabled() const;
	virtual void SetEnabled(const bool bEnabled);

private:
	bool mbEnabled;
};

