#include "TreeNode.h"
#include <iostream>

extern aie::Font* g_systemFont;
TreeNode::TreeNode(int value)
{
	m_left = nullptr;
	m_right = nullptr;
	m_value = value;
}

TreeNode::~TreeNode()
{

}

void TreeNode::draw(aie::Renderer2D * renderer, int x, int y, aie::Font* g_systemFont, bool selected)
{
	static char buffer[10];

	sprintf(buffer, "%d", m_value);

	renderer->setRenderColour(.22f, 1.f, .08f);
	renderer->drawCircle(x, y, 30);

	if (selected == true)
	{
		renderer->setRenderColour(1, 1, 1);
	}
	else
	{
		renderer->setRenderColour(0, 0, 0);
	}
		renderer->drawCircle(x, y, 28);
		renderer->setRenderColour(1, 0, 1);
		renderer->drawText(g_systemFont, buffer, x - 10, y - 10);
}
