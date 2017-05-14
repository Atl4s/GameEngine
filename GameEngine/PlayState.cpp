#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Game.h"
#include "StateParser.h"
#include <Camera3D.h>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (!m_bStateIsOver) {
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) Game::Instance()->getStateMachine()->pushState(new PauseState());

		for (int i = 0; i< v_pGameObjects.size(); i++)
		{
			v_pGameObjects[i]->update();
		}
		
		for (int i = 0; i< m_pObjects.size(); i++)
		{
			m_pObjects[i]->update();
		}

		//if (checkCollision(dynamic_cast<SDLGameObject*>(v_pGameObjects[0]), dynamic_cast<SDLGameObject*>(v_pGameObjects[1]))) Game::Instance()->getStateMachine()->changeState(new GameOverState());

		Camera3D::Instance()->update();
	}
	//SDL_WarpMouseInWindow(Game::Instance()->getWindow()->getWindow(), 320, 240);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void PlayState::render()
{
	static float angle = 0.0f;

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	m_colorProgram.use();

	GLint textureLocation = m_colorProgram.getUniformLocation("m_texture");
	glUniform1i(textureLocation, 0);

	textureLocation = m_colorProgram.getUniformLocation("m_normalMap");
	glUniform1i(textureLocation, 1);

	GLuint mvpLocation = m_colorProgram.getUniformLocation("MVP");
	glm::mat4 camMatrix = Camera3D::Instance()->getMVP();
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(camMatrix[0][0]));

	GLuint mLocation = m_colorProgram.getUniformLocation("M");
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(mLocation, 1, GL_FALSE, &(modelMatrix[0][0]));

	GLuint camLocation = m_colorProgram.getUniformLocation("camPosition");
	glm::vec3 camDirection = Camera3D::Instance()->getCamPosition();
	glUniform3fv(camLocation, 1, &(camDirection[0]));

	for (int i = 0; i < m_pLights.size(); i++)
	{
		m_pLights[i]->setUniform(m_colorProgram, "light", i);
	}


	angle += 0.01;
	   
	m_spriteBatch.begin();
	
	for (int i = 0; i < v_pParticles.size(); i++)
	{
		v_pParticles[i]->draw(m_spriteBatch);
	}

	for (int i = 0; i < v_pGameObjects.size(); i++)
	{
		v_pGameObjects[i]->draw(m_spriteBatch);
	}

	m_spriteBatch.end();

	m_spriteBatch.renderBatch();

	for (int i = 0; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->render();
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	m_colorProgram.unuse();
	
	Game::Instance()->getWindow()->swapBuffer();
	
}

bool PlayState::onEnter()
{
	Camera3D::Instance()->setSpeed(5.3f);

	std::cout << s_playID << std::endl;

	//StateParser stateParser;
	//stateParser.parseState("../assets/test.xml", s_playID, &v_pGameObjects);

	

	m_bStateIsOver = false;

	initShaders();
	m_spriteBatch.init();

	for (int i = 0; i < 1; i++)
	{
		m_pLights.push_back(new LightSource(0, 30000.0f,
			glm::vec3(100.0f, 0.0f, 100.0f),
			glm::vec3(1), glm::vec4(1)));
	}
	for (int i = 0; i < 1; i++)
	{
		m_pObjects.push_back(new Object);
		m_pObjects.back()->createVertexArray();
		m_pObjects.back()->loadOBJ("../assets/Lilith.obj");
	}
	
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exit from Play" << v_pGameObjects.size() << std::endl;

	for (int i = 0; i < v_pGameObjects.size(); i++) delete v_pGameObjects[i];

	v_pGameObjects.clear();

	m_bStateIsOver = true;

	Camera2D::Instance()->reset();


	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int left_p1 = p1->getPosition().x;
	int right_p1 = p1->getPosition().x + p1->getWidth();
	int top_p1 = p1->getPosition().y;
	int bottom_p1 = p1->getPosition().y + p1->getHeight();

	int left_p2 = p2->getPosition().x;
	int right_p2 = p2->getPosition().x + p2->getWidth();
	int top_p2 = p2->getPosition().y;
	int bottom_p2 = p2->getPosition().y + p2->getHeight();

	if ((bottom_p1 > top_p2 && top_p1 < bottom_p2)
		&& (
		(left_p1 > left_p2 && left_p1 < right_p2) || (right_p1 > left_p2 && right_p1 < right_p2))
		   ) return true;
	if (bottom_p1 > top_p2 && top_p1 < bottom_p2 && left_p1 > left_p2 && right_p1 < right_p2) return true;

	if (bottom_p1 > top_p2 && top_p1 < bottom_p2 && left_p1 <= left_p2 && right_p1 >= right_p2) return true;
	
	return false;
}

void PlayState::initShaders()
{
	m_colorProgram.compileShaders("../Shaders/colorShaderTest.vert", "../Shaders/colorShaderTest.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertexUV");
	m_colorProgram.addAttribute("vertexNormal");
	m_colorProgram.linkShaders();
}