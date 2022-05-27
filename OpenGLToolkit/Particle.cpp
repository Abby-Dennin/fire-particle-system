#include "Particle.h"

Particle::Particle() {}

Particle::Particle(glm::vec3 l) {
	location = l;
	velocity = glm::vec3(0.0, 0.001, 0);
	color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	lifespan = 255 * random(1.0, 1.5);
}

void Particle::update() {
	// calculating the movement of a particle, changed to get different types of movement
	double x_acc = 0.000004 * random(-1.0, 1.0);
	double y_acc = 0.000034 * random(-1.0, 1.0);
	double z_acc = 0.0;
	acceleration = glm::vec3(x_acc, y_acc, z_acc);
	velocity += acceleration;
	location += velocity;
	lifespan -= .7;
}

bool Particle::isDead() {
	if (lifespan < 0.0) {
		return true;
	}
	else {
		return false;
	} 
}

double Particle::random(double upper, double lower) {
	double range = (upper - lower);
	double random_double = lower + (range * ((double)rand()) / (RAND_MAX));
	return random_double;
}

glm::vec3 Particle::getPosition() {
	return location;
}

float Particle::getLifespan() {
	return lifespan;
}

glm::vec4 Particle::getColor() {
	return color;
}

void Particle::kill() {
	lifespan = 0.0;
}