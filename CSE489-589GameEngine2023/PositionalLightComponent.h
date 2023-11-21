#pragma once
#include "LightComponent.h"

class PositionalLightComponent : public LightComponent
{
public:
	PositionalLightComponent(int controlkey);
	virtual void update(const float& deltaTime) override;
};

