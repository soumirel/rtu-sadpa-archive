#include <iostream>
#include <locale.h>
using namespace std;


const int constArrSize = 1000;
void printMenu(long* array, int size, bool isFilled);
void fillArray(long* array, int size);
void printArray(long* array, int size, bool isArrayFilled);
int findIndex(long* array, int size, long digit);
int findHighestDigit(int vaule);
int insertElement(long* array, int size, long element, int digit);
int deleteElements(long* array, int size, int digit);


int main() {
	setlocale(LC_ALL, "Russian");
	//������� ����������.
	long mainArray[constArrSize];
	int actualSize = 0;
	//��������� ����������.
	int numDeletedElems = 0;
	int foundIndex;
	bool isArrayFilled = false;
	//���������� ��� ����������������� �����.
	int userChoice = 1;
	int userDigit;
	long userElement;
	while (userChoice != 0) { // ������� ����-����.
		printMenu(mainArray, actualSize, isArrayFilled);
		cin >> userChoice;
		switch (userChoice) {
		case 1: // ���� ���������� �������.
			cout << "������� ���-�� ��������� � �������: ";
			cin >> actualSize;
			if (actualSize <= 0 || actualSize > constArrSize) {
				cout << "������ ����� ����������� �������!\n";
			}
			else {
				cout << "������� �������� �������: ";
				fillArray(mainArray, actualSize);
				isArrayFilled = true;
			}
			system("pause");
			break;
		case 2: // ���� ������ �������.
			if (!isArrayFilled) {
				cout << "������! ��������� ������ � ���������� �����\n";
			}
			else {
				cout << "������� ������� �����:";
				cin >> userDigit;
				foundIndex = findIndex(mainArray, actualSize, userDigit);
				if (foundIndex != -1) {
					cout << "������� ������: " << foundIndex << "\n";
				}
				else{
					cout << "������ �� ������� :(\n";
				}
			}
			system("pause");
			break;
		case 3: // ���� ������� ��������.
			if (!isArrayFilled) {
				cout << "������! ��������� ������ � ���������� �����\n";
			}
			else {
				cout << "������� �����, �� ������� ����� ����������� ����� ��������: ";
				cin >> userDigit;
				cout << "������� ��������, ������� ������ ��������: ";
				cin >> userElement;
				if (insertElement(mainArray, actualSize, userElement, userDigit) != -1) {
					cout << "������ �������.\n";
					actualSize += 1;
				}
				else {
					cout << "�� ��������� �������� ������ �� �������, ������ ��������� ������� :(\n";
				}
			}
			system("pause");
			break;
		case 4: //���� �������� ��������(��).
			if (!isArrayFilled) {
				cout << "������! ��������� ������ � ���������� �����\n";
			}
			else {
				cout << "������� �����, �� ������� ����� ����������� ����� ���������: ";
				cin >> userDigit;
				numDeletedElems = deleteElements(mainArray, actualSize, userDigit);
				if (numDeletedElems != 0) {
					if (numDeletedElems == actualSize) {
						cout << "����������� �������� ������ �������� ����.\n";
						actualSize -= numDeletedElems;
					}
					else {

						actualSize -= numDeletedElems;
						cout << "������ �������.\n";
					}
				}
				else {
					cout << "�� ��������� �������� ������ �� �������\n";
					"������ �������.\n";
				}
			}
			system("pause");
			break;
		case 0: // ���� ������.
			userChoice = 0;
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
			2) ����������� �������,
			3) ������ �������� "�������� �� ������?"
*/
void printMenu(long* array, int size, bool isFilled) { 
	system("cls");
	cout << "������������ ������ #1 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� 1 - ����������� ������\n"
		"================����================\n";
	if (isFilled && size != 0) {
		cout << "\n";
		printArray(array, size, isFilled);
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
void fillArray(long* array, int size) {
	for (int i = 0; i < size; i++) {
		cin >> array[i];
	}
}


/*
��������� ������ ������� � �������.
��������� - 1) ������, ������� ����� �������,
			2) ����������� �������,
			3) ������ �������� "�������� �� ������?".
*/
void printArray(long* array, int size, bool isFilled) {
	if (!isFilled) {
		cout << "������! ������ ����. ��������� ������ � ���������� �����.\n";
	}
	else {
		cout << "������� ������: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}
		cout << "\n";
	}
}


/*
������� ������ �������.
��������� - 1) ������, � ������� ������. �����,
			2) ����������� �������,
			3) ����� ��� ������.
����.���� - 1) ������, ���� ������,
			2) -1 ���� �� ������.
*/
int findIndex(long* array, int size, long digit) {
	for (int i = 0; i < size; i++){
		if (findHighestDigit(array[i]) == digit) {
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
			2) ������������ �������,
			3) ������� ��� �������,
			4) ����� ��� ������.
�����.���� - 1) 0, ���� ������� �������,
			 2) -1, ���� ������� �� �������.
*/
int insertElement(long* array, int size, long element, int digit) {
	int index = findIndex(array, size, digit);
	if (index != -1) {
		for (int i = size - 1; i >= index; i--) {
			array[i + 1] = array[i];
		}
		array[index] = element;
		return 0;
	}
	else {
		return -1;
	}
}

/*
������� �������� ��������(��) � �������.
��������� - 1) ������ ��� �������,
			2) ������������ �������,
			3) ����� ��� ������.
�����.���� - 1) ���-�� �������� ���������.
*/
int deleteElements(long* array, int size, int digit) {
	int deletedCounter = 0;
	for (int i = 0; i < size; i++){
		if (findHighestDigit(array[i]) == digit) {
			deletedCounter += 1;
			for (int k = i; k < size; k++) {
				array[k] = array[k + 1];
			}
			i -= 1;
		}
	}
	return deletedCounter;
}