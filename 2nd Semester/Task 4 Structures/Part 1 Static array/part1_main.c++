#include "Part1_Structures.h"
#include <iostream>
#include <string>
#include <locale>
#include <iomanip>
#include <windows.h>

using namespace std;

void printMenu(TechInspectTable& table, maxFieldsLen& maxLen);
void printTable(TechInspectTable& table, maxFieldsLen& maxLen);
TechInspectInfo createInfo(maxFieldsLen& maxLen);
void insertInfo(TechInspectInfo info, TechInspectTable& table);
size_t deleteInfo(TechInspectTable& table);
TechInspectTable createFilteredTable(TechInspectTable& table);


int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// ������� ����������
	TechInspectTable table{};
	TechInspectTable filteredTable{};

	//��������������� ����������
	size_t tempsize_t;

	//���������� ��� ������
	maxFieldsLen maxLen;

	//���������� ��� ����������������� �����.
	int userChoice = -1;

	while (userChoice != 0) { // ������� ����-����.
		system("cls");
		printMenu(table, maxLen);

		cin >> userChoice;
		cin.ignore();

		switch (userChoice) {
		case 1:
			cout << "������� ��������� ���������� � ���������� � �������\n";
			insertInfo(createInfo(maxLen), table);
			cout << "������ �������� � �������.\n";
			system("pause");
			break;

		case 2:
			cout << "������� �������� �� ������ ����������\n";
			tempsize_t = deleteInfo(table);
			if (tempsize_t != 0) {
				cout << "������� " << tempsize_t << " �����\n";
			}
			else {
				cout << "������� ��� �������� �� ���� �������\n";
			}
			system("pause");
			break;

		case 3:
			cout << "������� ������������ ������� �� ������ � �����\n";
			filteredTable = createFilteredTable(table);
			if (filteredTable.tableSize == 0) {
				cout << "�� ������� ������ �� ������� :(\n";
			}
			else {
				cout << "�� ������� �������:\n";
				printTable(filteredTable, maxLen);
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


//������� ������ ����
void printMenu(TechInspectTable& table, maxFieldsLen& maxLen) {
	cout << "������������ ������ #4 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� 4 - ���������. ���������� ������.\n"
		"================����================\n"
		"�������: ";

	printTable(table, maxLen);

	cout << endl;
	cout << "������� [1], ����� ������ ���������� � ���.�������.\n"
		"������� [2], ����� ������� �������� �� ���������� � �������� �������.\n"
		"������� [3], ����� ������������ ������ ����������� �� �������� ������ � �����.\n"
		"������� [0], ����� ��������� ������ ���������.\n";
	cout << "��� �����: ";
}


//������� ������ �������
void printTable(TechInspectTable& table, maxFieldsLen& maxLen) {
	if (table.tableSize != 0) {
		//��������� ��������� �������
		string tableHeader1 = "���.�����";
		string tableHeader2 = "������";
		string tableHeader3 = "����";
		string tableHeader4 = "���";
		string tableHeader5 = "�����";
		string tableHeader6 = "����";

		//���������� ����.���� � ������ ������ ������������ �����
		maxLen.model = max(maxLen.model, tableHeader2.length());
		maxLen.color = max(maxLen.color, tableHeader3.length());
		maxLen.name = max(maxLen.name + 1, tableHeader4.length());
		maxLen.adress = max(maxLen.adress, tableHeader5.length());

		//���������� ��� ������ �������
		size_t tableHeaderLen = tableHeader1.length() + tableHeader2.length() +
			tableHeader3.length() + tableHeader4.length() +
			tableHeader5.length() + tableHeader6.length() + 5;
		size_t horSepLen = tableHeaderLen + maxLen.adress + maxLen.name +
			maxLen.color + maxLen.model + maxLen.year;
		string VertSep = "|";

		//����� ���������
		cout << endl;
		cout << setw(horSepLen) << setfill('-') << "-" << endl;
		cout << setfill(' ');
		cout << VertSep << " " << left << tableHeader1 << "   ";
		cout << VertSep << " " << setw(maxLen.model) << left << tableHeader2 << " ";
		cout << VertSep << " " << setw(maxLen.color) << left << tableHeader3 << " ";
		cout << VertSep << " " << setw(maxLen.name) << left << tableHeader4 << " ";
		cout << VertSep << " " << setw(maxLen.adress) << left << tableHeader5 << " ";
		cout << VertSep << " " << setw(maxLen.year + 6) << tableHeader6 << " " << VertSep << endl;
		cout << setw(horSepLen) << setfill('-') << "-" << endl;
		cout << setfill(' ');

		//����� ���.����� �������
		for (size_t i = 0; i < table.tableSize; i++){

			//����� ������� ���� ������ �������
			cout << VertSep << setw(13) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.model + 2) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.color + 2) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.name + 2) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.adress + 2) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.year + 8) << setfill(' ') << " " << VertSep;
			cout << endl;

			//������� � �����������
			cout << VertSep << " " << setw(3) << right << table.infoList[i].carNumber.regionCode << " ";

			cout << table.infoList[i].carNumber.digits << " "
				 << table.infoList[i].carNumber.letters << " ";

			cout << VertSep << " " << setw(maxLen.model) << left << table.infoList[i].model << " ";

			cout << VertSep << " " << setw(maxLen.color) << left << table.infoList[i].color << " ";

			cout << VertSep << " " << setw(maxLen.name) << table.infoList[i].personInfo.surname
				+ " " + table.infoList[i].personInfo.name << " ";

			cout << VertSep << " " << setw(maxLen.adress) << table.infoList[i].personInfo.adress << " ";

			cout << VertSep << " " << table.infoList[i].date.day / 10 << table.infoList[i].date.day % 10 << "."
				 << table.infoList[i].date.month / 10 << table.infoList[i].date.month % 10 << "."
				 << setw(maxLen.year) << left << table.infoList[i].date.year << " " << VertSep << endl;

			//����� ������� ���� ����� �������
			cout << VertSep << setw(13) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.model + 2) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.color + 2) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.name + 2) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.adress + 2) << setfill(' ') << " ";
			cout << VertSep << setw(maxLen.year + 8) << setfill(' ') << " " << VertSep;
			cout << endl;

			cout << setw(horSepLen) << setfill('-') << "-" << endl;
			cout << setfill(' ');
		}
	}
	else {
		cout << "������� �����\n";
	}
}


//������� �������� ������ ��� ������� ����� ���� � ����������
TechInspectInfo createInfo(maxFieldsLen& maxLen) {
	TechInspectInfo newInfo{};

	cout << "������� ��� �������: ";
	getline(cin, newInfo.carNumber.regionCode);

	cout << "������� ����� ������: ";
	getline(cin, newInfo.carNumber.digits);

	cout << "������� ����� ������: ";
	getline(cin, newInfo.carNumber.letters);

	cout << "������� ������ ����������: ";
	getline(cin, newInfo.model);

	cout << "������� ���� ����������: ";
	getline(cin, newInfo.color);

	cout << "������� ������� ���������: ";
	getline(cin, newInfo.personInfo.surname);

	cout << "������� ��� ���������: ";
	getline(cin, newInfo.personInfo.name);

	cout << "������� ����� ���������: ";
	getline(cin, newInfo.personInfo.adress);

	cout << "������� ���� �������: ";
	cin >> newInfo.date.day;

	cout << "������� ����� �������: ";
	cin >> newInfo.date.month;

	cout << "������� ��� �������: ";
	cin >> newInfo.date.year;

	/*���������� ������������ ����� ����� � ������. �������*/
	maxLen.model = max(maxLen.model, newInfo.model.length());
	maxLen.color = max(maxLen.color, newInfo.color.length());
	maxLen.name = max(maxLen.name, newInfo.personInfo.surname.length() +
		newInfo.personInfo.name.length());
	maxLen.adress = max(maxLen.adress, newInfo.personInfo.adress.length());
	maxLen.year = max(maxLen.year, (size_t)log10(newInfo.date.year) + 1);

	return newInfo;
}


//������� ������� ������ � ������� � ����������� �� ����
void insertInfo(TechInspectInfo info, TechInspectTable& table) {
	/*���� ������ �� ������ - ����� ������� ��� �������
	� ��������������� �������*/
	if (table.tableSize != 0) {

		/*��������� ��, ��� ������� ������������� �� �����,
		� ������� �� ������ �������� �������� ���������������*/

		/*���� � ������� ��� ������ ������ ����� - ��������� � ������*/
		if (table.infoList[0].date.year > info.date.year) {
			/*�������� ��� ������� ������*/
			for (int i = table.tableSize - 1; i >= 0; i--) {
				table.infoList[i + 1] = table.infoList[i];
			}
			table.infoList[0] = info;
		}

		/*���� � ������� ��� ������ ������ ����� - ��������� � �����*/
		else if (table.infoList[table.tableSize - 1].date.year < info.date.year) {
			table.infoList[table.tableSize] = info;
		}

		/*���� ����� �� else - � ������� ���� ������ ��� � �������� ������,
		��� � �� �������� . ������������ �����, ���� �������� ����� ������, �
		������ � ������� ����� ��������� ������*/
		else {
			//����� ������� ��� ��������������� �������
			int i = 0;
			while (table.infoList[i].date.year < info.date.year && i < table.tableSize){
				i++;
			}
			while (table.infoList[i].date.month < info.date.month &&
				table.infoList[i].date.year == info.date.year &&
				i < table.tableSize) {
				i++;
			}
			while (table.infoList[i].date.day < info.date.day &&
				table.infoList[i].date.month == info.date.month &&
				table.infoList[i].date.year == info.date.year &&
				i < table.tableSize) {
				i++;
			}
			/*�������� ������ ����� �������
			��� ������������ ����� ��� ������ ��������*/
			for (int j = table.tableSize - 1; j >= i; j--) {
				table.infoList[j + 1] = table.infoList[j];
			}
			table.infoList[i] = info;
		}
	}
	/*������ ������ - ��������� � ������ �������*/
	else {
		table.infoList[table.tableSize] = info;
	}
	table.tableSize++;
}


/*������� �������� ����� �� �������� ���������
���������� ���-�� �������� ���������*/
size_t deleteInfo(TechInspectTable& table) {
	string rC, d, l;
	cout << "������� ��� �������: ";
	getline(cin, rC);
	cout << "������� ����� ������: ";
	getline(cin, d);
	cout << "������� ����� ������: ";
	getline(cin, l);
	size_t deletedCounter = 0;
	for (size_t i = 0; i < table.tableSize; i++){
		if (table.infoList[i].carNumber.regionCode == rC &&
			table.infoList[i].carNumber.digits == d &&
			table.infoList[i].carNumber.letters == l) {
			/*����� ������� �����, ����� ����� ��������� ������
			����������� �������, ������� ���������� �������*/
			for (size_t j = i; j < table.tableSize - 1; j++) {
				table.infoList[j] = table.infoList[j + 1];
			}
			i--;
			table.tableSize--;
			deletedCounter++;
		}
	}
	return deletedCounter;
}


//������� �������� ��������������� ������� �� ��������
TechInspectTable createFilteredTable(TechInspectTable& table) {
	TechInspectTable filteredTable{};
	string m, c;
	cout << "������� ������ ����������: ";
	getline(cin, m);
	cout << "������� ���� ����������: ";
	getline(cin, c);

	for (size_t i = 0; i < table.tableSize; i++) {
		if (table.infoList[i].model == m &&
			table.infoList[i].color == c) {
			filteredTable.infoList[filteredTable.tableSize] = table.infoList[i];
			filteredTable.tableSize++;
		}
	}
	return filteredTable;
}			