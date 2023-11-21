#include "SpotLightComponent.h"

SpotLightComponent::SpotLightComponent(int controlkey) 
	: LightComponent(controlkey)
{
	setIsSpot(true);
}

void SpotLightComponent::update(const float& deltaTime) {
	if (owningGameObject) {
		glm::vec3 worldPos = owningGameObject->getPosition();
		setPositionOrDirection(vec4(worldPos, 1.0f));
		setSpotCutoffCos(glm::radians(glm::dot(getSpotDirection(), worldPos)));
	}
}

bool SpotLightComponent::getIsSpot() {
	return SharedLighting::getIsSpot(lightIndex);
}

void SpotLightComponent::setIsSpot(bool spotOn) {
	SharedLighting::setIsSpot(lightIndex, spotOn);
}

glm::vec3 SpotLightComponent::getSpotDirection() {
	return SharedLighting::getSpotDirection(lightIndex);
}

void SpotLightComponent::setSpotDirection(glm::vec3 spotDirect) {
	SharedLighting::setSpotDirection(lightIndex, spotDirect);
}

float SpotLightComponent::getSpotCutoffCos() {
	return SharedLighting::getSpotCutoffCos(lightIndex);
}

void SpotLightComponent::setSpotCutoffCos(float cutoffCos) {
	SharedLighting::setSpotCutoffCos(lightIndex, cutoffCos);
}

float SpotLightComponent::getSpotExponent() {
	return SharedLighting::getSpotExponent(lightIndex);
}

void SpotLightComponent::setSpotExponent(float spotEx) {
	SharedLighting::setSpotExponent(lightIndex, spotEx);
}