#pragma once

#include <iostream>
#include <Windows.h>
#include "Tree.h"

using namespace std;

class TreePrinter
{
private:

	Tree* tree;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	enum Side
	{
		LEFT,
		RIGHT,
		FROM_ROOT
	};

	//Иннициализация консоли
	void InitializeConsole();

	//Вывод выражения из дерева прямым обходом
	void printExpression(Tree::Node* node);

	//
	void printNode(Tree::Node* node, size_t level, Side cameFrom = FROM_ROOT, size_t changeSidesAmount = 0);

public:
	//Пустой конструктор
	TreePrinter();
	
	//Конструктор параметризированный
	TreePrinter(Tree* tree);

	//Смена дерева
	void setTree(Tree* tree);

	//Рекурсивный вывод повёрнутого дерева
	void printTree();

	//Вывод выражения
	void printExpression();

	
};


TreePrinter::TreePrinter()
{
	tree = nullptr;
	InitializeConsole();
}


TreePrinter::TreePrinter(Tree* tree)
{
	this->tree = tree;
	InitializeConsole();
}


void TreePrinter::InitializeConsole()
{
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
}


void TreePrinter::setTree(Tree* tree)
{
	this->tree = tree;
}


void TreePrinter::printTree()
{
	printNode(tree->getRoot(), 0);
	cout << '\n';
}


void TreePrinter::printNode(Tree::Node* node, size_t level, Side cameFrom, size_t changeSidesAmount)
{
	if (node != nullptr)
	{
		if (cameFrom == LEFT)
		{
			printNode(node->rightNode, level + 1, RIGHT, changeSidesAmount + 1);
		}
		else
		{
			printNode(node->rightNode, level + 1, RIGHT, changeSidesAmount);
		}

		cout << '\n';

		for (int i = 0; i < level - 1 - changeSidesAmount && node != tree->getRoot(); i++)
		{
			cout << "    ";
		}

		for (int i = 0; i < changeSidesAmount && node != tree->getRoot(); i++)
		{
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
			cout << " ";
			SetConsoleTextAttribute(hConsole, saved_attributes);
			cout << "   ";
		}
		if (node != tree->getRoot())
		{
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
			cout << "    ";
		}

		SetConsoleTextAttribute(hConsole, saved_attributes);
		cout << node->value;

		if (cameFrom == RIGHT)
		{
			printNode(node->leftNode, level + 1, LEFT, changeSidesAmount + 1);
		}
		else
		{
			printNode(node->leftNode, level + 1, LEFT, changeSidesAmount);
		}

	}
}


void TreePrinter::printExpression()
{
	printExpression(tree->getRoot());
	cout << '\n';
}


void TreePrinter::printExpression(Tree::Node* node)
{
	if (node->leftNode != nullptr)
	{
		printExpression(node->leftNode);
	}

	if (node->leftNode == nullptr
		&& node->rightNode == nullptr)
	{
		cout << node->value << " ";
		return;
	}

	cout << node->value << " ";

	if (node->rightNode != nullptr)
	{
		printExpression(node->rightNode);
	}
}