#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_timer = 0;

	op = 2;

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		//SpritePosY += 250.0f * deltaTime;
		//m_2dRenderer->setUVRect(animate);
		op = 1;
	}

	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		//SpritePosY -= 250.0f * deltaTime;
		//m_2dRenderer->setUVRect(animate);
		op = 2;
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		//SptritePosX -= 250.0f * deltaTime;
		//m_2dRenderer->setUVRect(animate);
		op = 3;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		//SpritePosX+= 250.0f * deltaTime;
		//m_2dRenderer->setUVRect(animate);
		op = 4;
	}

	switch (op)
	{
		case 1:
		{
			if (input->isKeyUp(aie::INPUT_KEY_W))
			{
				//m_2dRenderer->setUVRect(animate);
			}
			break;
		}
		case 2:
		{
			if (input->isKeyUp(aie::INPUT_KEY_S))
			{
				//m_2dRenderer->setUVRect(animate);
			}
			break;
		}
		case 3:
		{
			if (input->isKeyUp(aie::INPUT_KEY_A))
			{
				//m_2dRenderer->setUVRect(animate);
			}
			break;
		}
		case 4:
		{
			if (input->isKeyUp(aie::INPUT_KEY_D))
			{
				//m_2dRenderer->setUVRect(animate);
			}
			break;
		}
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}