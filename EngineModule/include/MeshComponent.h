#pragma once

#include "BehaviourComponent.h"

class Mesh;
class Material;

class MeshComponent : public BehaviourComponent
{
public:
	friend class Renderer;

public:
	MeshComponent();
	MeshComponent(Mesh* const mesh);
	MeshComponent(Mesh* const mesh, Material* const material);
	~MeshComponent();

public:
	Mesh* GetMesh();
	Material* GetMaterial();

	void SetMesh(Mesh* const mesh);
	void SetMaterial(Material* const material);

private:
	void render(IDirect3DDevice9* const device);

private:
	Mesh* mMesh;
	Material* mMaterial;
};

