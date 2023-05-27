#pragma once

#include "BehaviourComponent.h"

class CameraComponent : public BehaviourComponent
{
public:
	friend class RenderingEngine;

public:
	CameraComponent();
	~CameraComponent();

public:
	static CameraComponent* GetCurrentCamera();
	static CameraComponent* GetMainCamera();

public:
	int GetFieldOfView() const;
	float GetNear() const;
	float GetFar() const;

	void SetNear(const float value);
	void SetFar(const float value);
	void SetFieldOfView(const int value);
	void SetEnable(const bool bEnable) override;

private:
	const D3DXMATRIX& getViewMatrix();
	const D3DXMATRIX& getProjectionMatrix(const int width, const int height);

private:
	int mFov;
	float mNear;
	float mFar;

	D3DXMATRIX mViewMatrix;
	D3DXMATRIX mProjMatrix;
};

