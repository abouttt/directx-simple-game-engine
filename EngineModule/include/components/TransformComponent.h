#pragma once

#include "Component.h"
#include "Transform.h"

class TransformComponent : public Component
{
public:
	TransformComponent();
	TransformComponent(const Transform& localTransform);

public: // 로컬 트랜스폼.
	D3DXVECTOR3 GetLocalPosition() const;
	D3DXQUATERNION GetLocalRotation() const;
	D3DXVECTOR3 GetLocalEulerAngles() const;
	D3DXVECTOR3 GetLocalScale() const;
	D3DXVECTOR3 GetLocalAxisX() const;
	D3DXVECTOR3 GetLocalAxisY() const;
	D3DXVECTOR3 GetLocalAxisZ() const;
	D3DXMATRIX GetLocalMatrix() const;

	void SetLocalPosition(const D3DXVECTOR3& position);
	void SetLocalRotation(const D3DXQUATERNION& rotation);
	void SetLocalRotation(const D3DXVECTOR3& eulerAngles);
	void SetLocalScale(const D3DXVECTOR3& scale);

	void AddLocalPosition(const D3DXVECTOR3& position);
	void AddLocalRotation(const D3DXVECTOR3& eulerAngles);
	void AddLocalScale(const D3DXVECTOR3& scale);
	void AddLocalRotationX(const float degree);
	void AddLocalRotationY(const float degree);
	void AddLocalRotationZ(const float degree);

	void Translate(const D3DXVECTOR3& translation);

public: // 월드 트랜스폼.
	D3DXVECTOR3 GetPosition() const;
	D3DXQUATERNION GetRotation() const;
	D3DXVECTOR3 GetEulerAngles() const;
	D3DXVECTOR3 GetScale() const;
	D3DXVECTOR3 GetAxisX() const;
	D3DXVECTOR3 GetAxisY() const;
	D3DXVECTOR3 GetAxisZ() const;
	D3DXMATRIX GetMatrix() const;

	void SetPosition(const D3DXVECTOR3& position);
	void SetRotation(const D3DXQUATERNION& rotation);
	void SetRotation(const D3DXVECTOR3& eulerAngles);
	void SetScale(const D3DXVECTOR3& scale);

	void AddPosition(const D3DXVECTOR3& position);
	void AddRotation(const D3DXVECTOR3& eulerAngles);
	void AddScale(const D3DXVECTOR3& scale);
	void AddRotationX(const float degree);
	void AddRotationY(const float degree);
	void AddRotationZ(const float degree);

public: // 계층 관련.
	TransformComponent* FindChild(const std::wstring& name);
	TransformComponent* GetChild(std::size_t index);
	bool IsChildOf(const TransformComponent* const child);
	std::size_t GetChildCount();

	TransformComponent* GetRoot();

	bool HasParent();
	TransformComponent* GetParent();
	void SetParent(TransformComponent* const parent);

private:
	void removeFromParent();
	void updateLocal();
	void updateWorld();
	void updateChildrenWorld();

private:
	Transform mLocalTransform;
	Transform mWorldTransform;

	TransformComponent* mParent;
	std::vector<TransformComponent*> mChildren;
};

