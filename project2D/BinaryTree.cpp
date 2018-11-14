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

void BinaryTree::insert(int a_nValue)
{
	//created two nodes that are set to the root
	TreeNode* currentNode = m_pRoot;
	TreeNode* ParentNode = m_pRoot;

	//checks to see if the tree is empty
	if (isEmpty() == true)
	{
		//sets the first node inserted to be the root of the tree
		TreeNode* first = new TreeNode(a_nValue);
		m_pRoot = first;
		return;
	}

	//runs while the current node is not pointing to null
	while (currentNode != nullptr)
	{
		//checks if the value inserted is less than the current node
		if (a_nValue < currentNode->getData())
		{
			//creates a new node and points current node to its left null to be inserted later
			//while making parent point to current node
			TreeNode* newNode = new TreeNode(a_nValue);
			ParentNode = currentNode;
			currentNode = currentNode->getLeft();
			continue;
		}

		//checks if the value inserted is greater than the current node
		if (a_nValue > currentNode->getData())
		{
			//creates a new node and points current node to its right null to be inserted later
			//while making parent point to current node
			TreeNode* newNode = new TreeNode(a_nValue);
			ParentNode = currentNode;
			currentNode = currentNode->getRight();
			continue;
		}

		//checks if the value inserted is equal than the current node
		if (a_nValue == currentNode->getData())
		{
			return;
		}
	}

	//checks if the value to be inserted is less than the parent node
	if (a_nValue < ParentNode->getData())
	{
		//sets the parents node left to the inserted value
		//which will make current become the inserted value
		TreeNode* test = new TreeNode(a_nValue);
		ParentNode->setLeft(test);
	}

	//checks if the value to be inserted is greater than the parent node
	if (a_nValue > ParentNode->getData())
	{
		//sets the parents node right to the inserted value
		//which will make current become the inserted value
		TreeNode* test = new TreeNode(a_nValue);
		ParentNode->setRight(test);
	}
}

void BinaryTree::remove(int a_nValue)
{
	//created two nodes that are set to the root
	TreeNode* currentNode = m_pRoot;
	TreeNode* parentNode = m_pRoot;

	//created two node pointers that are set to the nodes we just created
	TreeNode** ptrCurrentNode = &currentNode;
	TreeNode** ptrParentNode = &parentNode;

	//checks to see if the node you are finding exist
	if (findNode(a_nValue, ptrCurrentNode, ptrParentNode))
	{
		//checks if the current node has a right node
		if (currentNode->hasRight())
		{
			//creates two Iterating nodes set to the node pointers
			TreeNode* IterCurrent = (*ptrCurrentNode);
			TreeNode* IterParent = (*ptrParentNode);

			//checks if the Iterating currents node has a right node
			if (IterCurrent->hasRight())
			{
				//points Iterator currents node to its right
				//while making Iterator parents node point to Iterator currents node
				IterParent = IterCurrent;
				IterCurrent = IterCurrent->getRight();
			}

			//runs while the Iterator currents node has a left node
			while (IterCurrent->hasLeft())
			{
				//points Iterator currents node to its left
				//while making Iterator parents node point to Iterator currents node
				IterParent = IterCurrent;
				IterCurrent = IterCurrent->getLeft();
			}

			//sets the current nodes data to the iterating currents node data
			currentNode->setData(IterCurrent->getData());

			//checks if the Iterating parents nodes left eqauls the Iterator currents node
			if (IterParent->getLeft() == IterCurrent)
			{
				//sets Iterator parents left node is set to Iterator currents right node 
				IterParent->setLeft(IterCurrent->getRight());
			}

			//checks if the Iterating parents nodes right eqauls the Iterator currents node
			else if (IterParent->getRight() == IterCurrent)
			{
				//sets Iterator parents right node is set to Iterator currents right node 
				IterParent->setRight(IterCurrent->getRight());
			}
			delete IterCurrent;
		}

		else
		{
			//checks if the parents nodes left eqauls the currents node
			if (parentNode->getLeft() == currentNode)
			{
				//sets parents left node is set to currents right node 
				parentNode->setLeft(currentNode->getLeft());
			}

			//checks if the parents nodes right eqauls the currents node
			else if (parentNode->getRight() == currentNode)
			{
				//sets parents right node is set to currents right node 
				parentNode->setRight(currentNode->getLeft());
			}

			//checks if the root equals the currents node
			else if (m_pRoot == currentNode)
			{
				//sets the root to the current nodes left
				m_pRoot = currentNode->getLeft();
			}
			delete currentNode;
		}
	}
}

TreeNode * BinaryTree::find(int a_nValue)
{
	//creates a current node pointer which is set to the root
	TreeNode* currentNode = m_pRoot;

	//runs while the current node is not pointing to null
	while (currentNode != nullptr)
	{
		//checks to see if the value inserted is less than the current node
		if (a_nValue < currentNode->getData())
		{
			//points to current nodes left
			currentNode = currentNode->getLeft();
			continue;
		}
		
		//checks to see if the value inserted is greater than the current node
		if (a_nValue > currentNode->getData())
		{
			//points to current nodes right
			currentNode = currentNode->getRight();
			continue;
		}

		//checks to see if the value inserted is equal than the current node
		if (a_nValue == currentNode->getData())
		{
			//returns the current node
			return currentNode;
		}
	}
}

void BinaryTree::draw(aie::Renderer2D * renderer, aie::Font* g_systemFont, TreeNode * selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, g_systemFont, selected);
}

bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	//created two nodes that are set to the root
	TreeNode* currentNode = m_pRoot;
	TreeNode* parentNode = m_pRoot;

	//runs while the current node is not pointing to null
	while (currentNode != nullptr)
	{
		//checks to see if the value inserted is equal than the current node
		if (a_nSearchValue == currentNode->getData())
		{
			*ppOutNode = currentNode;
			*ppOutParent = parentNode;
			return true;
		}

		//checks to see if the value inserted is less than the current node
		if (a_nSearchValue < currentNode->getData())
		{
			parentNode = currentNode;
			currentNode = currentNode->getLeft();
		}

		//checks to see if the value inserted is greater than the current node
		if (a_nSearchValue > currentNode->getData())
		{
			parentNode = currentNode;
			currentNode = currentNode->getRight();
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