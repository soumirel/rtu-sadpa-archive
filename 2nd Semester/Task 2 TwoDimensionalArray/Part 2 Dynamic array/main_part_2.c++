#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

using namespace std;
const int maxRows = 100;
const int maxColumns = 100;

void printMenu(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, bool f1, bool f2, bool f3);
void arrFillingHub(double** arr, int rows, int columns, bool* filledSignal);
int correctInputSizes();
void fillArray(double** array, int rows, int columns, int generateType);
double getRandomNumber();
void randomFilling(double** array, int rows, int columns);
void keyboardFilling(double** array, int rows, int columns);
void printArrays(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, bool f1, bool f2, bool f3);
double findMaxNumInArrRow(double** array, int columns, int rowNumber);
double findD(double** array, int rows, int cols);
void sumOfArrs(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, double** sA, int rows, int cols);
double findSolution(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, bool f1, bool f2, bool f3, double** sA, int rS, int cS);
void printSpecialArr(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, double** sA, int rS, int cS, bool f1, bool f2, bool f3);




int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	// ������� ����������
	double** arrayA = 0;
	int aRows = 0, aCols = 0;
	double** arrayB = 0;
	int bRows = 0, bCols = 0;
	double** arrayC = 0;
	int cRows = 0, cCols = 0;

	//���������� ��� ����������������� �����.
	int userChoice = -1;

	// ��������� ����������
	double solution;
	double** specialArray = nullptr;
	int specRows, specCols;
	bool is_specArr_filled = false;
	bool is_ArrA_Filled = false;
	bool is_ArrB_Filled = false;
	bool is_ArrC_Filled = false;

	while (userChoice != 0) { // ������� ����-����.
		system("cls");
		printMenu(arrayA, arrayB, arrayC, aRows, aCols, bRows, bCols, cRows, cCols, is_ArrA_Filled, is_ArrB_Filled, is_ArrC_Filled);
		cin >> userChoice;
		switch (userChoice) {
		case 1:  // ���������� 1�� �������
			if (is_ArrA_Filled) {
				for (int i = 0; i < aRows; i++) {
					delete arrayA[i];
				}
				delete arrayA;
			}
			cout << " === ���������� 1�� ������� ===\n"
				"������� ������ ������� � ������� MxN,"
				"��� M - ��� - �� �����, N - ��� - �� ��������\n";
			cout << "�����: ";
			aRows = correctInputSizes();
			cout << "��������: ";
			aCols = correctInputSizes();
			arrayA = new double* [aRows];
			for (int i = 0; i < aRows; i++) {
				arrayA[i] = new double[aCols];
			}
			arrFillingHub(arrayA, aRows, aCols, &is_ArrA_Filled);
			system("pause");
			break;
		case 2:  // ���������� 2�� �������
			if (is_ArrB_Filled) {
				for (int i = 0; i < bRows; i++) {
					delete arrayB[i];
				}
				delete arrayB;
			}
			cout << " === ���������� 2�� ������� ===\n"
				"������� ������ ������� � ������� MxN,"
				"��� M - ��� - �� �����, N - ��� - �� ��������\n";
			cout << "�����: ";
			bRows = correctInputSizes();
			cout << "��������: ";
			bCols = correctInputSizes();
			arrayB = new double* [bRows];
			for (int i = 0; i < bRows; i++) {
				arrayB[i] = new double[bCols];
			}
			arrFillingHub(arrayB, bRows, bCols, &is_ArrB_Filled);
			system("pause");
			break;
		case 3:  // ���������� 3�� �������
			if (is_ArrC_Filled) {
				for (int i = 0; i < cRows; i++) {
					delete arrayC[i];
				}
				delete arrayC;
			}
			cout << " === ���������� 3�� ������� ===\n"
				"������� ������ ������� � ������� MxN,"
				"��� M - ��� - �� �����, N - ��� - �� ��������\n";
			cout << "�����: ";
			cRows = correctInputSizes();
			cout << "��������: ";
			cCols = correctInputSizes();
			arrayC = new double* [cRows];
			for (int i = 0; i < cRows; i++) {
				arrayC[i] = new double[cCols];
			}
			arrFillingHub(arrayC, cRows, cCols, &is_ArrC_Filled);
			system("pause");
			break;
		case 4:
			if (is_ArrA_Filled && is_ArrB_Filled && is_ArrC_Filled) {
				specRows = max(aRows, bRows);
				specRows = max(specRows, cRows);
				specCols = max(aCols, bCols);
				specCols = max(specCols, cCols);
			}
			if (!is_specArr_filled) {
				specialArray = new double* [specRows];
				for (int i = 0; i < specRows; i++) {
					specialArray[i] = new double[specCols];
				}
				is_specArr_filled = true;
			}
			else {
				for (int i = 0; i < specRows; i++) {
					delete specialArray[i];
				}
				delete specialArray;
				specialArray = new double* [specRows];
				for (int i = 0; i < specRows; i++) {
					specialArray[i] = new double[specCols];
				}
			}
			printSpecialArr(arrayA, arrayB, arrayC, aRows, aCols, bRows,
				bCols, cRows, cCols, specialArray, specRows, specCols, is_ArrA_Filled, is_ArrB_Filled, is_ArrC_Filled);
			system("pause");
			break;
		case 5:
			if (is_ArrA_Filled && is_ArrB_Filled && is_ArrC_Filled) {
				specRows = max(aRows, bRows);
				specRows = max(specRows, cRows);
				specCols = max(aCols, bCols);
				specCols = max(specCols, cCols);
				if (!is_specArr_filled) {
					specialArray = new double* [specRows];
					for (int i = 0; i < specRows; i++) {
						specialArray[i] = new double[specCols];
					}
					is_specArr_filled = true;
				}
				else {
					for (int i = 0; i < specRows; i++) {
						delete specialArray[i];
					}
					delete specialArray;
					specialArray = new double* [specRows];
					for (int i = 0; i < specRows; i++) {
						specialArray[i] = new double[specCols];
					}
				}
				solution = findSolution(arrayA, arrayB, arrayC, aRows,
					aCols, bRows, bCols, cRows, cCols,
					is_ArrA_Filled, is_ArrB_Filled, is_ArrC_Filled,
					specialArray, specRows, specCols);
				if (solution != -1) {
					cout << "��������� ����: (|A| + |B| + |C|)/|A + B + C|)\n"
						"��� |D| = max(������ ������) + max(������ ������) + ... + max(n-�� ������)\n"
						" ����� " << solution << "\n";
				}
			}
			else {
				cout << "������! ��������� ��� �������.\n";
			}
			system("pause");
			break;
		case 0:
			cout << "�� ��������!\n";
			userChoice = 0;
			system("pause");
			break;
		default:
			cout << "� �� ������� ���, ��������� ����\n";
			cin.clear();
			system("pause");
			break;
		}
	}
	return 0;
}


void printMenu(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, bool f1, bool f2, bool f3) {
	cout << "������������ ������ #2 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� 1 - ������������ ������\n"
		"================����================\n";
	if (f1 || f2 || f3) {
		cout << "\n";
		printArrays(a1, a2, a3, r1, c1, r2, c2, r3, c3, f1, f2, f3);
		cout << "\n";
	}
	else {
		cout << "\n������� �����\n\n";
	}
	cout << "1) ��������� ������� 1 \n"
		"2) ��������� ������� 2.\n"
		"3) ��������� ������� 3.\n"
		"4) ������� ����� ��� ������.\n"
		"5) ���������� �������� ��������� (|A| + |B| + |C|)/|A + B + C)\n"
		"��� |D| = max(������ ������) + max(������ ������) + ... + max(n-�� ������)\n"
		"0) �����.\n"
		"��� �����: ";
}


void arrFillingHub(double** arr, int rows, int columns, bool* filledSignal) {
	int typeOfFilling;
	cout << "�������� ��� ����������:\n"
		"������� 1, ����� ��������� ������ ����. �������,\n"
		"������� 2, ����� ��������� ������� � ����������.\n"
		"��� �����: ";
	cin >> typeOfFilling;
	if (typeOfFilling == 1 || typeOfFilling == 2) {
		fillArray(arr, rows, columns, typeOfFilling);
		*filledSignal = true;
	}
	else {
		cout << "������! ���������� ����: 1 ��� 2.\n";
	}
}


int correctInputSizes() {
	int inputValue;
	while (!(cin >> inputValue) || inputValue > 1000 || inputValue < 1) {
		cout << "������! �� �������� ���������� ����. ������� ��������� ��������: \n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return inputValue;
}


void fillArray(double** array, int rows, int columns, int generateType) {
	if (generateType == 1) {
		randomFilling(array, rows, columns);
	}
	else {
		cout << "������� " << rows * columns << " �����: ";
		keyboardFilling(array, rows, columns);
	}
}


double getRandomNumber() {
	return (rand() / 100.0);
}


void randomFilling(double** array, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			array[i][j] = getRandomNumber();
		}
	}
}


void keyboardFilling(double** array, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cin >> array[i][j];
		}
	}
}


void printArrays(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, bool f1, bool f2, bool f3) {
	int maxRows = max(r1, max(r2, r3));
	int maxCols = max(c1, max(c2, c3));
	for (int i = -1; i < maxRows + 1; i++) {
		for (int j = 0; j <= 3 * maxCols + 1; j++) {
			if (i == -1 || i == maxRows) {
				cout << setw(7) << setfill('-') << "-";
			}
			else {
				cout << setfill(' ');
				if (j < maxCols) {
					if (j < c1 && f1 && i < r1) {
						cout << setw(7) << a1[i][j] << " ";
					}
					else {
						cout << setw(7) << "*" << " ";
					}
				}
				if (j == maxCols) {
					cout << "|";
				}
				if (j > maxCols && j <= 2 * maxCols) {
					if (j - (maxCols + 1) <= c2 - 1 && f2 && i < r2) {
						cout << setw(7) << a2[i][j - (maxCols + 1)] << " ";
					}
					else {
						cout << setw(7) << "*" << " ";
					}
				}
				if (j == 2 * maxCols + 1) {
					cout << "|";
				}
				if (j > 2 * maxCols + 1) {
					if (j - (2 * maxCols + 2) <= c3 - 1 && f3 && i < r3) {
						cout << setw(7) << a3[i][j - (2 * maxCols + 2)] << " ";
					}
					else {
						cout << setw(7) << "*" << " ";
					}
				}
			}

		}
		cout << "\n";
	}
}


double findMaxNumInArrRow(double** array, int columns, int rowNumber) {
	int maxNumber = 0;
	for (int i = 0; i < columns; i++) {
		if (maxNumber < array[rowNumber][i]) {
			maxNumber = array[rowNumber][i];
		}
	}
	return maxNumber;
}


double findD(double** array, int rows, int cols) {
	int D = 0;
	for (int i = 0; i < rows; i++) {
		D += findMaxNumInArrRow(array, cols, i);
	}
	return D;
}


void sumOfArrs(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, double** sA, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sA[i][j] = 0;
		}
	}
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			sA[i][j] += a1[i][j];
		}
	}
	for (int i = 0; i < r2; i++) {
		for (int j = 0; j < c2; j++) {
			sA[i][j] += a2[i][j];
		}
	}
	for (int i = 0; i < r3; i++) {
		for (int j = 0; j < c3; j++) {
			sA[i][j] += a3[i][j];
		}
	}
}


double findSolution(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, bool f1, bool f2, bool f3, double** sA, int rS, int cS) {
	double solution = -1;
	if (f1 && f2 && f3) {
		sumOfArrs(a1, a2, a3, r1, c1, r2, c2, r3, c3, sA, rS, cS);
		double numerator = 0, denominator = 0;
		numerator += findD(a1, r1, c1) + findD(a2, r2, c2) + findD(a3, r3, c3);
		denominator = findD(sA, rS, cS);
		solution = numerator / denominator;
		return solution;
	}
	else {
		return solution;
	}
}


void printSpecialArr(double** a1, double** a2, double** a3,
	int r1, int c1, int r2, int c2, int r3, int c3, double** sA, int rS, int cS, bool f1, bool f2, bool f3) {
	if (f1 && f2 && f3) {
		cout << "����� ��� ��������:\n";
		sumOfArrs(a1, a2, a3, r1, c1, r2, c2, r3, c3, sA, rS, cS);
		for (int i = 0; i < rS; i++) {
			for (int j = 0; j < cS; j++) {
				cout << setw(7) << setfill(' ') << sA[i][j] << " ";
			}
			cout << setfill(' ') << "\n";
		}
	}
	else {
		cout << "���������� ����� �����. �� ��� ������� ���������.\n";
	}
}