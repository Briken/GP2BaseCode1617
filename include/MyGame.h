#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void InitScene();
	void DestroyScene();
	void Render();
	void Update();

private:
	GLuint m_VBO;
	GLuint m_VAO;
};
#endif
