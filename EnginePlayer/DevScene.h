#pragma once

#include "Scene.h"

class DevScene : public Scene
{
public:
	DevScene();
	~DevScene();

protected:
	void init() override;
};

