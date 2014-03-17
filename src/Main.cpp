
// 🐢
#include <ctime>
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Simulation.h"
#include "Renderer.h"
#include <shader.hpp>

Simulation* helloWorld;
Renderer* render_engine;

int width, height;

int main(){

	const int population_size = 20;
	const int max_generations = 2;

	const float crossover_ratio = 0.8f;
	const float elitism_ratio = 0.2f;
	const float mutation_ratio = 0.8f;

	std::clock_t start_time;
	start_time = std::clock();

	Evolution ev(crossover_ratio, elitism_ratio, mutation_ratio);

	// creates the population!
	std::vector<Creature> population;
	population.resize(population_size);

	for (int i=0; i<population_size; ++i){
		population[i] = Creature(Chromosome::random());//Creature::random();
	}

	// sortera Creature
	std::sort(population.begin(), population.end(), CreatureLargerThan());

	int i=0;
	Creature best = population[0]; // den bästa tas fram

	while( (++i < max_generations) && (best.GetFitness() < 30) ) {

		population = ev.nextGeneration(population);

		std::sort(population.begin(), population.end(), CreatureLargerThan());
		best = population[0];

		//std:: cout << "Generation " << i << ": " << best << std::endl;
		// Trying some other mating and mutating with nextGenerationMixedMating.
		std::cout << "🐛" << "Generation : " << i << std::endl;
		std::cout << "Best fitness : " << best.GetFitness() << std::endl;
	}

	std::cout << "Generation " << i << ": "<< best << std::endl;

	std::cout << "Total time: " << double( (std::clock() - start_time) / CLOCKS_PER_SEC ) << 
			" s" << std::endl;

	//The while true loop is so that the rendering can be re-done if
	//it does not draw
	//while (true) {
	//initalize simulation
	//helloWorld = new Simulation(best.GetChromosome().GetGene());
	WormBulletCreature *worm = new WormBulletCreature(best.GetChromosome().GetGene(), btVector3(0,0,0));
	helloWorld = new Simulation(); 
	helloWorld->AddCreatureToWorld(worm);
   


    //The rendering stuff
	GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    // We want the newest version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
	/* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
    // Print current OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    glPointSize(10.0f);
    // Create and compile the shader
    GLuint programID = LoadShaders( "../../data/shaders/simple.vert", "../../data/shaders/simple.frag" );

	//initialize debugDrawer for simulation (Needs to be done when context created)
	render_engine = new Renderer(helloWorld, true);
    
    while (!glfwWindowShouldClose(window))
    {
		helloWorld->Step(1/60.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);
		render_engine->render();
        glUseProgram(0);
		/* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

	}


	helloWorld->RemoveCreatureFromWorld(worm);
	delete worm; 

	delete helloWorld;
	delete render_engine;

	glfwTerminate();

	return 0;
}