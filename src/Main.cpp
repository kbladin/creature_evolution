
// 🐢
#include "SettingsManager.h"
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Simulation.h"
#include "Renderer.h"
#include "WindowsManager.h"
#include "EvolutionManager.h"


void render();
void update();

Simulation* helloWorld;
Renderer* render_engine;


int width, height;

int main(){

	WindowsManager wm; // = new WindowsManager();
	wm.setVariables(); // get info from window, write to settingsmanager

	EvolutionManager em;// = new EvolutionManager();
	std::cout << "Started the simulation process..." << std::endl;
	em.startEvolutionProcess(); // start the whole evolution process! 
	em.printBestFitnessValues();

	//Creature best = em.getBestCreatureFromLastGeneration(); // get the best generation

	int generation; 
	std::cout << "Which generation would you like to show? ";
	std::cin >> generation; 

	Creature best = em.getBestCreatureFromGeneration(generation);

    sf::ContextSettings settings(24,8,4,3,3);
    
    /*settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 1;*/
    
    

	// Create the main SFML window
	sf::RenderWindow app_window( sf::VideoMode( 800, 600 ), "SFGUI Canvas Example", sf::Style::Titlebar | sf::Style::Close, settings );
    
	// We have to do this because we don't use SFML to draw.
	app_window.resetGLStates();

	// Create an SFGUI. This is required before doing anything with SFGUI.
	sfg::SFGUI sfgui;

	// Create our OpenGL canvas window
	auto opengl_window = sfg::Window::Create();
	opengl_window->SetTitle( "OpenGL canvas" );
	opengl_window->SetPosition( sf::Vector2f( 100.f, 100.f ) );

	auto opengl_canvas = sfg::Canvas::Create( true );
	opengl_window->Add( opengl_canvas );
	opengl_canvas->SetRequisition( sf::Vector2f( 200.f, 150.f ) );


	//The while true loop is so that the rendering can be re-done if
	//it does not draw
	//while (true) {
		//initalize simulation
		//helloWorld = new Simulation(best.GetChromosome().GetGene());
		WormBulletCreature *worm = new WormBulletCreature(best.GetChromosome().GetGene(), btVector3(0,0,0));
		helloWorld = new Simulation(); 
		helloWorld->AddCreatureToWorld(worm);

		//initialize debugDrawer for simulation
		render_engine = new Renderer(helloWorld, true);

	// Create a desktop to contain our Windows.
	sfg::Desktop desktop;
	desktop.Add( opengl_window );

	sf::Clock clock;

	// Initialize GLEW
    
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
    

	// Start the game loop
	while ( app_window.isOpen() ) {
		// Process events
		sf::Event event;

		while ( app_window.pollEvent( event ) ) {
			// Handle events
			desktop.HandleEvent( event );

			// Close window : exit
			if ( event.type == sf::Event::Closed ) {
				app_window.close();
			}
		}

		// Update the GUI, note that you shouldn't normally
		// pass 0 seconds to the update method.
		desktop.Update( 0.f );
		// Clear screen
		app_window.clear();

		// First the Canvas for OpenGL rendering.
		opengl_canvas->Bind();
		opengl_canvas->Clear( sf::Color( 0, 0, 0, 0 ), true );

		helloWorld->Step(1/60.0f);

		//transforms
		/*glEnable( GL_DEPTH_TEST );
		glDepthMask( GL_TRUE );
		glDisable( GL_TEXTURE_2D );*/
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		
		//glScalef(0.1,0.1,0.1);

		glViewport( 0, 0, static_cast<int>( opengl_canvas->GetAllocation().width ), static_cast<int>( opengl_canvas->GetAllocation().height ) );	

        //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glColor3f(1, 0, 1);
        glBegin(GL_LINES);
        glVertex2d(0, 0);
        glVertex2d(1, 1);
        glEnd();
        
		render_engine->render();

		glViewport( 0, 0, app_window.getSize().x, app_window.getSize().y );

		//glEnable( GL_TEXTURE_2D );
		//glDisable( GL_DEPTH_TEST );

		///////

		opengl_canvas->Display();
		opengl_canvas->Unbind();

		app_window.setActive( true );

		// Draw the GUI
		sfgui.Display( app_window );

		// Update the window
		app_window.display();

	}


	helloWorld->RemoveCreatureFromWorld(worm);
	delete worm; 

	delete helloWorld;
	delete render_engine;

	exit(EXIT_SUCCESS);

	return 0;
}


void render() {

}

void update() {
	//helloWorld->step();
}