#include "Player.h"
#include "Camera2D.h"

Player::Player() : SDLGameObject()
{ 
}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	glm::vec4 color(250, 250, 250, 255);
	pe = new ParticleEngine(10000, m_position + glm::vec2(m_width / 2, m_height / 2), 0, 100000, 2, color);
}

void Player::draw(SpriteBatch& spriteBatch)
{
	pe->draw(spriteBatch);
	SDLGameObject::draw(spriteBatch);
}

void Player::update()
{
	m_velocity.x = 0;
	m_velocity.y = 0;

	handleInput();
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	pe->setPosition(m_position + glm::vec2(m_width/2, m_height/2));
	pe->update();

	SDLGameObject::update();
}

void Player::clean() {}

void Player::handleInput()
{
	
	if (InputHandler::Instance()->joysticksInitialised())
	{
		if (InputHandler::Instance()->xvalue(LEFT_STICK) > 0 ||
			InputHandler::Instance()->xvalue(LEFT_STICK) < 0) // left stick moves horizontaly
		{
			m_velocity.x = 1 * InputHandler::Instance()->xvalue(LEFT_STICK);
		}

		if (InputHandler::Instance()->yvalue(LEFT_STICK) > 0 ||
			InputHandler::Instance()->yvalue(LEFT_STICK) < 0) // left stick moves verticaly
		{
			m_velocity.y = 1 * InputHandler::Instance()->yvalue(LEFT_STICK);
		}

		if (InputHandler::Instance()->xvalue(RIGHT_STICK) > 0 ||
			InputHandler::Instance()->xvalue(RIGHT_STICK) < 0) // right stick moves horizontaly
		{
			m_velocity.x = 1 * InputHandler::Instance()->xvalue(RIGHT_STICK);
		}

		if (InputHandler::Instance()->yvalue(RIGHT_STICK) > 0 ||
			InputHandler::Instance()->yvalue(RIGHT_STICK) < 0) // right stick moves verticaly
		{
			m_velocity.y = 1 * InputHandler::Instance()->yvalue(RIGHT_STICK);
		}
		
		
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_A)) // button A
		{
			std::cout << "A" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_B)) // button B
		{
			std::cout << "B" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_X)) // button X
		{
			std::cout << "X" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_Y)) // button Y
		{
			std::cout << "Y" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_BACK)) //button back
		{
			std::cout << "back" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_START)) //button start
		{
			std::cout << "start" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_LEFTSTICK)) //left stick button
		{
			std::cout << "left stick" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_RIGHTSTICK)) //right stick button
		{
			std::cout << "right stick" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) //button LB
		{
			std::cout << "LB" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) //button RB
		{
			std::cout << "RB" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP)) //d-pad up
		{
			std::cout << "d-pad up" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) //d-pad down
		{
			std::cout << "d-pad down" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) //d-pad left
		{
			std::cout << "d-pad left" << std::endl;
		}
		if (InputHandler::Instance()->getButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) //d-pad right
		{
			std::cout << "d-pad right" << std::endl;
		}
		if (InputHandler::Instance()->getLeftTriggerState()) //Left trigger
		{
			std::cout << "LT" << std::endl;
		}
		if (InputHandler::Instance()->getRightTriggerState()) //Right trigger
		{
			std::cout << "RT" << std::endl;
		}
	}
	if (InputHandler::Instance()->getMouseButtonState(LEFT)) // left mouse button
	{
		m_velocity.x = 1.0f;
	}
	if (InputHandler::Instance()->getMouseButtonState(MIDDLE)) // middle mouse button
	{
		m_velocity.x = 1.0f;
	}
	if (InputHandler::Instance()->getMouseButtonState(RIGHT)) // right mouse button
	{
		m_velocity.x = 1.0f;
	}

	//glm::vec2 mouseCoords = InputHandler::Instance()->getMousePosition();
	//mouseCoords = Camera2D::Instance()->convertScreenToWorld(mouseCoords);

	//m_velocity = 0.1f * (mouseCoords - (m_position + glm::vec2(m_width/2, m_height/2)));

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) { m_velocity.x = 2.0f; }
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) { m_velocity.x = -2.0f; }
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) { m_velocity.y = -2.0f; }
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) { m_velocity.y = 2.0f; }

}