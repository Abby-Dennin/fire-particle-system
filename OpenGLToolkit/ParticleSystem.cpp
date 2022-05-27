#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
}

ParticleSystem::ParticleSystem(glm::vec3 l) {
	emitter = l;
}

void ParticleSystem::CreateParticles(GLuint NumberOfParticlesIn) {
	NumberOfParticles = NumberOfParticlesIn;

	for (size_t i = 0; i < NumberOfParticles; i++) {
		
		glm::vec3 temp = random();
		temp += emitter;
		Particle p(emitter);
		particles.push_back(p);

		ParticlePositionData.push_back(p.getPosition().x); 
		ParticlePositionData.push_back(p.getPosition().y);
		ParticlePositionData.push_back(0.0f);
		ParticlePositionData.push_back(p.getColor().r);
	    ParticlePositionData.push_back(p.getColor().g);
		ParticlePositionData.push_back(p.getColor().b);

		float alpha = 1.2 - p.getLifespan() / 255;

		if (alpha > 0.95f) {
			alpha = 0.94f;
		}

		ParticlePositionData.push_back(alpha);
	}

	glGenVertexArrays(1, &ParticleObjectLocation);
	glBindVertexArray(ParticleObjectLocation);

	glGenBuffers(1, &ParticlePositionBufferLocation);

	glBindBuffer(GL_ARRAY_BUFFER, ParticlePositionBufferLocation);
	glBufferData(GL_ARRAY_BUFFER, ParticlePositionData.size() * sizeof(GLfloat), ParticlePositionData.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
}

void ParticleSystem::Render() {
	glBindVertexArray(ParticleObjectLocation);
	glDrawArrays(GL_POINTS, 0, NumberOfParticles);
	glBindVertexArray(0);
}

void ParticleSystem::Update(int type) {
	glBindBuffer(GL_ARRAY_BUFFER, ParticlePositionBufferLocation);

	// Updates the data for each individual particle
	for (int i = 0; i < NumberOfParticles; i++) {
		particles[i].update();
	}

	for (int i = 0; i < NumberOfParticles; i = i++) {

		// Setting the alpha based on lifespan with clamps so it does not get too dark or too light
		float alpha = 1.2 - particles[i].getLifespan() / 255;

		if (alpha > .95) {
			alpha = 1.0;
		}
		else if (alpha < 0.75) {
			alpha = 0.75;
		}

		if (particles[i].isDead()) {
			// If a particle dies, it is respawned at the emitter
			glm::vec3 temp = particles[i].getPosition();
			temp += emitter;
			Particle p(emitter);
			particles[i] = p;
		}
		else {

			float curr_x = particles[i].getPosition().x;
			float curr_y = particles[i].getPosition().y;

			// Sets x, y, z in position buffer
			ParticlePositionData[i * 7] = curr_x;
			ParticlePositionData[i * 7 + 1] = curr_y;
			ParticlePositionData[i * 7 + 2] = 0.0f;

			/* Horizontal Rainbow cutoffs
			
			if (curr_x >= -1.0 && curr_x < -0.75) {
				ParticlePositionData[i * 7 + 3] = 1.0f;
				ParticlePositionData[i * 7 + 4] = 0.0f;
				ParticlePositionData[i * 7 + 5] = 0.0f;
			}
			else if (curr_x >= -0.75 && curr_x < -0.5) {
				ParticlePositionData[i * 7 + 3] = 1.0f;
				ParticlePositionData[i * 7 + 4] = 165.0 / 255.0;
				ParticlePositionData[i * 7 + 5] = 0.0f;
			}
			else if (curr_x >= -0.5 && curr_x < -0.25) {
				ParticlePositionData[i * 7 + 3] = 1.0f;
				ParticlePositionData[i * 7 + 4] = 1.0f;
				ParticlePositionData[i * 7 + 5] = 0.0f;
			}
			else if (curr_x >= -0.25 && curr_x < 0.0) {
				ParticlePositionData[i * 7 + 3] = 0.0f;
				ParticlePositionData[i * 7 + 4] = 0.5f;
				ParticlePositionData[i * 7 + 5] = 0.0f;
			}
			else if (curr_x >= 0.0 && curr_x < 0.25) {
				ParticlePositionData[i * 7 + 3] = 0.0f;
				ParticlePositionData[i * 7 + 4] = 0.0f;
				ParticlePositionData[i * 7 + 5] = 0.5f;
			}
			else if (curr_x >= 0.25 && curr_x < 0.5) {
				ParticlePositionData[i * 7 + 3] = 0.0f;
				ParticlePositionData[i * 7 + 4] = 0.0f;
				ParticlePositionData[i * 7 + 5] = 1.0f;
			}
			else if (curr_x >= 0.5 && curr_x < 0.75) {
				ParticlePositionData[i * 7 + 3] = 75.0 / 255.0;
				ParticlePositionData[i * 7 + 4] = 0.0f;
				ParticlePositionData[i * 7 + 5] = 130.0 / 255.0;
			}
			else if (curr_x >= 0.75 && curr_x < 1.0) {
				ParticlePositionData[i * 7 + 3] = 238.0 / 255.0;
				ParticlePositionData[i * 7 + 4] = 130.0 / 255.0;
				ParticlePositionData[i * 7 + 5] = 238.0 / 255.0;
			}
	
			*/

			// If it floats too high, set its lifespan to zero so that
			// it is respawned in the next update
		    if (curr_y > 0.2) {
				particles[i].kill();
			}

			// Changes the color data at this height to a smokey color
			else if (curr_y > -0.12) {
				ParticlePositionData[i * 7 + 3] = 0.5f;
				ParticlePositionData[i * 7 + 4] = 0.5f;
				ParticlePositionData[i * 7 + 5] = 0.5f;
			}

			// Different types of particle systems, mainly for controlling colors but could have other uses

			// Handles the small inner flame with various shades of blue
			else if (type == 0) {
				if (curr_y < -0.8) {
					if (curr_x > -0.005 && curr_x < 0.005) {
						ParticlePositionData[i * 7 + 3] = 0.0f;
						ParticlePositionData[i * 7 + 4] = 0.0f;
						ParticlePositionData[i * 7 + 5] = 1.0f;
					}
					else if (curr_x > -0.006 && curr_x < 0.006) {
						ParticlePositionData[i * 7 + 3] = 23.0 / 255.0;
						ParticlePositionData[i * 7 + 4] = 37.0 / 255.0;
						ParticlePositionData[i * 7 + 5] = 76.0 / 255;
					}
					else if (curr_x > -0.01 && curr_x < 0.01) {
						ParticlePositionData[i * 7 + 3] = 17.0 / 255.0;
						ParticlePositionData[i * 7 + 4] = 103.0 / 255.0;
						ParticlePositionData[i * 7 + 5] = 177.0 / 255.0;
					}
					else if (curr_x > -0.02 && curr_x < 0.02) {
						ParticlePositionData[i * 7 + 3] = 42.0 / 255.0;
						ParticlePositionData[i * 7 + 4] = 157.0 / 255.0;
						ParticlePositionData[i * 7 + 5] = 244.0 / 255.0;
					}
					else {
						ParticlePositionData[i * 7 + 3] = 208.0 / 255.0;
						ParticlePositionData[i * 7 + 4] = 239.0 / 255.0;
						ParticlePositionData[i * 7 + 5] = 1.0f;
					}
				}
				
				// If it gets too high, turn to merge colors with the flame above it
				else {
					ParticlePositionData[i * 7 + 3] = 0.98f;
					ParticlePositionData[i * 7 + 4] = 0.75f;
					ParticlePositionData[i * 7 + 5] = 0.0f;
				}
			}

			// Standard orange flames
			else if (type == 1) {
				ParticlePositionData[i * 7 + 3] = 1.0f;
				ParticlePositionData[i * 7 + 4] = 0.5f;
				ParticlePositionData[i * 7 + 5] = 0.0f;
			}

			// Standard yellow flames that turn orange if they get too high
			else if (type == 2) {
				if (curr_y > -0.3) {
					ParticlePositionData[i * 7 + 3] = 1.0f;
					ParticlePositionData[i * 7 + 4] = 0.5f;
					ParticlePositionData[i * 7 + 5] = 0.0f;
				}
				else {
					ParticlePositionData[i * 7 + 3] = 0.98f;
					ParticlePositionData[i * 7 + 4] = 0.75f;
					ParticlePositionData[i * 7 + 5] = 0.0f;
				}
			}

			// For testing, not part of fire system, just red particles
			else if (type == 3) {
				ParticlePositionData[i * 7 + 3] = 1.0f;
				ParticlePositionData[i * 7 + 4] = 0.0f;
				ParticlePositionData[i * 7 + 5] = 0.0f;
			}

			// sets the alpha
			ParticlePositionData[i * 7 + 6] = alpha;
		}
	}

	// Used to set new data to replace the existing buffer data
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlePositionData.size() * sizeof(GLfloat), ParticlePositionData.data());
}

glm::vec3 ParticleSystem::random() {
	double lower = -0.02;
	double upper = 0.02;
	double range = upper - lower;
	double rand_x = lower + (range * ((double)rand()) / (RAND_MAX));
	double rand_y = lower + (range * ((double)rand()) / (RAND_MAX));
	return glm::vec3(rand_x, rand_y, 0);
}