#include <iostream>
#include <locale.h>
#include <vector>
using namespace std;


void printMenu(vector<long>& vec, bool isFilled);
void fillVector(vector<long>& vec, int size);
void printVector(vector<long>& vec, bool isFilled);
int findIndex(vector<long>& vec, long digit);
int findHighestDigit(int vaule);
int insertElement(vector<long>& vec, long element, int digit);
bool deleteElements(vector<long>& vec, int digit);


int main() {
	setlocale(LC_ALL, "Russian");
	//������� ����������.
	vector<long> mainVector{};
	//��������� ����������.
	int foundIndex;
	bool isVectorFilled = false;
	//���������� ��� ����������������� �����.
	int userSize = 0;
	int user�hoice = -1;
	int userDigit;
	long userElement;
	while (user�hoice != 0) { // ������� ����-����.
		printMenu(mainVector, isVectorFilled);
		cin >> user�hoice;
		switch (user�hoice) {
		case 1: // ���� ���������� �������.
			cout << "������� ���-�� ��������� � �������: ";
			cin >> userSize;
			if (userSize <= 0) {
				cout << "������ ����� ����������� �������!\n";
			}
			else {
				cout << "������� �������� �������: ";
				fillVector(mainVector, userSize);
				isVectorFilled = true;
			}
			system("pause");
			break;
		case 2: // ���� ������ �������.
			if (!isVectorFilled)
				cout << "������! ��������� ������ � ���������� �����\n";
			else {
				cout << "������� ������� �����:";
				cin >> userDigit;
				foundIndex = findIndex(mainVector, userDigit);
				if (foundIndex != -1)
					cout << "������� ������: " << foundIndex << "\n";
				else
					cout << "������ �� ������� :(\n";
			}
			system("pause");
			break;
		case 3: // ���� ������� ��������.
			if (!isVectorFilled)
				cout << "������! ��������� ������ � ���������� �����\n";
			else {
				cout << "������� �����, �� ������� ����� ����������� ����� ��������: ";
				cin >> userDigit;
				cout << "������� ��������, ������� ������ ��������: ";
				cin >> userElement;
				if (insertElement(mainVector, userElement, userDigit) == -1) {
					cout << "�� ��������� �������� ������ �� �������, ������ ��������� ������� :(\n";
				}
				else {
					cout << "������ �������.\n";
				}

			}
			system("pause");
			break;
		case 4: //���� �������� ��������(��).
			if (!isVectorFilled)
				cout << "������! ��������� ������ � ���������� �����\n";
			else {
				cout << "������� �����, �� ������� ����� ����������� ����� ���������: ";
				cin >> userDigit;
				if (deleteElements(mainVector, userDigit)) {
					cout << "������ �������.\n";
				}
				else {
					cout << "�� ��������� �������� ������ �� �������\n"
						"������ �������.\n";
				}
				if (mainVector.size() == 0) {
					isVectorFilled = false;
					cout << "����������� �������� ������ �������� ����.\n";
				}
			}
			system("pause");
			break;
		case 0: // ���� ������.
			user�hoice = 0;
			cout << "�� ��������!\n";
			system("pause");
			break;
		default:
			cout << "� �� ������� ���, ��������� ����\n";
			system("pause");
			break;
		}
	}
	return 0;
}


/*
��������� ����������� ���� � �������.
��������� - 1) ������, ������ � ������� ��������� ����,
			2) ������ �������� "�������� �� ������?"
*/
void printMenu(vector<long>& vec, bool isFilled) {
	system("cls");
	cout << "������������ ������ #1 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� 3 - ������\n"
		"================����================\n";
	if (isFilled) {
		cout << "\n";
		printVector(vec, isFilled);
		cout << "\n";
	}
	else {
		cout << "\n������� ������: ����\n\n";
	}
	cout << "1) ��������� ������\n"
		"2) ����� ������ �������� �������, ������� ����� �������� �������� ����� ��������.\n"
		"3) �������� ����� ������� � ������ ����� ��������� �������, ������� ����� �������� �������� ����� ��������\n"
		"4) ������� ��� �������� �������, ������� ����� �������� ������� ����� ��������.\n"
		"0) �����\n"
		"��� �����: ";
}


/*
��������� ���������� �������.
��������� - 1) ������, ������� ����� ���������,
			2) ����������� �������,
*/
void fillVector(vector<long>& vec, int size) {
	vec.clear();
	long elem;
	for (int i = 0; i < size; i++) {
		cin >> elem;
		vec.push_back(elem);
	}
}


/*
��������� ������ ������� � �������.
��������� - 1) �������, ������� ����� �������,
			2) ������ �������� "�������� �� ������?".
*/
void printVector(vector<long>& vec, bool isFilled) {
	if (!isFilled)
		cout << "������! ������ ����. ��������� ������ � ���������� �����.\n";
	else {
		cout << "������� ������: ";
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i] << " ";
		}
		cout << "\n";
	}
}


/*
������� ������ �������.
��������� - 1) ������, � ������� ������. �����,
			2) ����� ��� ������.
����.���� - 1) ������, ���� ������,
			2) -1 ���� �� ������.
*/
int findIndex(vector<long>& vec, long digit) {
	for (int i = 0; i < vec.size(); i++) {
		if (findHighestDigit(vec[i]) == digit) {
			return i;
		}
	}
	return -1;
}


/*
������� ������ ������� ����� �����.
��������� - 1) �����, � ������� ��������� �����.
�����.���� - 1) ������� ����� �����.
*/
int findHighestDigit(int vaule) {
	while (vaule > 9) {
		vaule /= 10;
	}
	return vaule;
}


/*
������� ������� �������� � ������.
��������� - 1) ������ ��� �������,
			2) ������� ��� �������,
			3) ����� ��� ������.
�����.���� - 1) ������ ���� �������� �������, ���� �����,
			 2) -1, ���� ������� �� ���������.
*/
int insertElement(vector<long>& vec, long element, int digit) {
	int index = findIndex(vec, digit);
	if (index != -1) {
		vec.insert(vec.begin() + index, element);
	}
	return index;
}


/*
��������� �������� ��������(��) � �������.
��������� - 1) ������ ��� �������,
			2) ����� ��� ������.
�����.���� - 1) true, ���� �����,
			 2) false, ���� �� ��������� ��������.
*/
bool deleteElements(vector<long>& vec, int digit) {
	bool isDeletedSmth = false;
	for (int i = 0; i < vec.size(); i++) {
		if (findHighestDigit(vec[i]) == digit) {
			vec.erase(vec.begin() + i);
			isDeletedSmth = true;
			i -= 1;
		}
	}
	return isDeletedSmth;
}