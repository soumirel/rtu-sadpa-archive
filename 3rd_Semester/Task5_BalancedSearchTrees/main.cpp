
#include <iostream>
#include <locale.h>
#include <random>
#include "BinaryFile.h"
#include "BinarySearchTree.h"
#include "AVL-B-Tree.h"

using namespace std;

enum MenuState
{
	INIT = 0,
	EXIT = 7
};

void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;

	//���������� ��� ������ ���������
	BinaryFile* file;

	// ������� ����-����.
	while (userMenuChoice != 7)
	{
		std::system("cls");
		cout << "������������ ������ #4 ����-03-21 ������� �.�. ������� 15\n\n"
			"������� - �������.\n"
			"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n";

		cout << "������� [0] - ���� �������� ������ ������\n"
				"������� [1] - ���� ���������������� ������ ������\n"
			"\n������� [7], ����� ��������� ������ ���������."
			"\n��� �����: ";
		
		cin >> userMenuChoice;
		cin.ignore();
		
		switch (userMenuChoice)
		{
		case 0:
		{
			string fileName = "fileName";
			file = new BinaryFile(fileName);
			cout << "���������� �����\n";
			file->print();
			cout << "-------------------\n";
			BinaryTreeManager tree(file);
			cout << "������:\n";
			tree.print();
			//cout << "-------------------\n";
			//cout << "�������� �������� 23.04\n";
			//char key[6] = "23.04";
			//tree.remove(key);
			//cout << "������:\n";
			//tree.print();
			//cout << "-------------------\n";
			//cout << "����� �������� 12.02\n";
			//strcpy_s(key, "12.02");
			//cout << "������ ��������\n";
			//cout << tree.find(key) << endl;
			//cout << "�������� �������\n";
			//cout << file->find(key) << '\n';
			break;
		}

		case 1:
		{
			string fileName = "fileName";
			file = new BinaryFile(fileName);
			cout << "���������� �����\n";
			file->print();
			cout << "-------------------\n";
			BTreeManager tree(file, 3);
			cout << "������\n";
			tree.print();
			cout << "-------------------\n";
			cout << "�������� �������� 23.04\n";
			char key[6] = "23.04";
			tree.remove(key);
			cout << "������:\n";
			tree.print();
			cout << "-------------------\n";
			cout << "����� �������� 12.02\n";
			strcpy_s(key, "12.02");
			cout << "������ ��������\n";
			cout << tree.find(key) << endl;
			cout << "�������� �������\n";
			cout << file->find(key) << '\n';
			break;
			break;
		}

		case 7:
			cout << "\n�� ��������!\n";
			break;

		default:
			cout << "\n� �� ������� ���.\n";
			cin.clear();
			break;
		}
		std::system("pause");
	}
}