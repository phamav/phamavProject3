#include "ArrowRotateComponent.h"
#include "SharedTransformations.h"

ArrowRotateComponent::ArrowRotateComponent(float rotRateDegreesPerSec, int updateOrder) 
	:Component(updateOrder), radianRotRate(glm::radians(rotRateDegreesPerSec))
{

}

void ArrowRotateComponent::update(const float& deltaTime) 
{
	//mat4 viewTrans = glm::inverse(owningGameObject->getWorldTransform());

	//SharedTransformations::setViewMatrix(viewTrans);

	//mat4 rot = owningGameObject->getRotation(WORLD);

	//mat4 matRotIncrement = mat4(1.0f);
	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)) {
	//	matRotIncrement = glm::rotate(radianRotRate * deltaTime, UNIT_Y_V3);
	//}
	//else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)) {
	//	matRotIncrement *= glm::rotate(-radianRotRate * deltaTime, UNIT_Y_V3);
	//}

	//rot *= matRotIncrement;

	//this->owningGameObject->setRotation(rot, WORLD);

	//vec3 pos = owningGameObject->getPosition();
	////vec3 direction = normalize(destination - pos);
	//vec3 velocity = normalize(owningGameObject->getFowardDirection());
	////velocity = glm::normalize(lerp(velocity, direction, 2.0f * deltaTime));
	//pos = pos + (velocity) * speed * deltaTime;
	////owningGameObject->rotateTo(velocity);
	//owningGameObject->setPosition(pos);
	mat4 rot = owningGameObject->getRotation();

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)) {

		rot *= glm::rotate(radianRotRate * deltaTime, UNIT_Y_V3);
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)) {

		rot *= glm::rotate(-radianRotRate * deltaTime, UNIT_Y_V3);

	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP)) {

		rot *= glm::rotate(-radianRotRate * deltaTime, UNIT_X_V3);

	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN)) {

		rot *= glm::rotate(radianRotRate * deltaTime, UNIT_X_V3);

	}

	this->owningGameObject->setRotation(rot);
}

void ArrowRotateComponent::processInput() {
	
}