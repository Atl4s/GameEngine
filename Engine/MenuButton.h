#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject
{
public:

	MenuButton();
	~MenuButton(){};
	virtual void load(const LoaderParams* pParams);
	virtual void draw(SpriteBatch& spriteBatch);
	virtual void update();
	virtual void clean();
	void setCallback(void(*callback) ()) { m_callback = callback; }
	int getCallbackID() { return m_callbackID; }

private:

	int m_callbackID;

	void(*m_callback)();

	bool m_bReleased;

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};