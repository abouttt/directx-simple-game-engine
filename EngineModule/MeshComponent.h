#pragma once

#include "BehaviourComponent.h"

class Mesh;
class Material;

class MeshComponent : public BehaviourComponent
{
public:
	friend class RenderEngine;

public:
	MeshComponent();
	~MeshComponent();

public:
	Mesh* GetMesh();
	Material* GetMaterial();

	void SetMesh(Mesh* const mesh);
	void SetMaterial(Material* const material);

private:
	void render(IDirect3DDevice9* device);

private:
	Mesh* mMesh;
	Material* mMaterial;
};

