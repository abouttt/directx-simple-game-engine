#pragma once

#include "Scene.h"

class DevScene : public Scene
{
public:
	DevScene(const std::wstring& name);
	~DevScene();

protected:
	void init() override;
};

