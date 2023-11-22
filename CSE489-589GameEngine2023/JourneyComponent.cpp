#include "JourneyComponent.h"

#define VERBOSE false

JourneyComponent::JourneyComponent(std::vector<std::shared_ptr<class GameObject>> waypoints, vec3 velocity)
	: velocity(velocity), speed(glm::length(velocity)), waypoints(waypoints),
	targetWaypointIndex(static_cast<int>(waypoints.size()) - 1)
{
	targetWaypointIndex = getNexWaypointIndex();

}

void JourneyComponent::update(const float& deltaTime)
{
	if (waypoints.empty() || targetWaypointIndex >= waypoints.size()) return;

	float radius = 1.0;

	// Check if next waypoint has been reached
	if (distanceToTargetWaypoint() < (speed * deltaTime + radius)) {
		targetWaypointIndex = getNexWaypointIndex();
	}

	// Get current facing directions
	vec3 current = owningGameObject->getFowardDirection(WORLD);

	// Get direction to the next waypoint
	vec3 desiredDirection = getDirectionToNextWaypoint();

	// Incrementally update current direction to face the next waypoint
	vec3 newDirection = glm::lerp(current, desiredDirection, deltaTime);

	// Rotate to face the new direction
	owningGameObject->rotateTo(newDirection, WORLD);

	// Get the current position
	vec3 position = owningGameObject->getPosition(WORLD);

	// Update the position based on the newDirection
	position = position + newDirection * speed * deltaTime;

	// Set the position of the GameObject
	owningGameObject->setPosition(position, WORLD);

} // end update


void JourneyComponent::processInput()
{
	GLFWwindow* window = glfwGetCurrentContext();

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		targetWaypointIndex = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		targetWaypointIndex = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		targetWaypointIndex = 2;
	}
}


int JourneyComponent::getNexWaypointIndex()
{
	return (targetWaypointIndex + 1) % waypoints.size();

} // end getNexWaypointIndex

vec3 JourneyComponent::getDirectionToNextWaypoint()
{
	return glm::normalize((waypoints[targetWaypointIndex]->getPosition(WORLD) - owningGameObject->getPosition(WORLD)));

} // end getDirectionToNextWaypoint

GLfloat JourneyComponent::distanceToTargetWaypoint()
{
	GLfloat dist = glm::distance(waypoints[targetWaypointIndex]->getPosition(WORLD), owningGameObject->getPosition(WORLD));

	if (VERBOSE) cout << dist << endl;

	return dist;

} // end distanceToTargetWaypoint