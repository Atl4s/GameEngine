#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "Game.h"
#include "StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
	if (!m_bStateIsOver) {
		handleEvents();

		int i = 0;
		while (i < v_pGameObjects.size())
		{
			v_pGameObjects[i]->update();
			++i;
		}

		i = 0;
		while (i < v_pParticles.size())
		{
			if (v_pParticles[i]->isDead()) {
				delete v_pParticles[i];
				v_pParticles.erase(v_pParticles.begin() + i);
				glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
				//v_pParticles[i] = new Particle(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 1000, color);
			}
			else {
				v_pParticles[i]->update();
			}
			i++;
		}

		Camera2D::Instance()->update();
	}
	
}

void MainMenuState::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = m_colorProgram.getUniformLocation("m_sampler");
	glUniform1i(textureLocation, 0);

	GLuint pLocation = m_colorProgram.getUniformLocation("P");
	glm::mat4 camMatrix = Camera2D::Instance()->getCamMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(camMatrix[0][0]));

	m_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 200.0f, 200.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);

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

	glBindTexture(GL_TEXTURE_2D, 0);

	m_colorProgram.unuse();

	Game::Instance()->getWindow()->swapBuffer();
}

bool MainMenuState::onEnter()
{
	std::cout << s_menuID << std::endl;

	StateParser stateParser;
	stateParser.parseState("../assets/test.xml", s_menuID, &v_pGameObjects);
	m_callbacks.push_back(0);
	m_callbacks.push_back([](){ Game::Instance()->getStateMachine()->changeState(new PlayState()); });//from menu to play
	m_callbacks.push_back([](){ Game::Instance()->clean(); });//exit
	setCallbacks(m_callbacks);

	glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);

	Camera2D::Instance()->init(640, 480);
	initShaders();
	m_spriteBatch.init();
	Camera2D::Instance()->update();

	m_bStateIsOver = false;

	return true;
}

bool MainMenuState::onExit()
{
	std::cout << "onExit" << v_pGameObjects.size() << std::endl;

	for (int i = 0; i < v_pGameObjects.size(); i++) delete v_pGameObjects[i];

	v_pGameObjects.clear();

	for (int i = 0; i < v_pParticles.size(); i++) delete v_pParticles[i];

	v_pParticles.clear();

	m_bStateIsOver = true;

	Camera2D::Instance()->reset();
	Camera2D::Instance()->update();

	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < v_pGameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(v_pGameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(v_pGameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void MainMenuState::initShaders()
{
	m_colorProgram.compileShaders("../Shaders/colorShader.vert", "../Shaders/colorShader.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertexUV");
	m_colorProgram.linkShaders();
}

void MainMenuState::handleEvents()
{
	InputHandler::Instance()->update();
	if (InputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		glm::vec2 playerPosition(0.0f);

		glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
		v_pParticles.push_back(new Particle(glm::vec2(-320.0f, 240.0f), glm::vec2(0.0f), glm::vec2(0.0f), 1000, color));
		v_pParticles.push_back(new Particle(glm::vec2(320.0f, 240.0f), glm::vec2(0.0f), glm::vec2(0.0f), 1000, color));
		v_pParticles.push_back(new Particle(glm::vec2(320.0f, -240.0f), glm::vec2(0.0f), glm::vec2(0.0f), 1000, color));
		v_pParticles.push_back(new Particle(glm::vec2(-320.0f, -240.0f), glm::vec2(0.0f), glm::vec2(0.0f), 1000, color));
	}
	if (InputHandler::Instance()->getMouseButtonState(LEFT))
	{
		glm::vec2 mouseCoords = InputHandler::Instance()->getMousePosition();
		mouseCoords = Camera2D::Instance()->convertScreenToWorld(mouseCoords);

		glm::vec2 playerPosition(0.0f);
		glm::vec2 velocity = mouseCoords - playerPosition;
		velocity = glm::normalize(velocity);

		glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
		v_pParticles.push_back(new Particle(mouseCoords, velocity, glm::vec2(0.0f, 0.0f), 1000, color));

	}
	if (InputHandler::Instance()->getMouseButtonState(MIDDLE))
	{
		
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
	{
		
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
	{
		
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
	{
		
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
	{
		
	}
}