#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Template/Window.h"
#include "../Template/Shader.h"
#include "ParticleSystem.h"

#include<chrono>
#include<dos.h>
#include<thread>

Window window;
Shader shader;


int main() {
	window = Window(1920, 1080);
	window.Initialise();
	
	shader.CreateFromFiles("../Template/Shaders/Basic2DShader.vert", "../Template/Shaders/Basic2DShader.frag");
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_POINTS);
	//glEnable(GL_PROGRAM_POINT_SIZE);

	glPointSize(5);
	ParticleSystem* ps = new ParticleSystem(glm::vec3(0.0, -1.6, 0.0));
	ParticleSystem* ps2 = new ParticleSystem(glm::vec3(0.0, -1.0, 0.0));
	ParticleSystem* ps3 = new ParticleSystem(glm::vec3(0.025, -0.9, 0.0));
	ParticleSystem* ps4 = new ParticleSystem(glm::vec3(-0.025, -0.9, 0.0));
	ParticleSystem* ps5 = new ParticleSystem(glm::vec3(0.04, -1.1, 0.0));
	ParticleSystem* ps6 = new ParticleSystem(glm::vec3(-0.04, -1.1, 0.0));

	ps->CreateParticles(5000);
	ps2->CreateParticles(5000);
	ps3->CreateParticles(5000);
	ps4->CreateParticles(5000);
	ps5->CreateParticles(5000);
	ps6->CreateParticles(5000);

	
	while (window.GetWindowShouldClose() == false) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		shader.UseShader(); 
		shader.setUniform1F("time", glfwGetTime());

		ps->Render();
	    ps2->Render();
		ps3->Render();
		ps4->Render();
		ps5->Render();
		ps6->Render();

		if (glfwGetTime() > 1) {
			ps->Update(0);
			ps2->Update(2);
			ps3->Update(1);
			ps4->Update(1);
			ps5->Update(1);
			ps6->Update(1);
		}



		window.SwapBuffers();
	}
}