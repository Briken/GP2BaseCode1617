#include "MyGame.h"


const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	Vertex verts[] = {
		{vec3 (-0.5f, -0.5f, 0.0f),	vec4(1.0f,1.0f,1.0f,1.0f),	vec2(0.0f,3.0f)},
		{vec3(0.5f, -0.5f, 0.0f),	vec4(1.0f,1.0f,1.0f,1.0f),	vec2(3.0f,3.0f)},
		{vec3(-0.5f,  0.5f, 0.0f),	vec4(1.0f,1.0f,1.0f,1.0f),	vec2(0.0f,0.0f)},
		{vec3(-0.5f, 0.5f, 0.0f),	vec4(1.0f,1.0f,1.0f,1.0f),	vec2(0.0f,0.0f)},
		{vec3(0.5f, 0.5f, 0.0f),	vec4(1.0f,1.0f,1.0f,1.0f),	vec2(3.0f,0.0f)},
		{vec3(0.5f,  -0.5f, 0.0f),	vec4(1.0f,1.0f,1.0f,1.0f),	vec2(3.0f,3.0f)}
	};

	m_TestObject = new GameObject();
	string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	m_TestObject->LoadShaders(vsPath, fsPath);
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	m_TestObject->LoadTexture(texturePath);
	m_TestObject->CopyVertexData(verts, 6);
	
	
	m_NewObject = new GameObject();
	vec3 tempPos = m_TestObject->GetPos();
	m_NewObject->SetPos(tempPos);
	m_NewObject->LoadShaders(vsPath, fsPath);
	texturePath = ASSET_PATH + TEXTURE_PATH + "/texture1.png";
	m_NewObject->LoadTexture(texturePath);
	m_NewObject->CopyVertexData(verts, 6);
	
}

void MyGame::destroyScene()
{
	m_TestObject->OnDestroy();
	m_NewObject->OnDestroy();
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_TestObject->OnUpdate();
	m_NewObject->OnUpdate();

	if (SDL_KEYDOWN == SDLK_LEFT)
	{ 
		m_TestObject->MoveLeft(5.0f);
	}
	if (SDL_KEYDOWN == SDLK_RIGHT)
	{
		m_TestObject->MoveRight(5.0f);
	}
}

void MyGame::render()
{
	GameApplication::render();
	m_TestObject->OnRender(m_ViewMatrix, m_ProjMatrix);
	m_NewObject->OnRender(m_ViewMatrix, m_ProjMatrix);
}
