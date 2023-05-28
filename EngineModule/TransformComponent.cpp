#include "pch.h"
#include "TransformComponent.h"

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

D3DXVECTOR3 TransformComponent::GetLocalPosition() const
{
	return mLocalTransform.GetPosition();
}

D3DXQUATERNION TransformComponent::GetLocalRotation() const
{
	return mLocalTransform.GetRotation();
}

D3DXVECTOR3 TransformComponent::GetLocalEulerAngles() const
{
	return mLocalTransform.GetEulerAngles();
}

D3DXVECTOR3 TransformComponent::GetLocalScale() const
{
	return mLocalTransform.GetScale();
}

D3DXVECTOR3 TransformComponent::GetLocalAxisX() const
{
	return mLocalTransform.GetAxisX();
}

D3DXVECTOR3 TransformComponent::GetLocalAxisY() const
{
	return mLocalTransform.GetAxisY();
}

D3DXVECTOR3 TransformComponent::GetLocalAxisZ() const
{
	return mLocalTransform.GetAxisZ();
}

D3DXMATRIX TransformComponent::GetLocalMatrix() const
{
	return mLocalTransform.GetMatrix();
}

void TransformComponent::SetLocalPosition(const D3DXVECTOR3& position)
{
	mLocalTransform.SetPosition(position);
	updateWorld();
}

void TransformComponent::SetLocalRotation(const D3DXQUATERNION& rotation)
{
	mLocalTransform.SetRotation(rotation);
	updateWorld();
}

void TransformComponent::SetLocalRotation(const D3DXVECTOR3& eulerAngles)
{
	mLocalTransform.SetRotation(eulerAngles);
	updateWorld();
}

void TransformComponent::SetLocalScale(const D3DXVECTOR3& scale)
{
	mLocalTransform.SetScale(scale);
	updateWorld();
}

void TransformComponent::AddLocalPosition(const D3DXVECTOR3& position)
{
	mLocalTransform.AddPosition(position);
	updateWorld();
}

void TransformComponent::AddLocalRotation(const D3DXVECTOR3& eulerAngles)
{
	mLocalTransform.AddRotation(eulerAngles);
	updateWorld();
}

void TransformComponent::AddLocalScale(const D3DXVECTOR3& scale)
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

void TransformComponent::Translate(const D3DXVECTOR3& translation)
{
	mLocalTransform.Translate(translation);
	updateWorld();
}

D3DXVECTOR3 TransformComponent::GetPosition() const
{
	return mWorldTransform.GetPosition();
}

D3DXQUATERNION TransformComponent::GetRotation() const
{
	return mWorldTransform.GetRotation();
}

D3DXVECTOR3 TransformComponent::GetEulerAngles() const
{
	return mWorldTransform.GetEulerAngles();
}

D3DXVECTOR3 TransformComponent::GetScale() const
{
	return mWorldTransform.GetScale();
}

D3DXVECTOR3 TransformComponent::GetAxisX() const
{
	return mWorldTransform.GetAxisX();
}

D3DXVECTOR3 TransformComponent::GetAxisY() const
{
	return mWorldTransform.GetAxisY();
}

D3DXVECTOR3 TransformComponent::GetAxisZ() const
{
	return mWorldTransform.GetAxisZ();
}

D3DXMATRIX TransformComponent::GetMatrix() const
{
	return mWorldTransform.GetMatrix();
}

void TransformComponent::SetPosition(const D3DXVECTOR3& position)
{
	mWorldTransform.SetPosition(position);
	updateLocal();
}

void TransformComponent::SetRotation(const D3DXQUATERNION& rotation)
{
	mWorldTransform.SetRotation(rotation);
	updateLocal();
}

void TransformComponent::SetRotation(const D3DXVECTOR3& eulerAngles)
{
	mWorldTransform.SetRotation(eulerAngles);
	updateLocal();
}

void TransformComponent::SetScale(const D3DXVECTOR3& scale)
{
	mWorldTransform.SetScale(scale);
	updateLocal();
}

void TransformComponent::AddPosition(const D3DXVECTOR3& position)
{
	mWorldTransform.AddPosition(position);
	updateLocal();
}

void TransformComponent::AddRotation(const D3DXVECTOR3& eulerAngles)
{
	mWorldTransform.AddRotation(eulerAngles);
	updateLocal();
}

void TransformComponent::AddScale(const D3DXVECTOR3& scale)
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
