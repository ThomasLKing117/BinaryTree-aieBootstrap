#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
}

bool BinaryTree::isEmpty() const
{
	if (m_pRoot == nullptr)
	{
		return true;
	}
	return false;
}


//	If the tree is empty, the value is inserted at the root
//	Set the current node to the root
//	While the current node is not null
//		If the value to be inserted is less than the value in the current node
//			Set the current node to the left child and continue
//		If the value to be inserted is greater than the current node
//			Set the current node to the right child and continue
//		If the value to be inserted is the same as the value in the current node
//			The value is already in the tree, so exit 
//	end While
//	Get the parent of the current node(before it was set to null)
//	If value to be inserted is less than parent
//		insert value as left child node
//	otherwise insert value as right child node
void BinaryTree::insert(int a_nValue)
{
	TreeNode* currentNode = m_pRoot;
	TreeNode* ParentNode;

	if (isEmpty() == true)
	{
		m_pRoot = new TreeNode(a_nValue);
		return;
	}

	while (currentNode != nullptr)
	{
		if (a_nValue < currentNode->getData())
		{
			ParentNode = currentNode;
			currentNode = currentNode->getLeft();
			continue;
		}
		if (a_nValue > currentNode->getData())
		{
			ParentNode = currentNode;
			currentNode = currentNode->getRight();
			continue;
		}
		if (a_nValue == currentNode->getData())
		{
			return;
		}
	}

	if (a_nValue < ParentNode->getData())
	{
		TreeNode* test = new TreeNode(a_nValue);
		ParentNode->setLeft(test);
	}
	if (a_nValue > ParentNode->getData())
	{
		TreeNode* test = new TreeNode(a_nValue);
		ParentNode->setRight(test);
	}
}


//	find the value in the tree, obtaining a pointer to the node and its parent
//	If the current node has a right branch, then
//		find the minimum value in the right branch by iterating down the left branch of the
//			current node’s right child until there are no more left branch nodes
//		copy the value from this minimum node to the current node
//		find the minimum node’s parent node(the parent of the node you are deleting)
//			if you are deleting the parent’s left node
//				set this left child of the parent to the right child of the minimum
//				node
//			if you are deleting the parent’s right node
//				set the right child of the parent to the minimum node’s right child
//	If the current node has no right branch
//		if we are deleting the parent’s left child, set the left child of the parent to the left
//			child of the current node
//		If we are deleting the parent’s right child, set the right child of the parent to the left
//			child of the current node
//		If we are deleting the root, the root becomes the left child of the current node
void BinaryTree::remove(int a_nValue)
{
	TreeNode* currentNode = m_pRoot;
	TreeNode* parentNode = m_pRoot;

	TreeNode** ptrCurrentNode = &currentNode;
	TreeNode** ptrParentNode = &parentNode;

	if (findNode(a_nValue, ptrCurrentNode, ptrParentNode))
	{
		if (currentNode->hasRight())
		{
			TreeNode* IterCurrent = (*ptrCurrentNode);
			TreeNode* IterParent = (*ptrParentNode);

			if (IterCurrent->hasRight())
			{
				IterParent = IterCurrent;
				IterCurrent = IterCurrent->getRight();
			}

			while (IterCurrent->hasLeft())
			{
				IterParent = IterCurrent;
				IterCurrent = IterCurrent->getLeft();
			}

			currentNode->setData(IterCurrent->getData());

			if (IterParent->getLeft() == IterCurrent)
			{
				IterParent->setLeft(IterCurrent->getRight());
			}

			else if (IterParent->getRight() == IterCurrent)
			{
				IterParent->setRight(IterCurrent->getRight());
			}
			delete IterCurrent;
		}

		else
		{
			if (parentNode->getLeft() == currentNode)
			{
				parentNode->setLeft(currentNode->getLeft());
			}
			else if (parentNode->getRight() == currentNode)
			{
				parentNode->setRight(currentNode->getLeft());
			}
			else if (m_pRoot == currentNode)
			{
				m_pRoot = currentNode->getLeft();
			}
			delete currentNode;
		}
	}
}

TreeNode * BinaryTree::find(int a_nValue)
{
	TreeNode* currentNode = m_pRoot;

	while (currentNode != nullptr)
	{
		if (a_nValue < currentNode->getData())
		{
			if (currentNode->hasLeft())
			{
				currentNode = currentNode->getLeft();
				continue;
			}
		}

		else if (a_nValue > currentNode->getData())
		{
			if (currentNode->hasRight())
			{
				currentNode = currentNode->getRight();
				continue;
			}
		}

		if (a_nValue == currentNode->getData())
		{
			return currentNode;
		}
	}
}

void BinaryTree::draw(aie::Renderer2D * renderer, aie::Font* g_systemFont, TreeNode * selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, g_systemFont, selected);
}


//	Set the current node to the root
//	While the current node is not null
//		if the search value equals the current node value,
//			return the current node and its parent
//		otherwise
//			If the search value is less than the current node
//				set the current node to the left child
//			otherwise set the current node to the right child
//	end While
//	If the loop exits, then a match was not found, so return false
bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	while (ppOutNode != nullptr)
	{
		if ((*ppOutNode)->getData() < a_nSearchValue)
		{
			if ((*ppOutNode)->hasRight())
			{
				*ppOutParent = *ppOutNode;
				*ppOutNode = (*ppOutNode)->getRight();
			}
		}
		else if ((*ppOutNode)->getData() > a_nSearchValue)
		{
			if ((*ppOutNode)->hasLeft())
			{
				*ppOutParent = *ppOutNode;
				*ppOutNode = (*ppOutNode)->getLeft();
			}
		}
		else if ((*ppOutNode)->getData() == a_nSearchValue)
		{
			return true;
		}
	}
	return false;
}

void BinaryTree::draw(aie::Renderer2D * renderer, TreeNode *pNode, int x, int y, int horizontalSpacing, aie::Font* g_systemFont, TreeNode * selected)
{
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->hasLeft())
		{
			renderer->setRenderColour(0.5f, 0.5f, 0.5f);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing, y - 80, horizontalSpacing, g_systemFont, selected);
		}

		if (pNode->hasRight())
		{
			renderer->setRenderColour(.5f, .5f, .5f);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getRight(), x + horizontalSpacing, y - 80, horizontalSpacing, g_systemFont, selected);
		}
		pNode->draw(renderer, x, y, g_systemFont, (selected == pNode));
	}
}





















//
//#include "BinaryTree.h"
//
//BinaryTree::BinaryTree()
//{
//	m_pRoot = nullptr;
//}
//
//BinaryTree::~BinaryTree()
//{
//}
//
//bool BinaryTree::isEmpty() const
//{
//	if (m_pRoot == nullptr)
//	{
//		return true;
//	}
//	return false;
//}
//
//
////	If the tree is empty, the value is inserted at the root
////	Set the current node to the root
////	While the current node is not null
////		If the value to be inserted is less than the value in the current node
////			Set the current node to the left child and continue
////		If the value to be inserted is greater than the current node
////			Set the current node to the right child and continue
////		If the value to be inserted is the same as the value in the current node
////			The value is already in the tree, so exit 
////	end While
////	Get the parent of the current node(before it was set to null)
////	If value to be inserted is less than parent
////		insert value as left child node
////	otherwise insert value as right child node
//void BinaryTree::insert(int a_nValue)
//{
//	TreeNode* currentNode = m_pRoot;
//	TreeNode* ParentNode = m_pRoot;
//
//	if (isEmpty() == true)
//	{
//		TreeNode* first = new TreeNode(a_nValue);
//		m_pRoot = first;
//		return;
//	}
//
//	while (currentNode != nullptr)
//	{
//		if (a_nValue < currentNode->getData())
//		{
//			TreeNode* newNode = new TreeNode(a_nValue);
//			ParentNode = currentNode;
//			currentNode = currentNode->getLeft();
//			continue;
//		}
//		if (a_nValue > currentNode->getData())
//		{
//			TreeNode* newNode = new TreeNode(a_nValue);
//			ParentNode = currentNode;
//			currentNode = currentNode->getRight();
//			continue;
//		}
//		if (a_nValue == currentNode->getData())
//		{
//			return;
//		}
//	}
//
//	if (a_nValue < ParentNode->getData())
//	{
//		TreeNode* test = new TreeNode(a_nValue);
//		ParentNode->setLeft(test);
//	}
//	if (a_nValue > ParentNode->getData())
//	{
//		TreeNode* test = new TreeNode(a_nValue);
//		ParentNode->setRight(test);
//	}
//}
//
//
////	find the value in the tree, obtaining a pointer to the node and its parent
////	If the current node has a right branch, then
////		find the minimum value in the right branch by iterating down the left branch of the
////			current node’s right child until there are no more left branch nodes
////		copy the value from this minimum node to the current node
////		find the minimum node’s parent node(the parent of the node you are deleting)
////			if you are deleting the parent’s left node
////				set this left child of the parent to the right child of the minimum
////				node
////			if you are deleting the parent’s right node
////				set the right child of the parent to the minimum node’s right child
////	If the current node has no right branch
////		if we are deleting the parent’s left child, set the left child of the parent to the left
////			child of the current node
////		If we are deleting the parent’s right child, set the right child of the parent to the left
////			child of the current node
////		If we are deleting the root, the root becomes the left child of the current node
//void BinaryTree::remove(int a_nValue)
//{
//	TreeNode* currentNode = m_pRoot;
//	TreeNode* parentNode = m_pRoot;
//
//	TreeNode** ptrCurrentNode = &currentNode;
//	TreeNode** ptrParentNode = &parentNode;
//
//	if (findNode(a_nValue, ptrCurrentNode, ptrParentNode))
//	{
//		if (currentNode->hasRight())
//		{
//			TreeNode* IterCurrent = (*ptrCurrentNode);
//			TreeNode* IterParent = (*ptrParentNode);
//
//			while (IterCurrent->hasLeft())
//			{
//				IterParent = IterCurrent;
//				IterCurrent = IterCurrent->getLeft();
//			}
//
//			currentNode->setData(IterCurrent->getData());
//
//			if (IterParent->getLeft() == IterCurrent)
//			{
//				IterParent->setLeft(IterCurrent->getRight());
//			}
//
//			else if (IterParent->getRight() == IterCurrent)
//			{
//				IterParent->setRight(IterCurrent->getRight());
//			}
//			delete IterCurrent;
//		}
//
//		else
//		{
//			if (parentNode->getLeft() == currentNode)
//			{
//				parentNode->setLeft(currentNode->getLeft());
//			}
//			else if (parentNode->getRight() == currentNode)
//			{
//				parentNode->setRight(currentNode->getLeft());
//			}
//			else if (m_pRoot == currentNode)
//			{
//				m_pRoot = currentNode->getLeft();
//			}
//			delete currentNode;
//		}
//	}
//}
//
//TreeNode * BinaryTree::find(int a_nValue)
//{
//	TreeNode* currentNode = m_pRoot;
//
//	while (currentNode != nullptr)
//	{
//		if (a_nValue < currentNode->getData())
//		{
//			currentNode = currentNode->getLeft();
//			continue;
//		}
//		if (a_nValue > currentNode->getData())
//		{
//			currentNode = currentNode->getRight();
//			continue;
//		}
//		if (a_nValue == currentNode->getData())
//		{
//			return currentNode;
//		}
//	}
//}
//
//void BinaryTree::draw(aie::Renderer2D * renderer, aie::Font* g_systemFont, TreeNode * selected)
//{
//	draw(renderer, m_pRoot, 640, 680, 640, g_systemFont, selected);
//}
//
//
////	Set the current node to the root
////	While the current node is not null
////		if the search value equals the current node value,
////			return the current node and its parent
////		otherwise
////			If the search value is less than the current node
////				set the current node to the left child
////			otherwise set the current node to the right child
////	end While
////	If the loop exits, then a match was not found, so return false
//bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
//{
//	TreeNode* currentNode = m_pRoot;
//	TreeNode* parentNode = m_pRoot;
//
//	while (currentNode != nullptr)
//	{
//		if (a_nSearchValue == currentNode->getData())
//		{
//			*ppOutNode = currentNode;
//			*ppOutParent = parentNode;
//			return true;
//		}
//		else
//		{
//			if (a_nSearchValue < currentNode->getData())
//			{
//				parentNode = currentNode;
//				currentNode = currentNode->getLeft();
//			}
//			else
//			{
//				parentNode = currentNode;
//				currentNode = currentNode->getRight();
//			}
//		}
//	}
//	return false;
//}
//
//void BinaryTree::draw(aie::Renderer2D * renderer, TreeNode *pNode, int x, int y, int horizontalSpacing, aie::Font* g_systemFont, TreeNode * selected)
//{
//	horizontalSpacing /= 2;
//
//	if (pNode)
//	{
//		if (pNode->hasLeft())
//		{
//			renderer->setRenderColour(0.5f, 0.5f, 0.5f);
//			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
//			draw(renderer, pNode->getLeft(), x - horizontalSpacing, y - 80, horizontalSpacing, g_systemFont, selected);
//		}
//
//		if (pNode->hasRight())
//		{
//			renderer->setRenderColour(.5f, .5f, .5f);
//			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
//			draw(renderer, pNode->getRight(), x + horizontalSpacing, y - 80, horizontalSpacing, g_systemFont, selected);
//		}
//		pNode->draw(renderer, x, y, g_systemFont, (selected == pNode));
//	}
//}