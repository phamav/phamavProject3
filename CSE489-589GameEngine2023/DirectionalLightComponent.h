#pragma once
#include "LightComponent.h"

class DirectionalLightComponent : public LightComponent
{
public:
	DirectionalLightComponent(int controlkey);
	virtual void update(const float& deltaTime) override;
};