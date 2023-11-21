#pragma once

#include "MathLibsConstsFuncs.h"
#include "SharedUniformBlock.h"

#define sharedFogBlockBindingPoint 9

class SharedFog
{
public:
	static void setUniformBlockForShader(GLuint shaderProgram);

	// getters
	static glm::vec4 getFogColor();
	static int getFogMode();
	static float getFogStart();
	static float getFogEnd();
	static float getFogDensity();

	// setters
	static void setFogColor(glm::vec4 fogColor);
	static void setFogMode(int fogMode);
	static void setFogStart(float fogStart);
	static void setFogEnd(float fogEnd);
	static void setFogDensity(float fogDensity);
private:
	static glm::vec4 fogColor;
	static int fogMode;
	static float fogStart;
	static float fogEnd;
	static float fogDensity;

	// Locations
	static GLuint fogColorLoc;
	static GLuint fogModeLoc;
	static GLuint fogStartLoc;
	static GLuint fogEndLoc;
	static GLuint fogDensityLoc;
	
	static SharedUniformBlock fogBlock;
	static const std::string fogBlockName;
};

