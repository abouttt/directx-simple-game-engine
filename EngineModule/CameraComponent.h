#pragma once

#include "Component.h"

class CameraComponent : public Component
{
public:
	friend class RenderEngine;

public:
	CameraComponent();
	~CameraComponent();

public:
	int GetFieldOfView() const;
	float GetNear() const;
	float GetFar() const;

	void SetNear(const float value);
	void SetFar(const float value);
	void SetFieldOfView(const int value);

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

