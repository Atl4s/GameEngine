#include "MenuButton.h"
#include "InputHandler.h"
#include "Camera2D.h"

MenuButton::MenuButton() : SDLGameObject()
{
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_callbackID = pParams->getCallBackID();
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw(SpriteBatch& spriteBatch)
{
	SDLGameObject::draw(spriteBatch);
}

void MenuButton::update()
{
	SDLGameObject::update();

	glm::vec2 pMousePos = InputHandler::Instance()->getMousePosition();
	pMousePos = Camera2D::Instance()->convertScreenToWorld(pMousePos);

	if ((pMousePos.x < (m_position.x + m_width))
		&& (pMousePos.x > m_position.x)
		&& (pMousePos.y < (m_position.y + m_height))
		&& (pMousePos.y > m_position.y))
	{
		if (InputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			m_callback();

			m_bReleased = false;
		}
		else if (!InputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else m_currentFrame = MOUSE_OUT;
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}