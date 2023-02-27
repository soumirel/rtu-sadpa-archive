
#include <iostream>
#include <locale.h>
#include "Graph.h"

using namespace std;


void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;

	//���������� ��� ������ ���������

	// ������� ����-����.
	while (userMenuChoice != 7)
	{
		std::system("cls");
		cout << "������������ ������ #6 ����-03-21 ������� �.�. ������� 15\n\n"
			"������� - ����.\n"
			"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n";

		cout << "������� [0] - ���� �������� �����\n"
			<< "������� [1], ����� ������� ���� ������� � ����������\n"
			"\n������� [7], ����� ��������� ������ ���������."
			"\n��� �����: ";

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice)
		{
		case 0:
		{
			//���� �� 10�� ����� �� ������� ������������ ������
			Graph graph;
			graph.addEdge(1, 2, 23);
			graph.addEdge(1, 3, 12);
			graph.addEdge(2, 3, 25);
			graph.addEdge(2, 5, 22);
			graph.addEdge(2, 8, 35);
			graph.addEdge(3, 4, 18);
			graph.addEdge(4, 6, 20);
			graph.addEdge(5, 6, 23);
			graph.addEdge(5, 7, 14);
			graph.addEdge(6, 7, 24);
			graph.addEdge(7, 8, 16);

			cout << "���� � ���� ������ ������ � ������: \n";
			graph.print();

			int vID = 5;
			cout << "������� ������� " << vID << ": "
				<< graph.calculateVertexDegree(vID) << '\n';

			cout << "���������� ���� �� ������� 1 � ������� 8: ";
			graph.showShortestPath(1, 8);

			break;
		}

		case 1:
		{
			Graph graph;
			int firstID, secondID, weight;
			char userChoice = 'Y';
			while (userChoice == 'Y')
			{
				cout << "������� ID ������ �������: ";
				cin >> firstID;
				cout << "������� ID ������ �������: ";
				cin >> secondID;
				cout << "������� ��� �����: ";
				cin >> weight;
				try
				{
					graph.addEdge(firstID, secondID, weight);
				}
				catch (const std::exception& e)
				{
					cout << e.what();
				}
				
				cout << "�������� ��� �����? (Y/N): ";
				cin >> userChoice;
			}
			cout << "���� � ���� ������ ������ � ������: \n";
			graph.print();

			int ID;
			cout << "������� ID �������, ��� ������� ����� ��������� �������: ";
			cin >> ID;
			cout << "������� ������� " << ID << ": "
				<< graph.calculateVertexDegree(ID) << '\n';

			cout << "������� ID ������ �������: ";
			cin >> firstID;
			cout << "������� ID ������ �������: ";
			cin >> secondID;
			cout << "���������� ���� �� ������� " << firstID
				<< " � ������� " << secondID << ": ";
			graph.showShortestPath(firstID, secondID);

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


