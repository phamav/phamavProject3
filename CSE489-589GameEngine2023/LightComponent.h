#pragma once
#include "Component.h"
#include "SharedLighting.h"

class LightComponent : public Component
{
public:
	LightComponent(int controlkey);
	virtual ~LightComponent();

	virtual void processInput() override;
	virtual void update(const float & deltaTime) override;

	// Other methods for setting light properties...
	void setAmbientColor(glm::vec4 color);
	glm::vec4 getAmbientColor();
	void setDiffuseColor(glm::vec4 color);
	glm::vec4 getDiffuseColor();
	void setSpecularColor(glm::vec4 color);
	glm::vec4 getSpecularColor();
	void setEnabled(bool enabled);

	// Position or direction
	void setPositionOrDirection(glm::vec4 coords);
	glm::vec4 getPositionOrDirection();

	// Attenuations
	void setAttenuationFactors(glm::vec3 factors);
	void setConstantAttenuation(float factor);
	float getConstantAttenuation();
	void setLinearAttenuation(float factor);
	float getLinearAttenuation();
	void setQuadraticAttenuation(float factor);
	float getQuadraticAttenuation();

protected:
	int lightIndex = 0;
	int controlKey;
	bool keyPressed = false;
};