#pragma once

#include "BehaviourComponent.h"

class CameraComponent : public BehaviourComponent
{
public:
	friend class Renderer;

public:
	CameraComponent();

public:
	static CameraComponent* GetMainCamera();
	static CameraComponent* GetCurrentCamera();

public:
	int GetFieldOfView() const;
	float GetNear() const;
	float GetFar() const;

	void SetNear(const float value);
	void SetFar(const float value);
	void SetFieldOfView(const int value);

protected:
	void OnEnable() override;
	void OnDisable() override;

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

