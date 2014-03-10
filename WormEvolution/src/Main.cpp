#include <ctime>
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Simulation.h"
#include "Renderer.h"

void render();
void update();

Simulation* helloWorld;
Renderer* render_engine;

int width, height;

int main(){
	const int population_size = 10;
	const int max_generations = 10;
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
		std::cout << "Generation : " << i << std::endl;
		std::cout << "Best fitness : " << best.GetFitness() << std::endl;
	}

	std::cout << "Generation " << i << ": "<< best << std::endl;

	std::cout << "Total time: " << double( (std::clock() - start_time) / CLOCKS_PER_SEC ) << 
			" s" << std::endl;






	// Create the main SFML window
	sf::RenderWindow app_window( sf::VideoMode( 800, 600 ), "SFGUI Canvas Example", sf::Style::Titlebar | sf::Style::Close );

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

		//update(); 
		helloWorld->Step(1/60.0f);
		//render();

		///////


		//transforms
		glEnable( GL_DEPTH_TEST );
		glDepthMask( GL_TRUE );
		glDisable( GL_TEXTURE_2D );
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		
		glScalef(0.1,0.1,0.1);
		glRotatef(90.0, 0.0, 1.0, 0.0);

		glBegin(GL_LINES);
		    glColor3f(1, 0, 0);
		    glVertex3d(0, 0, 0);
		    glVertex3d(1, 1, 0);
		glEnd();


		glViewport( 0, 0, static_cast<int>( opengl_canvas->GetAllocation().width ), static_cast<int>( opengl_canvas->GetAllocation().height ) );	

		render_engine->render();

		glViewport( 0, 0, app_window.getSize().x, app_window.getSize().y );

		glEnable( GL_TEXTURE_2D );
		glDisable( GL_DEPTH_TEST );

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