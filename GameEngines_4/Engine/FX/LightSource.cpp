#include "LightSource.h"

LightSource::LightSource()
{
	position = glm::vec3(0, 0, 0);
	lightColour = glm::vec3(1, 1, 1);
	ambientValue = 1;
	diffuseValue = 1;
	specularValue = 1;
}

LightSource::LightSource(glm::vec3 position_, glm::vec3 lightColour_, float ambientValue_, float diffuseValue_, float specularValue_)
{
	position = position_;
	lightColour = lightColour_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
	specularValue = specularValue_;

}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::getPosition() const
{
	return position;
}

glm::vec3 LightSource::getLightColour() const
{
	return lightColour;
}

float LightSource::getAmbientValue() const
{
	return ambientValue;
}

float LightSource::getDiffuseValue() const
{
	return diffuseValue;
}

float LightSource::getSpecularValue() const
{
	return specularValue;
}

void LightSource::setPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::setLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
}

void LightSource::setAmbientValue(float ambientValue_)
{
	ambientValue = ambientValue_;
}

void LightSource::setDiffuseValue(float diffuseValue_)
{
	diffuseValue = diffuseValue_;
}

void LightSource::setSpecularValue(float specularValue_)
{
	specularValue = specularValue_;
}

