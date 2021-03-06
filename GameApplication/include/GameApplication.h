#ifndef _GAMEAPPLICATION_H
#define _GAMEAPPLICATION_H

#include "Common.h"
#include "Shader.h"
#include "Texture.h"

//Game Application class, this basically wraps up the initialisation of a game
//this will be the base class of any game we are making. You should override this
//and some of the methods to create your own game
class GameApplication:public NonCopyable
{
public:
	//Constructor
	GameApplication();
	
	//Window Creation
	void createWindow(const string& windowTitle,
		const unsigned int width, const unsigned int height,
		const unsigned int windowFlags = 0);
	
	//Virtual Deconstructor
	virtual ~GameApplication();

	//This is where all major subsystems are created
	virtual bool init(int args,char * arg[]);

	//Basically runs our game
	void run();

	//Controls quitting the game
	void OnQuit();

	void OnBeginRender();

	void OnEndRender();

	virtual void Render();

	virtual void Update();

	void InitGraphics();

	void setViewport(int width, int height);

	virtual void InitScene();

	virtual void DestroyScene();



protected:
	ProgramOptions m_Options;

	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	unsigned int m_WindowCreationFlags;
	string m_WindowTitle;

	SDL_GLContext m_GLcontext;


	bool m_bIsRunning;

	SDL_Window * m_pWindow;

	void parseConfig(int args,char * arg[]);
};
#endif
