#include "CameraComponent.h"
#include "SharedTransformations.h"

#define VERBOSE false

std::vector<std::shared_ptr<CameraComponent>> CameraComponent::activeCameras;

CameraComponent::CameraComponent(
	const int& cameraDepth, const float& vertFovDegrees,
	const float& nearClip, const float& farClip) 
{
    componentType = CAMERA;
    this->cameraDepth = cameraDepth;
    this->vertFovRadians = glm::radians(vertFovDegrees);
    this->nearClip = nearClip;
    this->farClip = farClip;
}

void CameraComponent::setCameraTransformations() {
	if (!owningGameObject) return;

    // Get the current width and height of the rendering window
    glm::ivec2 dimensions = owningGameObject->getOwningGame()->getWindowDimensions();

    // Set the viewport for this camera using the normalized coordinates and dimensions
    glViewport(static_cast<GLint>(xLowerLeft * dimensions.x),
        static_cast<GLint>(yLowerLeft * dimensions.y),
        static_cast<GLint>(viewPortWidth * dimensions.x),
        static_cast<GLint>(viewPortHeight * dimensions.y));

    // Clear only the portion of the window associated with the camera viewport
    // using the scissor test
    glEnable(GL_SCISSOR_TEST);

    glScissor(static_cast<GLint>(xLowerLeft * dimensions.x),
        static_cast<GLint>(yLowerLeft * dimensions.y),
        static_cast<GLint>(viewPortWidth * dimensions.x),
        static_cast<GLint>(viewPortHeight * dimensions.y));

    glClearColor(cameraClearColor.r, cameraClearColor.g, cameraClearColor.b, cameraClearColor.a);
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    mat4 perspectProjection = glm::perspective(PI / 6.0f, (float)dimensions.x / dimensions.y, 1.0f, 1000.f);
    SharedTransformations::setProjectionMatrix(perspectProjection);

    // Get the modeling transformation of the owning game object
    mat4 modelingTrans = owningGameObject->getModelingTransformation();
    SharedTransformations::setViewMatrix(glm::inverse(modelingTrans));

}

void CameraComponent::setViewPort(GLfloat xLowerLeft, GLfloat yLowerLeft, GLfloat viewPortWidth, GLfloat viewPortHeight) {
    this->xLowerLeft = xLowerLeft;
    this->yLowerLeft = yLowerLeft;
    this->viewPortWidth = viewPortWidth;
    this->viewPortHeight = viewPortHeight;
}

CameraComponent::~CameraComponent() {
    removeCamera(std::shared_ptr<CameraComponent>(std::shared_ptr<CameraComponent>(), this));
}

void CameraComponent::addCamera(std::shared_ptr<class CameraComponent> cameraComponent) {
    auto iter = std::find(activeCameras.begin(), activeCameras.end(), cameraComponent);

    if (iter == activeCameras.end()) {
        activeCameras.emplace_back(cameraComponent);
        // sort cameras based on their depth value
        std::sort(activeCameras.begin(), activeCameras.end(), CompareCameraDepth);
    }
}

void CameraComponent::removeCamera(std::shared_ptr<class CameraComponent> cameraComponent) {
    auto iter = std::find(activeCameras.begin(), activeCameras.end(), cameraComponent);

    if (iter != activeCameras.end()) {
        if (VERBOSE) cout << "removeCamera" << endl;
        // swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, activeCameras.end() - 1);
        activeCameras.pop_back();
    }
}

const std::vector<std::shared_ptr<class CameraComponent>> CameraComponent::GetActiveCameras() {
    std::vector<std::shared_ptr<class CameraComponent>> sortedCameras = activeCameras;
    std::sort(sortedCameras.begin(), sortedCameras.end(), CameraComponent::CompareCameraDepth);
    return sortedCameras;
}

void CameraComponent::setCameraClearColor(vec4 clearColor) {
    cameraClearColor = clearColor;
}