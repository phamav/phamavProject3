#include "LightComponent.h"

LightComponent::LightComponent(int controlkey) 
	: controlKey(controlkey)
{
	componentType = LIGHT;

	for (int i = 0; i < MAX_LIGHTS; i++) {

		if (SharedLighting::lights[i].inUse == false) {
			lightIndex = i;
			SharedLighting::lights[i].inUse = true;
			break;
		}
	}
}

LightComponent::~LightComponent() {
	SharedLighting::initilizeAttributes(lightIndex);
	SharedLighting::lights[lightIndex].inUse = false;
}

void LightComponent::processInput() {
	// Toggle the light on key press
	if (glfwGetKey(glfwGetCurrentContext(), controlKey) && !keyPressed) {
		bool isEnabled = SharedLighting::getEnabled(lightIndex);
		SharedLighting::setEnabled(lightIndex, !isEnabled);
		keyPressed = true;
	}
	else if (!glfwGetKey(glfwGetCurrentContext(), controlKey)) {
		keyPressed = false;
	}
}

void LightComponent::update(const float& deltaTime) {
	// Update the light's position or direction if necessary
}

void LightComponent::setAmbientColor(glm::vec4 color) {
	SharedLighting::setAmbientColor(lightIndex, color);
}

glm::vec4 LightComponent::getAmbientColor() {
	return SharedLighting::getAmbientColor(lightIndex);
}

void LightComponent::setDiffuseColor(glm::vec4 color) {
	SharedLighting::setDiffuseColor(lightIndex, color);
}

glm::vec4 LightComponent::getDiffuseColor() {
	return SharedLighting::getDiffuseColor(lightIndex);
}

void LightComponent::setSpecularColor(glm::vec4 color) {
	SharedLighting::setSpecularColor(lightIndex, color);
}

glm::vec4 LightComponent::getSpecularColor() {
	return SharedLighting::getSpecularColor(lightIndex);
}

void LightComponent::setEnabled(bool enabled) {
	SharedLighting::setEnabled(lightIndex, enabled);
}

// Position or direction
void LightComponent::setPositionOrDirection(glm::vec4 coords) {
	SharedLighting::setPositionOrDirection(lightIndex, coords);
}

glm::vec4 LightComponent::getPositionOrDirection() {
	return SharedLighting::getPositionOrDirection(lightIndex);
}

// Attenuations
void LightComponent::setAttenuationFactors(glm::vec3 factors) {
	SharedLighting::setAttenuationFactors(lightIndex, factors);
}

void LightComponent::setConstantAttenuation(float factor) {
	SharedLighting::setConstantAttenuation(lightIndex, factor);
}

float LightComponent::getConstantAttenuation() {
	return SharedLighting::getConstantAttenuation(lightIndex);
}

void LightComponent::setLinearAttenuation(float factor) {
	SharedLighting::setLinearAttenuation(lightIndex, factor);
}

float LightComponent::getLinearAttenuation() {
	return SharedLighting::getLinearAttenuation(lightIndex);
}

void LightComponent::setQuadraticAttenuation(float factor) {
	SharedLighting::setQuadraticAttenuation(lightIndex, factor);
}

float LightComponent::getQuadraticAttenuation() {
	return SharedLighting::getQuadraticAttenuation(lightIndex);
}