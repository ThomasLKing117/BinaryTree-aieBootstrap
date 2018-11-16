#include "CDDS_BinaryTreeApp.h"

aie::Font* g_systemFont = nullptr;

CDDS_BinaryTreeApp::CDDS_BinaryTreeApp()
{

}

CDDS_BinaryTreeApp::~CDDS_BinaryTreeApp()
{

}

bool CDDS_BinaryTreeApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	g_systemFont = new aie::Font("./font/consolas.ttf", 32);

	return true;
}

void CDDS_BinaryTreeApp::shutdown()
{
	delete g_systemFont;
	delete m_2dRenderer;
}

void CDDS_BinaryTreeApp::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	static int value = 0;
	ImGui::InputInt("Value", &value);

	if (ImGui::Button("Insert", ImVec2(50, 0)))
	{
		m_binaryTree.insert(value);
		m_selectedNode = m_binaryTree.find(value);
	}

	if (ImGui::Button("Remove", ImVec2(50, 0)))
	{
		m_binaryTree.remove(value);
	}

	if (ImGui::Button("Find", ImVec2(50, 0)))
	{
		m_selectedNode = m_binaryTree.find(value);
	}
}

void CDDS_BinaryTreeApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_binaryTree.draw(m_2dRenderer, g_systemFont, m_selectedNode);

	// output some text
	m_2dRenderer->drawText(g_systemFont, "Press ESC to quit", 0, 0 + 1);

	// done drawing sprites
	m_2dRenderer->end();
}
