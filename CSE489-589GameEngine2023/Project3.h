#pragma once

#include "GameEngine.h"

class Project3 : public Game
{
protected:
	bool t_key = false;
	std::shared_ptr<GameObject> sphereObject;
	std::shared_ptr<GameObject> boxObject;
	std::shared_ptr<GameObject> modelObject;

	std::shared_ptr<CameraComponent> mainCamComp;
	std::shared_ptr<CameraComponent> secondCamComp;

	virtual void processGameInput()
	{
		Game::processGameInput(); // call to superclass

		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0)) {
			SharedFog::setFogMode(0); // no fog
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_1)) {
			SharedFog::setFogMode(1); // linear fog
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_2)) {
			SharedFog::setFogMode(2); // exp fog
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_3)) {
			SharedFog::setFogMode(3); // exp two fog
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_EQUAL)) {
			SharedFog::setFogDensity(SharedFog::getFogDensity() + 0.001f); // add fog density
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_MINUS)) {
			SharedFog::setFogDensity(glm::max(SharedFog::getFogDensity() - 0.001f, 0.0f)); // reduce fog density
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_PERIOD)) {
			float newFogStart = SharedFog::getFogStart() + 5.0f;
			if (newFogStart < SharedFog::getFogEnd()) {
				SharedFog::setFogStart(newFogStart);
			}
		}
		else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_COMMA)) {
			float newFogStart = SharedFog::getFogStart() - 5.0f;
			if (newFogStart >= 0.0f) { // Fog start should not be negative
				SharedFog::setFogStart(newFogStart);
			}
		}
	}

	void loadScene() override
	{
		// Set the window title
		glfwSetWindowTitle(renderWindow, "CSE 489/589 GameEngine Fall 2023 Project Three");

		// Set the clear color
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		// Build and use the shader program
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "Shaders/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		GLuint shaderProgram = BuildShaderProgram(shaders);

		SharedMaterials::setUniformBlockForShader(shaderProgram);
		SharedTransformations::setUniformBlockForShader(shaderProgram);
		SharedLighting::setUniformBlockForShader(shaderProgram);
		SharedFog::setUniformBlockForShader(shaderProgram);

		//// ******* Light Objects ******

		// Create the directional light game object and component
		auto dirLightObject = std::make_shared<GameObject>();
		auto dirLightComp = std::make_shared<DirectionalLightComponent>(GLFW_KEY_D); // 'D' key to toggle
		
		addChildGameObject(dirLightObject);

		dirLightObject->setPosition(glm::vec3(20.0f, 10.0f, 0.0f));
		dirLightComp->setAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		dirLightComp->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		dirLightComp->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		
		dirLightObject->addComponent(dirLightComp);

		// Create the positional light game object and component
		auto posLightObject = std::make_shared<GameObject>();
		auto posLightComp = std::make_shared<PositionalLightComponent>(GLFW_KEY_P); // 'P' key to toggle
		
		addChildGameObject(posLightObject);

		posLightObject->setPosition(glm::vec3(10.0f, 10.0f, 10.0f));
		posLightComp->setAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		posLightComp->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // Bright white light
		posLightComp->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		posLightObject->addComponent(posLightComp);

		// Create the spotlight game object and component
		auto spotLightObject = std::make_shared<GameObject>();
		auto spotLightComp = std::make_shared<SpotLightComponent>(GLFW_KEY_S); // 'S' key to toggle
		
		addChildGameObject(spotLightObject);

		spotLightObject->setPosition(glm::vec3(0.0f, 0.0f, 10.0f)); // Adjust position as needed
		spotLightComp->setSpotDirection(glm::vec3(0.0f, 0.0f, -2.0f)); // Pointing towards the objects
		spotLightComp->setSpotCutoffCos(glm::cos(glm::radians(50.0f))); // Wider angle for the spotlight
		spotLightComp->setSpotExponent(50.0f); // Softer falloff
		
		spotLightObject->addComponent(spotLightComp);

		// Add the main (front) camera
		auto mainCamObj = std::make_shared<GameObject>();
		mainCamComp = std::make_shared<CameraComponent>(0); // depth 0
		addChildGameObject(mainCamObj);

		mainCamObj->setPosition(vec3(0.0f, 0.0f, 20.0f));
		mainCamObj->addComponent(std::make_shared<ArrowRotateComponent>());
		mainCamObj->addComponent(mainCamComp);

		// Add a second camera
		auto secondCamObj = std::make_shared<GameObject>();
		secondCamComp = std::make_shared<CameraComponent>(1, 90.0f);
		addChildGameObject(secondCamObj);

		secondCamObj->setPosition(vec3(-15.0f, 0.0f, 20.0f));
		secondCamObj->rotateTo(ZERO_V3 - vec3(-15.0f, 0.0f, 20.0f));
		secondCamObj->setPosition(vec3(-15.0f, 0.0f, 20.0f));

		secondCamComp->setViewPort(0.6f, 0.6f, 0.4f, 0.4f);
		secondCamObj->addComponent(secondCamComp);

		//// ***** Sound Setup *****

		// Create a new GameObject for sound source
		auto soundOne = std::make_shared<GameObject>();
		addChildGameObject(soundOne);
		soundOne->setPosition(vec3(0.0f, 0.0f, 0.0f));

		// Create a SoundSourceComponent and attach it to soundObject
		auto soundSourceComp = std::make_shared<SoundSourceComponent>("Assets/iamtheprotectorofthissystem.wav", 1.0f, 5.0f, 100.0f);
		soundOne->addComponent(soundSourceComp);

		// Set properties for the sound source
		soundSourceComp->setLooping(true);
		soundSourceComp->setGain(1.0f); // full volume

		// Start playing the sound
		soundSourceComp->play();

		//// ***** SIMULATION ******

		// Includes the Sun, Earth, Earth’s moon 
		// and >= 1 other planet.

		// ***** Sun ******
		auto sunGameObject = std::make_shared<GameObject>();
		this->addChildGameObject(sunGameObject);
		sunGameObject->setPosition(vec3(0.0f, 0.0f, 0.0f), WORLD);

		Material sunMat;
		sunMat.setEmissiveMat(YELLOW_RGBA);
		auto sunMesh = std::make_shared<SphereMeshComponent>(shaderProgram, sunMat);
		sunGameObject->addComponent(sunMesh);

		// Sun has a positional light source at its location
		// TODO: create the positional light source

		// ***** Empty GameObject ****
		auto emptyGameObject = std::make_shared<GameObject>();
		addChildGameObject(emptyGameObject);
		emptyGameObject->addComponent(std::make_shared<SpinComponent>());

		// ***** Empty GameObject 2 ****
		auto emptyGameObject2 = std::make_shared<GameObject>();
		addChildGameObject(emptyGameObject2);
		emptyGameObject2->setPosition(vec3(-50.0f, 0.0f, 0.0f), LOCAL);

		// ***** Earth *****
		auto earthGameObject = std::make_shared<GameObject>();
		emptyGameObject2->addChildGameObject(earthGameObject);

		Material earthMat;
		earthMat.setDiffuseTexture(Texture::GetTexture("Textures/earthmap.jpg")->getTextureObject());
		auto earthMesh = std::make_shared<SphereMeshComponent>(shaderProgram);
		earthGameObject->addComponent(earthMesh);
		earthGameObject->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 90.0f));
		

	} // end loadScene


};
