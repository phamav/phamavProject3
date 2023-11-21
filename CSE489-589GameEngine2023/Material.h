#pragma once

#include "MathLibsConstsFuncs.h"

using namespace constants_and_types;

struct Material
{
	friend class SharedMaterials;

	Material()
	{
		static int id = 0; 
		_id = id++;
	}

	void setAmbientMat(glm::vec4 ambientMat)
	{
		this->ambientMat = glm::clamp(ambientMat, 0.0f, 1.0f);
	}

	void setDiffuseMat(glm::vec4 diffuseMat)
	{
		this->diffuseMat = glm::clamp(diffuseMat, 0.0f, 1.0f);
	}

	void setSpecularMat(glm::vec4 specularMat)
	{
		this->specularMat = glm::clamp(specularMat, 0.0f, 1.0f);
	}

	void setSpecularExponentMat(float specularExpMat)
	{
		this->specularExpMat = glm::clamp(specularExpMat, 0.0f, INFINITY);
	}

	void setEmissiveMat(glm::vec4 emissiveMat)
	{
		this->emissiveMat = glm::clamp(emissiveMat, 0.0f, 1.0f);;
	}

	void setAmbientAndDiffuseMat(glm::vec4 objectColor)
	{
		setAmbientMat(objectColor);
		setDiffuseMat(objectColor);

	}

	void setTextureMode(TextureMode textureMode)
	{
		if( textureMode >= NO_TEXTURE && textureMode <= REPLACE_AMBIENT_DIFFUSE)

		this->textureMode = textureMode;
	}

	void setDiffuseTexture(GLint textureObject)
	{
		this->diffuseTextureObject = textureObject;
		setTextureMode(REPLACE_AMBIENT_DIFFUSE);
		diffuseTextureEnabled = true;

	} // end setDiffuseTexture

	void setSpecularTexture(GLint textureObject)
	{
		this->specularTextureObject = textureObject;
		setTextureMode(REPLACE_AMBIENT_DIFFUSE);
		specularTextureEnabled = true;

	} // end setSpecularTexture

	void setNormalMap(GLint textureObject)
	{
		this->normalMapTextureObject = textureObject;
		normalMapTextureEnabled = true;

	} // end setNormalMap


	int _id;

protected:

	glm::vec4 ambientMat = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);

	glm::vec4 diffuseMat = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);

	glm::vec4 specularMat = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec4 emissiveMat = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	float specularExpMat = 64.0f;

	TextureMode textureMode = NO_TEXTURE;

	GLuint diffuseTextureObject = 0;
	bool diffuseTextureEnabled = false;

	GLuint specularTextureObject = 0;
	bool specularTextureEnabled = false;

	GLuint normalMapTextureObject = 0;
	bool normalMapTextureEnabled = false;

};


