#include <SFML/Graphics.hpp>
#include <btBulletDynamicsCommon.h>

// Always include the necessary header files.
// Including SFGUI/SFGUI.hpp includes everything
// you can possibly need automatically.
#include <SFGUI/SFGUI.hpp>

int main() {
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

	auto text_window = sfg::Window::Create();
	text_window->SetTitle( "Label window" );
	text_window->SetPosition( sf::Vector2f( 300.f, 100.f ) );

	std::string bulletHelloWorld = "";
	auto text_label = sfg::Label::Create();

	// Create the Canvases.
	// Passing true in to Create() tells SFGUI
	// to create a depth buffer for the canvas.
	// This might be needed for your OpenGL rendering.
	// Specifying nothing defaults to no depth buffer.
	auto opengl_canvas = sfg::Canvas::Create( true );

	// Add the Canvases to the windows.
	opengl_window->Add( opengl_canvas );
	text_window->Add( text_label );

	// Because Canvases provide a virtual surface to draw
	// on much like a ScrolledWindow, specifying their
	// minimum requisition is necessary.
	opengl_canvas->SetRequisition( sf::Vector2f( 200.f, 150.f ) );

	// Create a desktop to contain our Windows.
	sfg::Desktop desktop;
	desktop.Add( opengl_window );
	desktop.Add( text_window );

	sf::Clock clock;


	// -------------BULLET TEST

	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0,-10,0));


    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);

    btCollisionShape* fallShape = new btSphereShape(1);


    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);


    btDefaultMotionState* fallMotionState =
            new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
    btScalar mass = 1;
    btVector3 fallInertia(0,0,0);
    fallShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(fallRigidBody);

    // -------------------------------




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

		dynamicsWorld->stepSimulation(1/600.f,1000);

        btTransform trans;
        fallRigidBody->getMotionState()->getWorldTransform(trans);
        std::ostringstream ss;

        ss << trans.getOrigin().getY();

        text_label->SetText(ss.str());

		// Update the GUI, note that you shouldn't normally
		// pass 0 seconds to the update method.
		desktop.Update( 0.f );

		// Clear screen
		app_window.clear();

		// We bind the Canvases and draw whatever we want to them.
		// This must occur BEFORE the GUI is displayed.
		// You must not forget to set whatever context was active
		// before to active again after you unbind a Canvas.
		// Clear() takes an RGBA color and a bool which specifies
		// if you want to clear the depth buffer as well. In this
		// case, we do.

		// First the Canvas for OpenGL rendering.
		opengl_canvas->Bind();
		opengl_canvas->Clear( sf::Color( 0, 0, 0, 0 ), true );

		// Do some OpenGL drawing. If you don't intend
		// on drawing with OpenGL just ignore this section.
		glEnable( GL_DEPTH_TEST );
		glDepthMask( GL_TRUE );
		glDisable( GL_TEXTURE_2D );

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glLoadIdentity();

		glTranslatef( 0.f, 0.f, -2.f );

		glRotatef( clock.getElapsedTime().asSeconds() * 30.f, 0.f, 0.f, 1.f );

		glDisable( GL_TEXTURE_2D );

		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity();

		glViewport( 0, 0, static_cast<int>( opengl_canvas->GetAllocation().width ), static_cast<int>( opengl_canvas->GetAllocation().height ) );

		gluPerspective( 90.f, opengl_canvas->GetAllocation().width / opengl_canvas->GetAllocation().height, 1.f, 20.f );

		glBegin( GL_QUADS );
		glVertex2s( -1, 1 );
		glVertex2s( -1, -1 );
		glVertex2s( 1, -1 );
		glVertex2s( 1, 1 );
		glEnd();

		glPopMatrix();
		glMatrixMode( GL_MODELVIEW );
		glPopMatrix();

		glViewport( 0, 0, app_window.getSize().x, app_window.getSize().y );

		glEnable( GL_TEXTURE_2D );
		glDisable( GL_DEPTH_TEST );

		opengl_canvas->Display();
		opengl_canvas->Unbind();


		app_window.setActive( true );

		// Draw the GUI
		sfgui.Display( app_window );

		// Update the window
		app_window.display();
	}

	dynamicsWorld->removeRigidBody(fallRigidBody);
    delete fallRigidBody->getMotionState();
    delete fallRigidBody;

    dynamicsWorld->removeRigidBody(groundRigidBody);
    delete groundRigidBody->getMotionState();
    delete groundRigidBody;


    delete fallShape;

    delete groundShape;


    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;

	return EXIT_SUCCESS;
}
