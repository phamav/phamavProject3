#include "SharedMaterials.h"

GLuint SharedMaterials::ambientMatLocation; // Byte offset ambient material color

GLuint SharedMaterials::diffuseMatLocation; // Byte offset diffuse material color

GLuint SharedMaterials::specularMatLocation; // Byte offset specular material color

GLuint SharedMaterials::emmissiveMatLocation; // Byte offset emmisive material color

GLuint SharedMaterials::specularExpLocation;  // Byte offset ambient material color

GLuint SharedMaterials::diffuseTextureEnabledLocation;

GLuint SharedMaterials::specularTextureEnabledLocation;

GLuint SharedMaterials::normalMapEnabledLocation;

GLuint SharedMaterials::textureModeLoction;

SharedUniformBlock SharedMaterials::materialBlock(materialBlockBindingPoint);

const std::string SharedMaterials::materialBlockName = "MaterialBlock";


void SharedMaterials::setUniformBlockForShader(GLuint shaderProgram)
{
	std::vector<std::string> materialMemberNames = { "object.ambientMat", "object.diffuseMat", 
		"object.specularMat", "object.emmissiveMat", "object.specularExp", "object.diffuseTextureEnabled" ,
		"object.specularTextureEnabled", "object.normalMapTextureEnabled", "object.textureMode" };

	std::vector<GLint> uniformOffsets = materialBlock.setUniformBlockForShader(shaderProgram, materialBlockName, materialMemberNames);

	// Save locations
	ambientMatLocation = uniformOffsets[0];
	diffuseMatLocation = uniformOffsets[1];
	specularMatLocation = uniformOffsets[2];
	emmissiveMatLocation = uniformOffsets[3];
	specularExpLocation = uniformOffsets[4];
	diffuseTextureEnabledLocation = uniformOffsets[5];
	specularTextureEnabledLocation = uniformOffsets[6];
	normalMapEnabledLocation = uniformOffsets[7];
	textureModeLoction = uniformOffsets[8];

} // end setUniformBlockForShader


void SharedMaterials::setShaderMaterialProperties(const Material & material)
{
	if (materialBlock.getSize() > 0) {

		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, materialBlock.getBuffer());

		// Set the Material properties in the shader.
		glBufferSubData(GL_UNIFORM_BUFFER, ambientMatLocation, sizeof(glm::vec4), &material.ambientMat);
		glBufferSubData(GL_UNIFORM_BUFFER, diffuseMatLocation, sizeof(glm::vec4), &material.diffuseMat);
		glBufferSubData(GL_UNIFORM_BUFFER, specularMatLocation, sizeof(glm::vec4), &material.specularMat);
		glBufferSubData(GL_UNIFORM_BUFFER, emmissiveMatLocation, sizeof(glm::vec4), &material.emissiveMat);
		glBufferSubData(GL_UNIFORM_BUFFER, specularExpLocation, sizeof(float), &material.specularExpMat);
		glBufferSubData(GL_UNIFORM_BUFFER, diffuseTextureEnabledLocation, sizeof(bool), &material.diffuseTextureEnabled);
		glBufferSubData(GL_UNIFORM_BUFFER, specularTextureEnabledLocation, sizeof(bool), &material.specularTextureEnabled);
		glBufferSubData(GL_UNIFORM_BUFFER, normalMapEnabledLocation, sizeof(bool), &material.normalMapTextureEnabled);
		glBufferSubData(GL_UNIFORM_BUFFER, textureModeLoction, sizeof(int), &material.textureMode);

		// Unbind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Activate and set texture units.
		if (material.diffuseTextureEnabled == true) {

			glBindTextureUnit(0, material.diffuseTextureObject);

		}
		if (material.specularTextureEnabled == true) {

			glBindTextureUnit(1, material.specularTextureObject);
		}

		if (material.normalMapTextureEnabled == true) {

			glBindTextureUnit(2, material.normalMapTextureObject);
		}

	}
	if (material.diffuseMat.a < 1.0) {

		glEnable(GL_BLEND);
	}

} // end setShaderMaterialProperties


void SharedMaterials::cleanUpMaterial(const Material & material)
{
	//if (material.diffuseTextureEnabled == true) {

	//	//glBindTextureUnit(0, 0);
	//}
	//if (material.specularTextureEnabled == true) {

	//	//glBindTextureUnit(1, 0);
	//}
	
	if (material.diffuseMat.a < 1.0) {

		glDisable(GL_BLEND);
	}
}
