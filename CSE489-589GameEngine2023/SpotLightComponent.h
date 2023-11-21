#pragma once
#include "LightComponent.h"

class SpotLightComponent : public LightComponent
{
public:
	SpotLightComponent(int controlkey);
	virtual void update(const float& deltaTime) override;

	// spotlight specific methods
	bool getIsSpot();
	void setIsSpot(bool spotOn);

	glm::vec3 getSpotDirection();
	void setSpotDirection(glm::vec3 spotDirect);

	float getSpotCutoffCos();
	void setSpotCutoffCos(float cutoffCos);

	float getSpotExponent();
	void setSpotExponent(float spotEx);
};

