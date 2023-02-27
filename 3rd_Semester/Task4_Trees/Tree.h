#pragma once

#include <string>
#include <vector>

using namespace std;

class Tree
{
public:
	
	struct Node
	{
		Node* leftNode = nullptr;
		Node* rightNode = nullptr;
		char value;

		Node(char value)
		{
			this->value = value;
		}
	};

	Tree();

	Tree(std::string expression);

	Node* getRoot();

private:

	vector<int> findOperatorIndexes(string expression);

	Node* createTree(string expression);

	Node* root;
};


Tree::Tree()
{
	root = nullptr;
}

Tree::Tree(std::string expression)
{
	if (expression.length() == 1)
	{
		root = new Node(expression[0]);
		return;
	}
	
	vector<int> operatorIndexes = findOperatorIndexes(expression);

	int centerOperatorIndex = operatorIndexes.size() / 2;

	root = new Node(expression[operatorIndexes[centerOperatorIndex]]);

	//Создание левого поддерева
	string leftExpression = expression.substr(0, operatorIndexes[centerOperatorIndex]);
	root->leftNode = createTree(leftExpression);

	//Создание правого поддерева
	string rightExpression = expression.substr(operatorIndexes[centerOperatorIndex] + 1);
	root->rightNode = createTree(rightExpression);
}

Tree::Node* Tree::createTree(string expression)
{
	vector<int> operatorIndexes = findOperatorIndexes(expression);

	int centerOperatorIndex = operatorIndexes.size() / 2;

	Tree::Node* node = nullptr;

	if (operatorIndexes.size() != 0)
	{
		node = new Tree::Node(expression[operatorIndexes[centerOperatorIndex]]);

		string leftExpression = expression.substr(0, operatorIndexes[centerOperatorIndex]);
		node->leftNode = createTree(leftExpression);

		string rightExpression = expression.substr(operatorIndexes[centerOperatorIndex] + 1);
		node->rightNode = createTree(rightExpression);
	}
	else
	{
		node = new Tree::Node(expression[centerOperatorIndex]);
	}

	return node;
}


vector<int> Tree::findOperatorIndexes(string expression)
{
	vector<int> operatorIndexes;
	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
		{
			operatorIndexes.push_back(i);
		}
	}
	return operatorIndexes;
}


Tree::Node* Tree::getRoot()
{
	return root;
}