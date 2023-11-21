#include "SharedLighting.h"

#include <sstream> 

GeneralLight SharedLighting::lights[MAX_LIGHTS];

const std::string SharedLighting::generalLightBlockName = "LightBlock";

SharedUniformBlock SharedLighting::lightBlock(generalLightBlockBindingPoint);


void SharedLighting::setUniformBlockForShader(GLuint shaderProgram)
{
	std::vector <std::string > lightBlockMemberNames = buildUniformBlockNameList();

	std::vector<GLint> uniformOffsets = lightBlock.setUniformBlockForShader(shaderProgram,
		generalLightBlockName,
		lightBlockMemberNames);
	int offsetIndex = 0;

	for (int i = 0; i < MAX_LIGHTS; i++) {

		// Light color locations
		lights[i].ambientColorLoc = uniformOffsets[offsetIndex++];
		lights[i].diffuseColorLoc = uniformOffsets[offsetIndex++];
		lights[i].specularColorLoc = uniformOffsets[offsetIndex++];

		// Position and direction location
		lights[i].positionOrDirectionLoc = uniformOffsets[offsetIndex++];

		// Spotlight locations
		lights[i].spotDirectionLoc = uniformOffsets[offsetIndex++];
		lights[i].isSpotLoc = uniformOffsets[offsetIndex++];
		lights[i].spotCutoffCosLoc = uniformOffsets[offsetIndex++];
		lights[i].spotExponentLoc = uniformOffsets[offsetIndex++];

		//Attenuation factor locations
		lights[i].constantLoc = uniformOffsets[offsetIndex++];
		lights[i].linearLoc = uniformOffsets[offsetIndex++];
		lights[i].quadraticLoc = uniformOffsets[offsetIndex++];

		// Enabled location
		lights[i].enabledLoc = uniformOffsets[offsetIndex++];

		// Initialize the attributes of the light to something meaningful
		initilizeAttributes(i);
	}

} // end setUniformBlockForShader


std::vector<std::string> SharedLighting::buildUniformBlockNameList()
{
	static const int NUM_LIGHT_ATTRIBUTES = 12;

	// Get the indices of the uniform block variables in the shader
	static const std::string names[NUM_LIGHT_ATTRIBUTES]
		= { "ambientColor", "diffuseColor", "specularColor",
		"positionOrDirection", "spotDirection",
		"isSpot", "spotCutoffCos", "spotExponent",
		"constant", "linear", "quadratic", "enabled" };

	std::vector<std::string> uniformBlockNames;

	for (int lightNumber = 0; lightNumber < MAX_LIGHTS; lightNumber++) {

		// Get string representation of the int
		std::string numberStrg = std::to_string(lightNumber);

		std::string uniformNames[NUM_LIGHT_ATTRIBUTES];

		for (int i = 0; i < NUM_LIGHT_ATTRIBUTES; i++) {

			uniformBlockNames.push_back("lights[" + numberStrg + "]." + names[i]);
		}

	}

	return uniformBlockNames;

}


void SharedLighting::initilizeAttributes(GLint lightNumber)
{
	setEnabled(lightNumber, lights[lightNumber].enabled);

	setAmbientColor(lightNumber, lights[lightNumber].ambientColor);
	setDiffuseColor(lightNumber, lights[lightNumber].diffuseColor);
	setSpecularColor(lightNumber, lights[lightNumber].specularColor);

	setPositionOrDirection(lightNumber, lights[lightNumber].positionOrDirection);

	setIsSpot(lightNumber, lights[lightNumber].isSpot);
	setSpotDirection(lightNumber, lights[lightNumber].spotDirection);
	setSpotCutoffCos(lightNumber, lights[lightNumber].spotCutoffCos);
	setSpotExponent(lightNumber, lights[lightNumber].spotExponent);

	setConstantAttenuation(lightNumber, lights[lightNumber].constant);
	setLinearAttenuation(lightNumber, lights[lightNumber].linear);
	setQuadraticAttenuation(lightNumber, lights[lightNumber].quadratic);

}


void SharedLighting::setEnabled(int lightIndex, bool on)
{
	// Bind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].enabled = on;

	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].enabledLoc, sizeof(bool), &lights[lightIndex].enabled);

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setAmbientColor(int lightIndex, glm::vec4 color4)
{
	// Bind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].ambientColor = color4;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].ambientColorLoc, sizeof(glm::vec4), value_ptr(lights[lightIndex].ambientColor));

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setDiffuseColor(int lightIndex, glm::vec4 color4)
{
	// Bind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].diffuseColor = color4;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].diffuseColorLoc, sizeof(glm::vec4), value_ptr(lights[lightIndex].diffuseColor));

	// Unbind the buffer.
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setSpecularColor(int lightIndex, glm::vec4 color4)
{
	// Bind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].specularColor = color4;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].specularColorLoc, sizeof(glm::vec4), value_ptr(lights[lightIndex].specularColor));

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setPositionOrDirection(int lightIndex, glm::vec4 positOrDirect)
{
	// Bind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].positionOrDirection = positOrDirect;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].positionOrDirectionLoc, sizeof(glm::vec4), value_ptr(lights[lightIndex].positionOrDirection));

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setAttenuationFactors(int lightIndex, glm::vec3 factors)
{
	setConstantAttenuation(lightIndex, factors.x);
	setLinearAttenuation(lightIndex, factors.y);
	setQuadraticAttenuation(lightIndex, factors.z);

}

void SharedLighting::setConstantAttenuation(int lightIndex, float factor)
{
	// Bind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].constant = factor;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].constantLoc, sizeof(float), &lights[lightIndex].constant);

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setLinearAttenuation(int lightIndex, float factor)
{
	// Bind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].linear = factor;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].linearLoc, sizeof(float), &lights[lightIndex].linear);

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setQuadraticAttenuation(int lightIndex, float factor)
{
	// Bind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].quadratic = factor;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].quadraticLoc, sizeof(float), &lights[lightIndex].quadratic);

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setIsSpot(int lightIndex, bool spotOn)
{
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].isSpot = spotOn;

	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].isSpotLoc, sizeof(bool), &lights[lightIndex].isSpot);

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setSpotDirection(int lightIndex, glm::vec3 spotDirect)
{
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].spotDirection = glm::normalize(spotDirect);
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].spotDirectionLoc, sizeof(glm::vec3), value_ptr(lights[lightIndex].spotDirection));

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setSpotCutoffCos(int lightIndex, float cutoffCos)
{
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].spotCutoffCos = cutoffCos;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].spotCutoffCosLoc, sizeof(float), &lights[lightIndex].spotCutoffCos);

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void SharedLighting::setSpotExponent(int lightIndex, float spotEx)
{
	glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());

	lights[lightIndex].spotExponent = spotEx;
	glBufferSubData(GL_UNIFORM_BUFFER, lights[lightIndex].spotExponentLoc, sizeof(float), &lights[lightIndex].spotExponent);

	// Unbind the buffer. 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}