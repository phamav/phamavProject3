#pragma once
#include "Component.h"
class SpinComponent : public Component
{
private:
    glm::vec3 axis;
    float rotationRateRadians;

public:
    SpinComponent(vec3 axis, float rotRateDegrees);

    virtual void update(const float& deltaTime) override;
};

