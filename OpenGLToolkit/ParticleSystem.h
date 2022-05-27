#pragma once

#include <vector>
#include <random>
#include <glad/glad.h>

#include "Particle.h"

class ParticleSystem {
public:
	ParticleSystem();
	ParticleSystem(glm::vec3 emitter);
	void CreateParticles(GLuint NumberOfParticlesIn);
	void Render();
	void Update(int type);
	glm::vec3 random();

	std::vector<GLfloat> ParticlePositionData;
	std::vector<GLubyte> ParticleColorData;

	GLuint ParticlePositionBufferLocation;
	GLuint ParticleColorBufferLocation;
	std::vector<Particle> particles;

private:
	GLuint ParticleObjectLocation;
	GLuint ParticleColorLocation;
	GLuint NumberOfParticles;
	glm::vec3 emitter;
};