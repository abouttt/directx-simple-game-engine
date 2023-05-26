#pragma once

#include "Component.h"
#include "Transform.h"

struct Vector;
struct Quaternion;
struct Matrix;

class TransformComponent : public Component
{
public:
	TransformComponent();
	TransformComponent(const Transform& localTransform);

public: // ���� Ʈ������.
	Vector GetLocalPosition() const;
	Quaternion GetLocalRotation() const;
	Vector GetLocalEulerAngles() const;
	Vector GetLocalScale() const;
	Vector GetLocalAxisX() const;
	Vector GetLocalAxisY() const;
	Vector GetLocalAxisZ() const;
	Matrix GetLocalMatrix() const;

	void SetLocalPosition(const Vector& position);
	void SetLocalRotation(const Quaternion& rotation);
	void SetLocalRotation(const Vector& eulerAngles);
	void SetLocalScale(const Vector& scale);

	void AddLocalPosition(const Vector& position);
	void AddLocalRotation(const Vector& eulerAngles);
	void AddLocalScale(const Vector& scale);
	void AddLocalRotationX(const float degree);
	void AddLocalRotationY(const float degree);
	void AddLocalRotationZ(const float degree);

	void Translate(const Vector& translation);

public: // ���� Ʈ������.
	Vector GetPosition() const;
	Quaternion GetRotation() const;
	Vector GetEulerAngles() const;
	Vector GetScale() const;
	Vector GetAxisX() const;
	Vector GetAxisY() const;
	Vector GetAxisZ() const;
	Matrix GetMatrix() const;

	void SetPosition(const Vector& position);
	void SetRotation(const Quaternion& rotation);
	void SetRotation(const Vector& eulerAngles);
	void SetScale(const Vector& scale);

	void AddPosition(const Vector& position);
	void AddRotation(const Vector& eulerAngles);
	void AddScale(const Vector& scale);
	void AddRotationX(const float degree);
	void AddRotationY(const float degree);
	void AddRotationZ(const float degree);

public: // ���� ����.
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

