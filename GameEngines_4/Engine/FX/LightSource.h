#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>
class LightSource
{
public:

	LightSource();
	LightSource(glm::vec3 position_, glm::vec3 lightColour_, float ambientValue_, float diffuseValue_, float specularValue_);
	~LightSource();

	glm::vec3 getPosition() const;
	glm::vec3 getLightColour() const;

	float getAmbientValue() const;
	float getDiffuseValue() const;
	float getSpecularValue() const;


	void setPosition(glm::vec3 position_);
	void setLightColour(glm::vec3 lightColour_);

	void setAmbientValue(float ambientValue_);
	void setDiffuseValue(float diffuseValue_);
	void setSpecularValue(float specularValue_);
private:
	glm::vec3 position;
	glm::vec3 lightColour;

	float ambientValue;
	float diffuseValue;
	float specularValue;
};
#endif // !LIGHTSOURCE_H

