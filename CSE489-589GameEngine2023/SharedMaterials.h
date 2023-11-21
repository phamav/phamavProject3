#pragma once

#include "MathLibsConstsFuncs.h"
#include "SharedUniformBlock.h"

#include "Material.h"

#define materialBlockBindingPoint 12
#define diffuseSamplerLocation 100
#define specularSamplerLocation 101
#define normalMapSamplerLocation 102

using namespace constants_and_types;

class SharedMaterials
{
public:

	// Should be called for each shader program that includes the
	// Material*uniform block.
	static void setUniformBlockForShader(GLuint shaderProgram);

	// Call the set the Material*properties in the shader before 
	// rendering the object.
	static void setShaderMaterialProperties(const Material & material);

	// Cleans Material*properties after rendering an object.
	static void cleanUpMaterial(const Material & material);

protected:

	static GLuint ambientMatLocation; // Byte offset ambient material color

	static GLuint diffuseMatLocation; // Byte offset diffuse material color

	static GLuint specularMatLocation; // Byte offset specular material color

	static GLuint emmissiveMatLocation; // Byte offset emmisive material color

	static GLuint specularExpLocation;  // Byte offset specular exponent

	static GLuint diffuseTextureEnabledLocation;

	static GLuint specularTextureEnabledLocation;

	static GLuint normalMapEnabledLocation;

	static GLuint textureModeLoction;

	static SharedUniformBlock materialBlock;

	const static std::string materialBlockName;

};