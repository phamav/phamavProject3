#include "SharedFog.h"

glm::vec4 SharedFog::fogColor;
int SharedFog::fogMode;
float SharedFog::fogStart;
float SharedFog::fogEnd;
float SharedFog::fogDensity;

// Locations
GLuint SharedFog::fogColorLoc;
GLuint SharedFog::fogModeLoc;
GLuint SharedFog::fogStartLoc;
GLuint SharedFog::fogEndLoc;
GLuint SharedFog::fogDensityLoc;

SharedUniformBlock SharedFog::fogBlock(sharedFogBlockBindingPoint);
const std::string SharedFog::fogBlockName = "FogBlock";

void SharedFog::setUniformBlockForShader(GLuint shaderProgram) {
	std::vector<std::string> fogMemberNames = { "fogColor", "fogEnd", "fogStart", "fogDensity", "fogMode" };

	std::vector<GLint> uniformOffsets = fogBlock.setUniformBlockForShader(shaderProgram, fogBlockName, fogMemberNames);

	// Save locations
	fogColorLoc = uniformOffsets[0];
	fogEndLoc = uniformOffsets[1];
	fogStartLoc = uniformOffsets[2];
	fogDensityLoc = uniformOffsets[3];
	fogModeLoc = uniformOffsets[4];

	uniformOffsets.clear();
}

// getters
glm::vec4 SharedFog::getFogColor() {
	return fogColor;
}
int SharedFog::getFogMode() {
	return fogMode;
}
float SharedFog::getFogStart() {
	return fogStart;
}
float SharedFog::getFogEnd() {
	return fogEnd;
}
float SharedFog::getFogDensity() {
	return fogDensity;
}

// setters
void SharedFog::setFogColor(glm::vec4 fogColor) {
	if (fogBlock.getSize() > 0) {

		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, fogBlock.getBuffer());

		SharedFog::fogColor = fogColor;

		glBufferSubData(GL_UNIFORM_BUFFER, fogColorLoc, sizeof(glm::vec4), glm::value_ptr(fogColor));

		// Unbind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void SharedFog::setFogMode(int fogMode) {
	if (fogBlock.getSize() > 0) {

		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, fogBlock.getBuffer());

		SharedFog::fogMode = fogMode;

		glBufferSubData(GL_UNIFORM_BUFFER, fogModeLoc, sizeof(int), &fogMode);

		// Unbind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void SharedFog::setFogStart(float fogStart) {
	if (fogBlock.getSize() > 0) {

		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, fogBlock.getBuffer());

		SharedFog::fogStart = fogStart;

		glBufferSubData(GL_UNIFORM_BUFFER, fogStartLoc, sizeof(float), &fogStart);

		// Unbind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void SharedFog::setFogEnd(float fogEnd) {
	if (fogBlock.getSize() > 0) {

		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, fogBlock.getBuffer());

		SharedFog::fogEnd = fogEnd;

		glBufferSubData(GL_UNIFORM_BUFFER, fogEndLoc, sizeof(float), &fogEnd);

		// Unbind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void SharedFog::setFogDensity(float fogDensity) {
	if (fogBlock.getSize() > 0) {

		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, fogBlock.getBuffer());

		SharedFog::fogDensity = fogDensity;

		glBufferSubData(GL_UNIFORM_BUFFER, fogDensityLoc, sizeof(float), &fogDensity);

		// Unbind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}