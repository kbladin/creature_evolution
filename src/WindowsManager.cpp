#include "WindowsManager.h"

//! Constructor
WindowsManager::WindowsManager(int window_width, int window_height,
		CreatureEvolution* ce) {

	ce_ = ce;

	if(!glfwInit()) {
		std::cout << "GLFW FAIL" << std::endl;
	}

	// We want the newest version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
    glfw_window_ = glfwCreateWindow(window_width, window_height,
    	 "Creature Evolution", NULL, NULL);
    if (!glfw_window_)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(glfw_window_);
    
    GLEWInit();

    // Print current OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


	std::cout << "Created WindowsManager." << std::endl;

}

//! Destructor
WindowsManager::~WindowsManager(void) {
	glfwTerminate();
}

void WindowsManager::GLEWInit() {
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");

	}
}

void WindowsManager::DisplayAndRender() {

	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
	ce_->InitWorld();

	while(!glfwWindowShouldClose(glfw_window_)) {
		ce_->StepTheWorld();
		ce_->UpdateTheWorld();
		ce_->RenderTheWorld();

		glfwSwapBuffers(glfw_window_);
		glfwPollEvents();
	}

}


void WindowsManager::setVariables(){
	// just for know, read in from user-input from console.
	// no check for wrong input!

	int max_generations, population_size;
	float crossover, elitism, mutation;

	std::cout << "Inside WindowManager, get input and send to SettingsManager" << std::endl;

	std::cout << "Max generations: " ;
	std::cin >> max_generations; 
	std::cout << "Population size: " ;
	std::cin >> population_size; 
	std::cout << "Crossover ratio (0.0-1.0): " ;
	std::cin >> crossover; 
	std::cout << "Elitism ratio (0.0-1.0): " ;
	std::cin >> elitism; 
	std::cout << "Mutation ratio (0.0-1.0): " ;
	std::cin >> mutation;

	SettingsManager::Instance()->setMaxGenerations(max_generations);
	SettingsManager::Instance()->setPopulationSize(population_size);
	SettingsManager::Instance()->setCrossover(crossover);
	SettingsManager::Instance()->setElitism(elitism);
	SettingsManager::Instance()->setMutation(mutation);
}


