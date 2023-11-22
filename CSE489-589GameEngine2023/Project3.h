#pragma once

#include "GameEngine.h"

class Project3 : public Game
{
protected:
	std::shared_ptr<CameraComponent> mainCamComp;
	std::shared_ptr<CameraComponent> secondCamComp;

	virtual void processGameInput()
	{
		Game::processGameInput(); // call to superclass
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

		//// ******* Cameras **********

		// Add the main (front) camera
		auto mainCamObj = std::make_shared<GameObject>();
		mainCamComp = std::make_shared<CameraComponent>(); // depth 0
		addChildGameObject(mainCamObj);

		mainCamObj->setPosition(vec3(0.0f, 400.0f, 0.0f));
		mainCamObj->rotateTo(vec3(0.0f, -1.0f, 0.0f));
		mainCamComp->setViewPort(0.0f, 0.5f, 1.0f, 0.5f);
		mainCamObj->addComponent(std::make_shared<ArrowRotateComponent>());
		mainCamObj->addComponent(mainCamComp);

		//// ***** SIMULATION ******

		// Includes the Sun, Earth, Earth’s moon 
		// and >= 1 other planet.

		// ***** Sun ******
		auto sunGameObject = std::make_shared<GameObject>();
		addChildGameObject(sunGameObject);
		sunGameObject->setPosition(vec3(0.0f, 0.0f, 0.0f), WORLD);

		Material sunMat;
		sunMat.setDiffuseTexture(Texture::GetTexture("Textures/sun.jfif")->getTextureObject());
		sunMat.setTextureMode(DECAL);
		auto sunMesh = std::make_shared<SphereMeshComponent>(shaderProgram, sunMat, 20.0f);
		sunGameObject->addComponent(sunMesh);

		// Sun has a positional light source at its location
		std::shared_ptr<GameObject> sunLight = std::make_shared<GameObject>();
		addChildGameObject(sunLight);
		sunLight->setPosition(vec3(0.0f, 0.0f, 0.0f));
		sunLight->addComponent(std::make_shared<PositionalLightComponent>(GLFW_KEY_S));


		// ***** Earth and Moon *****
		auto earthGameObject = std::make_shared<GameObject>();
		auto earthOrbitSun = std::make_shared<GameObject>();
		auto moonGameObject = std::make_shared<GameObject>();
		auto moonOrbitEarth = std::make_shared<GameObject>();

		addChildGameObject(earthOrbitSun);
		earthOrbitSun->addChildGameObject(earthGameObject);
		earthOrbitSun->addChildGameObject(moonOrbitEarth);
		moonOrbitEarth->addChildGameObject(moonGameObject);

		// Apply texture for Earth
		Material earthMat;
		earthMat.setDiffuseTexture(Texture::GetTexture("Textures/Terrestrial1.png")->getTextureObject());
		auto earthMesh = std::make_shared<SphereMeshComponent>(shaderProgram, earthMat, 8.0f);
		earthGameObject->addComponent(earthMesh);
		earthGameObject->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 90.0f));

		// Apply texture for Moon
		Material moonMat;
		moonMat.setDiffuseTexture(Texture::GetTexture("Textures/moon.jpg")->getTextureObject());
		auto moonMesh = std::make_shared<SphereMeshComponent>(shaderProgram, moonMat, 3.0f);
		moonGameObject->addComponent(moonMesh);
		moonGameObject->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 45.0f)); // Moon's spin

		// Configure Earth's and Moon's positions
		earthOrbitSun->setPosition(vec3(0.0f, 0.0f, 0.0f));
		earthGameObject->setPosition(vec3(-50.0f, 0.0f, 0.0f));
		moonOrbitEarth->setPosition(earthGameObject->getPosition());
		moonGameObject->setPosition(vec3(-75.0f, 0.0f, 0.0f));

		// Configure Earth's and Moon's orbital motion
		earthOrbitSun->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 5.0f)); // Earth's orbit
		moonOrbitEarth->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 12.0f)); // Moon's orbit

		earthGameObject->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 20.0f));
		moonGameObject->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 10.0f));

		// ***** Jupiter *****
		auto jupiterGameObject = std::make_shared<GameObject>();
		auto jupiterOrbitSun = std::make_shared<GameObject>();
		addChildGameObject(jupiterOrbitSun); // Jupiter's orbit around the Sun
		jupiterOrbitSun->addChildGameObject(jupiterGameObject); // Jupiter

		// Configure Jupiter
		Material jupiterMat;
		jupiterMat.setDiffuseTexture(Texture::GetTexture("Textures/Gaseous1.png")->getTextureObject());
		auto jupiterMesh = std::make_shared<SphereMeshComponent>(shaderProgram, jupiterMat, 10.0f);
		jupiterGameObject->addComponent(jupiterMesh);

		// Configure Jupiter's orbital motion and position
		jupiterOrbitSun->setPosition(vec3(0.0f, 0.0f, 0.0f));
		jupiterOrbitSun->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 3.0f)); // Jupiter's orbit

		jupiterGameObject->setPosition(vec3(-100.0f, 0.0f, 0.0f));
		jupiterGameObject->addComponent(std::make_shared<SpinComponent>(UNIT_Y_V3, 5.0f)); // Jupiter's spin


		// ***** Spaceship *****
		auto spaceshipObj = std::make_shared<GameObject>();
		addChildGameObject(spaceshipObj);
		std::shared_ptr<ModelMeshComponent> spaceshipMesh = std::make_shared<ModelMeshComponent>("Assets/jet_models/F-15C_Eagle.obj", shaderProgram);
		spaceshipObj->addComponent(spaceshipMesh);
		spaceshipObj->setPosition(vec3(-50.0f, 0.0f, 0.0f));
		spaceshipObj->setScale(vec3(1.0f, 1.0f, 1.0f));

		std::vector<std::shared_ptr<GameObject>> waypoints = { sunGameObject, earthGameObject, jupiterGameObject };
		auto spaceshipJourney = std::make_shared<JourneyComponent>(waypoints, vec3(0.0f, 0.0f, 10.0f));
		spaceshipObj->addComponent(spaceshipJourney);

		// Add the spotlight to the spaceship
		auto lightObj = std::make_shared<GameObject>();
		spaceshipObj->addChildGameObject(lightObj);
		addChildGameObject(lightObj);
		auto spotlight = std::make_shared<SpotLightComponent>(GLFW_KEY_L);
		spotlight->setSpotExponent(300.0f);
		lightObj->addComponent(spotlight);

		// Add a second camera follows behind the spaceship
		auto secondCamObj = std::make_shared<GameObject>();
		spaceshipObj->addChildGameObject(secondCamObj);
		secondCamComp = std::make_shared<CameraComponent>();
		addChildGameObject(secondCamObj);
		secondCamObj->setPosition(vec3(0.0f, 0.0f, 50.0f));
		secondCamComp->setViewPort(0.0f, 0.0f, 1.0f, 0.5f);
		secondCamObj->addComponent(secondCamComp);

		// Add sound listener to spaceship
		auto listener = std::make_shared<SoundListenerComponent>();
		spaceshipObj->addComponent(listener);

		// ***** Sound Setup *****

		// Sun Sound
		auto sunSoundComp = std::make_shared<SoundSourceComponent>("Assets/nasa_sun.wav");
		sunGameObject->addComponent(sunSoundComp);
		sunSoundComp->setLooping(true);
		sunSoundComp->setGain(0.5f);
		sunSoundComp->setRollOffFactor(30.0f);
		sunSoundComp->play();

		// Earth Sound
		auto earthSoundComp = std::make_shared<SoundSourceComponent>("Assets/earth_tsunami.wav");
		earthGameObject->addComponent(earthSoundComp);
		earthSoundComp->setLooping(true);
		earthSoundComp->setGain(1.0f);
		earthSoundComp->setRollOffFactor(15.0f);
		earthSoundComp->play();

		// Moon Sound
		auto moonSoundComp = std::make_shared<SoundSourceComponent>("Assets/moon_landing.wav");
		moonGameObject->addComponent(moonSoundComp);
		moonSoundComp->setLooping(true);
		moonSoundComp->setGain(1.0f);
		moonSoundComp->setRollOffFactor(10.0f);
		moonSoundComp->play();

		// Jupiter Sound
		auto jupiterSoundComp = std::make_shared<SoundSourceComponent>("Assets/nasa_jupiter.wav");
		jupiterGameObject->addComponent(jupiterSoundComp);
		jupiterSoundComp->setLooping(true);
		jupiterSoundComp->setGain(1.0f);
		jupiterSoundComp->setRollOffFactor(20.0f);
		jupiterSoundComp->play();

	} // end loadScene


};
