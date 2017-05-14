#include "PauseState.h"
#include "MenuButton.h"
#include "Game.h"
#include "StateParser.h"

const std::string PauseState::s_pauseID = "PAUSE";


void PauseState::s_pauseToMenu()
{
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	Game::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	int i = 0;
	while (i < v_pGameObjects.size() && !m_bStateIsOver)
	{
		v_pGameObjects[i]->update();
		++i;
	}
	i = 0;
	while (i < v_pParticles.size() && !m_bStateIsOver)
	{
		v_pParticles[i]->update();
		++i;
	}
	Camera2D::Instance()->update();
}

void PauseState::render()
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
	glm::vec4 color(255, 255, 255, 255);
	//m_spriteBatch.addGlyph(pos, uv, _texture.id, 0.0f, color);
	//m_spriteBatch.addGlyph(pos + glm::vec4(200.0f, 0.0f, -100.0f, -100.0f), uv + glm::vec4(0.0f, 0.0f, -0.5f, -0.5f), _texture.id, 0.0f, color);

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

bool PauseState::onEnter()
{
	SDL_SetRelativeMouseMode(SDL_FALSE);

	_cameraPosition = Camera2D::Instance()->getPosition();
	_cameraScale = Camera2D::Instance()->getScale();
	
	Camera2D::Instance()->reset();

	std::cout << s_pauseID << std::endl;

	StateParser stateParser;
	stateParser.parseState("../assets/test.xml", s_pauseID, &v_pGameObjects);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMenu);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	m_bStateIsOver = false;

	initShaders();
	m_spriteBatch.init();


	return true;
}

bool PauseState::onExit()
{
	std::cout << "onExit" << v_pGameObjects.size() << std::endl;

	for (int i = 0; i < v_pGameObjects.size(); i++) delete v_pGameObjects[i];

	v_pGameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
	ResourceManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	

	InputHandler::Instance()->clean();

	m_bStateIsOver = true;

	 Camera2D::Instance()->setPosition(_cameraPosition);
	 Camera2D::Instance()->setScale(_cameraScale);

	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < v_pGameObjects.size(); i++)
	{
		//if object is of type MenuButton then assign a callback based on the id passed in from the file 
		if (dynamic_cast<MenuButton*>(v_pGameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(v_pGameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void PauseState::initShaders()
{
	m_colorProgram.compileShaders("../Shaders/colorShader.vert", "../Shaders/colorShader.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertexUV");
	m_colorProgram.linkShaders();
}