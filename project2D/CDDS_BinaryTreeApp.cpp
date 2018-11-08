#include "CDDS_BinaryTreeApp.h"

CDDS_BinaryTreeApp::CDDS_BinaryTreeApp()
{

}

CDDS_BinaryTreeApp::~CDDS_BinaryTreeApp()
{

}

bool CDDS_BinaryTreeApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	return true;
}

void CDDS_BinaryTreeApp::shutdown()
{

}

void CDDS_BinaryTreeApp::update(float deltaTime)
{

}

void CDDS_BinaryTreeApp::draw()
{
	clearScreen();
	m_2dRenderer->begin();
	m_2dRenderer->drawCircle(250, 250, 25);
	m_2dRenderer->end();
}
