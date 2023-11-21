#include "DirectionalLightComponent.h"

DirectionalLightComponent::DirectionalLightComponent(int controlkey)
	: LightComponent(controlkey) {}

void DirectionalLightComponent::update(const float& deltaTime) {
	// Update the light's direction
	// based on its GameObject's forward vector
	if (owningGameObject) {
		glm::vec3 worldForward = owningGameObject->getFowardDirection();
		glm::vec4 lightDirection = glm::normalize(glm::vec4(-worldForward, 0.0f));
		setPositionOrDirection(lightDirection);
	}
}