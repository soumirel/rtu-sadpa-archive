#include <iostream>
#include "list.c++"

using namespace std;

template<typename T>
void printMenu(List<T>& list);

template<typename T>
void createList(List<T>& l);

template<typename T>
void printList(List<T>& listToPrint);

template<typename T>
T findMinumim(List<T>& list, size_t ind, T minVal = 0);


void main()
{
	setlocale(LC_ALL, "ru");

	// ������� ����������
	List<int> list;

	//���������� ��� ����������������� �����.
	int userMenuChoice = -1;

	// ������� ����-����.
	while (userMenuChoice != 0)
	{
		system("cls");
		printMenu(list);

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice)
		{
		case 1:
			list.clear();
			createList(list);
			system("pause");
			break;

		case 2:
			if (list.getSize() != 0)
			{
				cout << "����������� �������� ������: " << findMinumim(list, 0) << "\n";
			}
			else
			{
				cout << "�������� ����������. ��������� ������.\n";
			}
			system("pause");
			break;

		case 0:
			cout << "�� ��������!\n";
			userMenuChoice = 0;
			system("pause");
			break;

		default:
			cout << "� �� ������� ���, ��������� ����\n";
			cin.clear();
			system("pause");
			break;
		}
	}
}


template<typename T>
void printMenu(List<T>& list)
{
	cout << "������������ ������ #6 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� 5 - ����������� ���������.\n"
		"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n"
		"�������� ������: ";
	printList(list);
	cout << "������� [1], ����� ������ ������.\n"
		"������� [2], ����� �������� ����������� �������� � ������.\n"
		"������� [0], ����� ��������� ������ ���������.\n";
	cout << "��� �����: ";
}


//������� ������� ������
template<typename T>
void createList(List<T>& l)
{
	size_t size;
	T currentVal;
	cout << "������� ���������� �������� �����: ";
	cin >> size;
	cout << "������� " << size << " ��������: ";
	for (size_t i = 0; i < size; i++)
	{
		cin >> currentVal;
		l.pushBack(currentVal);
	}
}


//������� ������ ������
template<typename T>
void printList(List<T>& listToPrint)
{
	if (listToPrint.getSize())
	{
		size_t printSize = listToPrint.getSize();
		for (size_t i = 0; i < printSize; i++)
		{
			cout << listToPrint[i] << " ";
		}
		cout << "\n";
	}
	else
	{
		cout << "����\n";
	}
}


template<typename T>
T findMinumim(List<T>& list, size_t ind, T minVal)
{
	if (ind >= list.getSize())
	{
		return minVal;
	}
	else
	{
		if (ind == 0)
		{
			minVal = list[ind];
		}

		if (minVal > list[ind])
		{
			minVal = list[ind];
		}
		return findMinumim(list, ind + 1, minVal);
	}
}