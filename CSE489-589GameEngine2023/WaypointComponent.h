#pragma once

#include "Component.h"

class WaypointComponent : public Component
{
public:

	/**
	 * @fn	WaypointComponent::WaypointComponent(std::vector< glm::vec3> waypoints, vec3 velocity = vec3(10, 0, 0));
	 *
	 * @brief	Constructor
	 *
	 * @param	waypoints	The waypoints.
	 * @param	velocity 	(Optional) The velocity.
	 */
	WaypointComponent(std::vector<std::shared_ptr<class GameObject>> waypoints, vec3 velocity = vec3(10, 0, 0));

	virtual void update(const float& deltaTime) override;

protected:

	int getNexWaypointIndex();
	vec3 getDirectionToNextWaypoint();
	GLfloat distanceToTargetWaypoint();

	std::vector<std::shared_ptr<class GameObject>> waypoints;

	vec3 velocity;
	float speed;

	int targetWaypointIndex = 0;


};

