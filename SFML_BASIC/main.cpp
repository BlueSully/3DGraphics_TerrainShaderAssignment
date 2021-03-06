//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 

#include <iostream> 
  
#include "Terrain.h"
#include "Camera.h"

int main() 
{ 
    // Create the main window 
    int width = 600, height = 600;
	sf::ContextSettings Settings;
	Settings.depthBits = 24;			// Request a 24 bits depth buffer
	Settings.stencilBits = 8;			// Request a 8 bits stencil buffer
	Settings.antialiasingLevel = 16;	// Request 2 levels of antialiasing
	sf::RenderWindow App(sf::VideoMode(width, height, 32), "Terrain Assignment", sf::Style::Close, Settings);
    // Create a clock for measuring time elapsed     
    sf::Clock Clock; 

	aiVector3D position(0, 10, -30);

	Camera camera;
    camera.Init(position); //create a camera

	bool PERSPECTIVE = true;
	bool ORTHOGONAL = false;
	bool WIREFRAME = false;
	bool keypress = false;
	//prepare OpenGL surface for HSR 
	glClearDepth(1.f);
	glClearColor(0.3f, 0.3f, 0.6f, 0.f); //background colour

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// Setup a perspective projection & Camera position 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	//Create our Terrain
	Terrain terrain;
	terrain.Init("heightmap.bmp");

	//load & bind the shader
	sf::Shader shader;
	//all the lighting & texture blending code should  be put in 'fragment.glsl'
	if(!shader.loadFromFile("vertex.glsl", "fragment.glsl")){
		std::cout << "Could not load Shaders";
	}

	sf::Texture waterTexture;
	if (!waterTexture.loadFromFile("water_2.png"))
	{
		std::cout << "Could not load water image";
	}

	sf::Texture grassTexture;
	if (!grassTexture.loadFromFile("Grass_1.png"))
	{
		std::cout << "Could not load grass image";
	}
	sf::Texture rockTexture;
	if (!rockTexture.loadFromFile("Rock_1.png"))
	{
		std::cout << "Could not load snow image";
	}
	sf::Texture snowTexture;
	if (!snowTexture.loadFromFile("snow_2.png"))
	{
		std::cout << "Could not load snow image";
	}

	shader.setParameter("waterTex", waterTexture);
	shader.setParameter("grassTex", grassTexture);
	shader.setParameter("rockTex", rockTexture);
	shader.setParameter("snowTex", snowTexture);
	shader.setParameter("tallestPoint", terrain.heightestPoint);

	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat materialShininess[] = { 78.0f }; // select value between 0-128, 128=shiniest
	GLfloat light_position[] = { 10, 20, 50, 1.0 };

	// Start game loop 
	while (App.isOpen()) 
	{ 
		// Process events 
		sf::Event Event; 
		while (App.pollEvent(Event)) 
		{ 
			// Close window : exit 
			if (Event.type == sf::Event::Closed) 
				App.close(); 

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
				App.close(); 

			//update the camera
			camera.Update(Event);
		} 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			ORTHOGONAL = true;
			PERSPECTIVE = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			ORTHOGONAL = false;
			PERSPECTIVE = true;
		}
		//set up a 3D Perspective View volume
		if (PERSPECTIVE){
			gluPerspective(90.f, (float)(width / height), 0.01f, 300.0f);//fov, aspect, zNear, zFar 
		}
		else if (ORTHOGONAL)
		{
			glOrtho(-30, 30, -30, 30, 0.001f, 3000.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && keypress == false)
		{
			if (WIREFRAME)
			{
				WIREFRAME = false;
			}
			else if (!WIREFRAME)
			{
				WIREFRAME = true;
			}
			keypress = true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			keypress = false;
		}
		//Prepare for drawing 
		// Clear color and depth buffer 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sf::Shader::bind(&shader);
		glEnable(GL_NORMALIZE);

		//Lighting
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);//creating light
		glMaterialfv(GL_FRONT, GL_AMBIENT, light_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, light_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess); // set shininess of the material


		glLightfv(GL_LIGHT0, GL_POSITION, light_position);// Set the light position
		
		// Apply some transformations 
		//initialise the worldview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//get the viewing transform from the camera
		camera.ViewingTransform();

		glColor3f(0.2, 0.5, 0.8);
		//static float ang = 0.0;
		//ang += 0.08f;
		//glRotatef(ang*2, 0, 1, 0);//spin about y-axis	
		
		//draw the world
		terrain.Draw(WIREFRAME);

		// Finally, display rendered frame on screen 
		App.display(); 
	} 

	return EXIT_SUCCESS; 
}
