#include "pch.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "TransformComponent.h"
#include "Vector.h"

TransformComponent::TransformComponent()
	: mLocalTransform()
	, mWorldTransform()
	, mParent(nullptr)
	, mChildren()
{
}

TransformComponent::TransformComponent(const Transform& localTransform)
	: mLocalTransform(localTransform)
{
	updateWorld();
}

Vector TransformComponent::GetLocalPosition() const
{
	return mLocalTransform.GetPosition();
}

Quaternion TransformComponent::GetLocalRotation() const
{
	return mLocalTransform.GetRotation();
}

Vector TransformComponent::GetLocalEulerAngles() const
{
	return mLocalTransform.GetEulerAngles();
}

Vector TransformComponent::GetLocalScale() const
{
	return mLocalTransform.GetScale();
}

Vector TransformComponent::GetLocalAxisX() const
{
	return mLocalTransform.GetAxisX();
}

Vector TransformComponent::GetLocalAxisY() const
{
	return mLocalTransform.GetAxisY();
}

Vector TransformComponent::GetLocalAxisZ() const
{
	return mLocalTransform.GetAxisZ();
}

Matrix TransformComponent::GetLocalMatrix() const
{
	return mLocalTransform.GetMatrix();
}

void TransformComponent::SetLocalPosition(const Vector& position)
{
	mLocalTransform.SetPosition(position);
	updateWorld();
}

void TransformComponent::SetLocalRotation(const Quaternion& rotation)
{
	mLocalTransform.SetRotation(rotation);
	updateWorld();
}

void TransformComponent::SetLocalRotation(const Vector& eulerAngles)
{
	mLocalTransform.SetRotation(eulerAngles);
	updateWorld();
}

void TransformComponent::SetLocalScale(const Vector& scale)
{
	mLocalTransform.SetScale(scale);
	updateWorld();
}

void TransformComponent::AddLocalPosition(const Vector& position)
{
	mLocalTransform.AddPosition(position);
	updateWorld();
}

void TransformComponent::AddLocalRotation(const Vector& eulerAngles)
{
	mLocalTransform.AddRotation(eulerAngles);
	updateWorld();
}

void TransformComponent::AddLocalScale(const Vector& scale)
{
	mLocalTransform.AddScale(scale);
	updateWorld();
}

void TransformComponent::AddLocalRotationX(const float degree)
{
	mLocalTransform.AddRotationX(degree);
	updateWorld();
}

void TransformComponent::AddLocalRotationY(const float degree)
{
	mLocalTransform.AddRotationY(degree);
	updateWorld();
}

void TransformComponent::AddLocalRotationZ(const float degree)
{
	mLocalTransform.AddRotationZ(degree);
	updateWorld();
}

void TransformComponent::Translate(const Vector& translation)
{
	mLocalTransform.Translate(translation);
	updateWorld();
}

Vector TransformComponent::GetPosition() const
{
	return mWorldTransform.GetPosition();
}

Quaternion TransformComponent::GetRotation() const
{
	return mWorldTransform.GetRotation();
}

Vector TransformComponent::GetEulerAngles() const
{
	return mWorldTransform.GetEulerAngles();
}

Vector TransformComponent::GetScale() const
{
	return mWorldTransform.GetScale();
}

Vector TransformComponent::GetAxisX() const
{
	return mWorldTransform.GetAxisX();
}

Vector TransformComponent::GetAxisY() const
{
	return mWorldTransform.GetAxisY();
}

Vector TransformComponent::GetAxisZ() const
{
	return mWorldTransform.GetAxisZ();
}

Matrix TransformComponent::GetMatrix() const
{
	return mWorldTransform.GetMatrix();
}

void TransformComponent::SetPosition(const Vector& position)
{
	mWorldTransform.SetPosition(position);
	updateLocal();
}

void TransformComponent::SetRotation(const Quaternion& rotation)
{
	mWorldTransform.SetRotation(rotation);
	updateLocal();
}

void TransformComponent::SetRotation(const Vector& eulerAngles)
{
	mWorldTransform.SetRotation(eulerAngles);
	updateLocal();
}

void TransformComponent::SetScale(const Vector& scale)
{
	mWorldTransform.SetScale(scale);
	updateLocal();
}

void TransformComponent::AddPosition(const Vector& position)
{
	mWorldTransform.AddPosition(position);
	updateLocal();
}

void TransformComponent::AddRotation(const Vector& eulerAngles)
{
	mWorldTransform.AddRotation(eulerAngles);
	updateLocal();
}

void TransformComponent::AddScale(const Vector& scale)
{
	mWorldTransform.AddScale(scale);
	updateLocal();
}

void TransformComponent::AddRotationX(const float degree)
{
	mWorldTransform.AddRotationX(degree);
	updateLocal();
}

void TransformComponent::AddRotationY(const float degree)
{
	mWorldTransform.AddRotationY(degree);
	updateLocal();
}

void TransformComponent::AddRotationZ(const float degree)
{
	mWorldTransform.AddRotationZ(degree);
	updateLocal();
}

TransformComponent* TransformComponent::FindChild(const std::wstring& name)
{
	for (auto child : mChildren)
	{
		if (child->GetName() == name)
		{
			return child;
		}
	}

	return nullptr;
}

TransformComponent* TransformComponent::GetChild(std::size_t index)
{
	if (mChildren.empty())
	{
		return nullptr;
	}

	if (index < 0 || index >= mChildren.size())
	{
		return nullptr;
	}

	return mChildren[index];
}

bool TransformComponent::IsChildOf(const TransformComponent* const child)
{
	return std::find(mChildren.begin(), mChildren.end(), child) != mChildren.end() ? true : false;
}

std::size_t TransformComponent::GetChildCount()
{
	return mChildren.size();
}

TransformComponent* TransformComponent::GetRoot()
{
	TransformComponent* parent = nullptr;
	TransformComponent* current = this;
	while ((parent = current->GetParent()) != nullptr)
	{
		current = parent;
	}

	return current;
}

bool TransformComponent::HasParent()
{
	return mParent != nullptr;
}

TransformComponent* TransformComponent::GetParent()
{
	return mParent;
}

void TransformComponent::SetParent(TransformComponent* const parent)
{
	if (parent)
	{
		// 이미 있는 경우에는 넘어간다.
		auto it = std::find(parent->mChildren.begin(), parent->mChildren.end(), this);
		if (it != parent->mChildren.end())
		{
			return;
		}

		// 새로운 트랜스폼 노드로 부모 재설정
		removeFromParent();
		parent->mChildren.emplace_back(this);
		mParent = parent;

		// 새로운 부모에 맞춰 자신의 로컬 정보를 업데이트한다.
		updateLocal();
	}
	else
	{
		removeFromParent();
	}
}

void TransformComponent::removeFromParent()
{
	if (!HasParent())
	{
		return;
	}

	auto it = std::find(mParent->mChildren.begin(), mParent->mChildren.end(), this);
	if (it == mParent->mChildren.end())
	{
		return;
	}

	mParent->mChildren.erase(it);
	mParent = nullptr;
	updateLocal();
}

void TransformComponent::updateLocal()
{
	if (HasParent())
	{
		mLocalTransform = mWorldTransform.WorldToLocal(mParent->mWorldTransform);
	}
	else
	{
		mLocalTransform = mWorldTransform;
	}
}

void TransformComponent::updateWorld()
{
	if (HasParent())
	{
		mWorldTransform = mLocalTransform.LocalToWorld(mParent->mWorldTransform);
	}
	else
	{
		mWorldTransform = mLocalTransform;
	}

	updateChildrenWorld();
}

void TransformComponent::updateChildrenWorld()
{
	for (auto child : mChildren)
	{
		child->updateWorld();
	}
}
