#pragma once

#include "Tree.h"

using namespace std;

float calculateTree(Tree::Node* node);


float calculateLeftTree(Tree::Node* node)
{
	if (node != nullptr && node->leftNode != nullptr)
	{
		if (node->leftNode->leftNode == nullptr && node->leftNode->rightNode == nullptr)
		{
			return node->leftNode->value - '0';
		}
		else
		{
			return calculateTree(node->leftNode);
		}
	}
	else
	{
		return 0;
	}
}


float calculateRigthTree(Tree::Node* node)
{
	if (node != nullptr && node->rightNode != nullptr)
	{
		if (node->rightNode->leftNode == nullptr && node->rightNode->rightNode == nullptr)
		{
			return node->rightNode->value - '0';
		}
		else
		{
			return calculateTree(node->rightNode);
		}
	}
	else
	{
		return 0;
	}
}


float calculateTree(Tree::Node* node)
{
	if (node != nullptr)
	{
		float leftTreeValue = calculateLeftTree(node);
		float calculateRigthValue = calculateRigthTree(node);

		switch (node->value)
		{
		case '+':
			return leftTreeValue + calculateRigthValue;
		case '-':
			return leftTreeValue - calculateRigthValue;
		case '*':
			return leftTreeValue * calculateRigthValue;
		case '/':
			return leftTreeValue / calculateRigthValue;
		}
	}
	else
	{
		return 0;
	}
}


float calculateTreeExpression(Tree::Node* node)
{
	return calculateTree(node);
}

float calculateLeftTree(Tree* tree)
{
	return calculateTree(tree->getRoot()->leftNode);
}

float calculateRigthTree(Tree* tree)
{
	return calculateTree(tree->getRoot()->rightNode);
}