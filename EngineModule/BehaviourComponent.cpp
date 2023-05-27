#include "pch.h"
#include "BehaviourComponent.h"

BehaviourComponent::BehaviourComponent()
    : mbEnabled(true)
{
}

bool BehaviourComponent::IsActiveAndEnabled() const
{
    return IsActive() && mbEnabled;
}

bool BehaviourComponent::IsEnabled() const
{
    return mbEnabled;
}

void BehaviourComponent::SetEnabled(const bool bEnabled)
{
    mbEnabled = bEnabled;
}
