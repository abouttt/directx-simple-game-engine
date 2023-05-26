#include "pch.h"
#include "Object.h"

Object::Object()
    :mbActive(true)
{
}

bool Object::IsActive() const
{
    return mbActive;
}

void Object::SetActive(bool bActive)
{
    mbActive = bActive;
}
