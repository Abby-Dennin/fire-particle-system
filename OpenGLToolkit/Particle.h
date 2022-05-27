#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Particle
{
private:
	glm::vec3 location;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec4 color;
	float lifespan;
public:
	Particle();
	Particle(glm::vec3 l);

	void update();
	bool isDead();
	double random(double upper, double lower);
	glm::vec3 getPosition();
	float getLifespan();
	glm::vec4 getColor();
	void kill();

};

