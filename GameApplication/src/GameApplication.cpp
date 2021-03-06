#include "GameApplication.h"

GameApplication::GameApplication()
{
	CREATELOG("log.txt");
	m_WindowWidth = 640;
	m_WindowHeight = 480;
	m_WindowCreationFlags = SDL_WINDOW_OPENGL;
	m_WindowTitle = "Game";
	m_pWindow = nullptr;
	m_bIsRunning = false;
}

GameApplication::~GameApplication()
{
  CLOSELOG();
}

void GameApplication::parseConfig(int args,char * arg[])
{
  stringstream ss;
  //parse config file
  XMLOptionsParser xmlParser=XMLOptionsParser("settings.xml");
  xmlParser.parse(m_Options);
  ss<<m_Options;
  LOG(INFO,"Settings Parsed\n%s",ss.str().c_str());
  ss.str( std::string());
  ss.clear();
	//parse command line arguments into keyvalue pairs, this should
	//overide options in config files
  CommandLineParser commandLineParser=CommandLineParser(args,arg);
  commandLineParser.parse(m_Options);
  ss<<m_Options;
  LOG(INFO,"Command Line Parsed\n%s",ss.str().c_str());
  ss.str( std::string());
  ss.clear();
}


bool GameApplication::init(int args,char * arg[])
{
	parseConfig(args,arg);

	//init everything - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG(ERROR, "SDL can't be initialised %s", SDL_GetError());
		return false;
	}

	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);

	if (((returnInitFlags) & (imageInitFlags)) != imageInitFlags)
	{
		LOG(ERROR, "SDL_Image Init %s", IMG_GetError());
	}

	m_WindowWidth = m_Options.getOptionAsInt("WindowWidth");
	m_WindowHeight = m_Options.getOptionAsInt("WindowHeight");
	m_WindowTitle = m_Options.getOption("WindowTitle");
	createWindow(m_WindowTitle, m_WindowWidth, m_WindowHeight,  m_WindowCreationFlags);

	InitGraphics();
	InitScene();
	m_bIsRunning = true;
	
	return true;
}

void GameApplication::createWindow(const string& windowTitle,
	const unsigned int width, const unsigned int height,
	const unsigned int windowFlags)
{
	m_pWindow = SDL_CreateWindow(windowTitle.c_str(), 50, 50, width, height, windowFlags);

	
}

void GameApplication::run()
{
	//Value to hold the event generated by SDL
	SDL_Event event;
	//Game Loop
	while (m_bIsRunning)
	{
		//While we still have events in the queue
		while (SDL_PollEvent(&event))
		{
			//Get event type
			if (event.type == SDL_QUIT)
			{
				OnQuit();
			}
		}
		Update();
		OnBeginRender();
		Render();
		OnEndRender();
	}
}

void GameApplication::OnBeginRender()
{
	// Set the clear colour(background)

	glClearColor(0.5f, 0.0f, 0.5f, 0.0f);

	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GameApplication::Update()
{}

void GameApplication::InitGraphics()

	{

		//OpenGl Context

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,

			SDL_GL_CONTEXT_PROFILE_CORE);


		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		m_GLcontext = SDL_GL_CreateContext(m_pWindow);



		//GLEW

		glewExperimental = GL_TRUE;


		GLenum err = glewInit();


		if (GLEW_OK != err) {

			LOG(ERROR, "Error: %s", glewGetErrorString(err));

		}



		//OpenGL States

		//Smooth shading

		glShadeModel(GL_SMOOTH);



		//clear the background to black

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);



		//Clear the depth buffer to 1.0

		glClearDepth(1.0f);



		//Enable depth testing

		glEnable(GL_DEPTH_TEST);



		//The depth test to use

		glDepthFunc(GL_LEQUAL);



		//Turn on best perspective correction

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


		//Set our viewport
		setViewport((int)m_WindowWidth, (int)m_WindowHeight);


	}

void GameApplication::setViewport(int width, int height)
{

	//screen ration

	GLfloat ratio;


	//make sure height is always above 1

	if (height == 0) {

		height = 1;

	}


	//calculate screen ration

	ratio = (GLfloat)width / (GLfloat)height;


	//Setup viewport

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void GameApplication::InitScene()
{
}

void GameApplication::DestroyScene()
{
}


void GameApplication::Render()
{

	

}

void GameApplication::OnEndRender()
{
	SDL_GL_SwapWindow(m_pWindow);
}


void GameApplication::OnQuit()
{
	m_bIsRunning = false;
	DestroyScene();
	SDL_GL_DeleteContext(m_GLcontext);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}
