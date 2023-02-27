#include <iostream>
#include <clocale>
#include "list.c++"

using namespace std;

template<typename T>
void printMenu(List<T>& l1, List<T>& l2);

template<typename T>
void createList(List<T>& l);

template<typename T>
void printList(List<T>& listToPrint);

template<typename T>
List<T>& combineLists(List<T>& l1, List<T>& l2);

template<typename T>
void deleteEvenCells(List<T>& l);

template<typename T>
void magicalRework(List<T>& l);


int main() 
{
	setlocale(LC_ALL, "Russian");
	List<int> newList;
	createList(newList);
	cout << "old: ";
	printList(newList);
	cout << "\n������� x � y:";
	size_t x, y;
	cin >> x >> y;
	cout << "new: ";
	newList.doSmthng(x, y);
	printList(newList);

}
//	setlocale(LC_ALL, "ru");
//
//	// ������� ����������
//	List<int> L1;
//	List<int> L2;
//	List<int> L;
//
//	//���������� ��� ����������������� �����.
//	int userMenuChoice = -1;
//	int userCreatingChoice = -1;
//
//	// ������� ����-����.
//	while (userMenuChoice != 0) { 
//		system("cls");
//		printMenu(L1, L2);
//
//		cin >> userMenuChoice;
//		cin.ignore();
//
//		switch (userMenuChoice) {
//
//		//������������ L1 � L2
//		case 1:
//			cout << "����� ������ �� ������ ���������?\n";
//			cout << "��� �����: ";
//			cin >> userCreatingChoice;
//			switch (userCreatingChoice)
//			{
//			case 1:
//				createList(L1);
//				break;
//			case 2:
//				createList(L2);
//				break;
//			default:
//				cout << "������������ ����!\n";
//				cin.clear();
//				system("pause");
//				break;
//			}
//			system("pause");
//			break;
//
//		//������������ L
//		case 2:
//			if (L1.getSize() && L2.getSize())
//			{
//				cout << "������ L - set L1 � L2: ";
//				printList(combineLists(L1, L2));
//				cout << endl;
//			}
//			else
//			{
//				cout << "�������� ����������! ��������� ��� ������.\n";
//			}
//			system("pause");
//			break;
//
//		//������� ������ ������ �� L1
//		case 3:
//			if (L1.getSize())
//			{
//				deleteEvenCells(L1);
//				cout << "������ �� ������ �������� ������� �� ������ L1\n";
//			}
//			else
//			{
//				cout << "�������� ����������! ����������� ������ L1\n";
//			}
//			system("pause");
//			break;
//			
//		//������� ����� ��� ����� �� ����� � L2
//		case 4:
//			if (L2.getSize())
//			{
//				magicalRework(L2);
//				cout << "� ������ L2 ����� ������ ���� ����� ���� ��������� �� �����.\n";
//			}
//			else
//			{
//				cout << "�������� ����������! ����������� ������ L2\n";
//			}
//			system("pause");
//			break;
//			
//		case 0:
//			cout << "�� ��������!\n";
//			userMenuChoice = 0;
//			system("pause");
//			break;
//
//		default:
//			cout << "� �� ������� ���, ��������� ����\n";
//			cin.clear();
//			system("pause");
//			break;
//
//		}
//	}
//		return 0;
//}
//
//
////������� ������ ����
//template<typename T>
//void printMenu(List<T>& l1, List<T>& l2)
//{
//	cout << "������������ ������ #5 ����-03-21 ������� �.�. ������� 1\n\n"
//		"������� 5 - ���������������� ������.\n"
//		"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n"
//		"������:" << endl << "L1: ";
//	printList(l1);
//	cout << endl << "L2: ";
//	printList(l2);
//	cout << endl;
//	cout << "������� [1], ����� ������������ ������.\n"
//		"������� [2], ����� ������������ � ������� ������ L - \"set\" L1 � L2.\n"
//		"������� [3], ����� ������� �� L1 ���� � ������� ���������.\n"
//		"������� [4], ����� �������� � L2 ����� ������ ���� ����� ����� ���� - ����� �������������� ����.\n"
//		"������� [0], ����� ��������� ������ ���������.\n";
//	cout << "��� �����: ";
//}
//
//
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
//
//
////������� ������ ������
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
	}
	else
	{
		cout << "����";
	}
}
//
//
////������� ������ ��� ����������� set'a �� L1 � L2
//template<typename T>
//List<T>& combineLists(List<T>& l1, List<T>& l2)
//{
//	List<T>* result = new List<T>;
//	T tempVal;
//	for (size_t i = 0; i < l1.getSize(); i++)
//	{
//		tempVal = l1[i];
//		if (result->lFind(tempVal) == -1)
//		{
//			result->pushBack(tempVal);
//		}
//	}
//	for (size_t i = 0; i < l2.getSize(); i++)
//	{
//		tempVal = l2[i];
//		if (result->lFind(tempVal) == -1)
//		{
//			result->pushBack(tempVal);
//		}
//	}
//	return *result;
//}
//
//
////�������� ����� �� ������ ��������
//template<typename T>
//void deleteEvenCells(List<T>& l)
//{
//	/* ������������ ���� ���� ��������, ��� ���� ��������������� ������� �� �������
//	* ������ � ��������� i = 0, 1, ... n, ��� n - ���-�� ����� � ������ �������,
//	* �� ����� ������� ��� ������ �� ������ ��������, �.� ��� �������� �����-���� ������ 
//	* ��������� ����������. � ���-�� ������ ������� ����� ����� ������� �������,
//	* ������������ ���������� �� 2. */
//	size_t forSize = l.getSize() / 2;
//	for (size_t i = 0; i < forSize; i++)
//	{
//		l.earase(i);
//	}
//}
//
//
////������� ��� ������� ����� ���� ����� ���� ����� 
//template<typename T>
//void magicalRework(List<T>& l)
//{
//	T currentSum = 0;
//	short pairCounter = 0;
//	for (size_t i = 0; i < l.getSize(); i++)
//	{
//		pairCounter++;
//		currentSum += l[i];
//		if (pairCounter == 2)
//		{
//			l.insert(currentSum, ++i);
//			currentSum = 0;
//			pairCounter = 0;
//
//		}
//	}
//}