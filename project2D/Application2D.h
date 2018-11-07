#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <imgui.h>

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		m_IdleAdvent;
	aie::Texture*		m_WalkingAdvent;

	float m_timer;
	float m_AdventPosX, m_AdventPosY;
	int op;
};