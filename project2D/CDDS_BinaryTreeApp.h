#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "BinaryTree.h"
#include <Input.h>
#include <imgui.h>
#include <Font.h>

class CDDS_BinaryTreeApp : public aie::Application
{
public:
	CDDS_BinaryTreeApp();
	virtual ~CDDS_BinaryTreeApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			g_systemFont;

	BinaryTree			m_binaryTree;
	TreeNode*			m_selectedNode;

	float m_timer;
};