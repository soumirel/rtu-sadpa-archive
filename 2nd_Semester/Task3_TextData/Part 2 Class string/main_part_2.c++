#include <iostream>
#include <string>
#include <clocale>
#include <algorithm>

using namespace std;

void printMenu(string origStr, string answStr);
string insertionSort(string str);
string findLetters(string word);
string createAnswerString(string originaString);
string getUserString();

int main() {
	setlocale(LC_ALL, "Russian");

	// ������� ����������
	string userString = "";

	// ��������� ����������
	string answerString = "";

	//���������� ��� ����������������� �����.
	int userChoice = -1;

	while (userChoice != 0) { // ������� ����-����.
		system("cls");
		printMenu(userString, answerString);
		cin >> userChoice;
		switch (userChoice) {
		case 1:
			cout << "������� ������ �� ����, ���������������� ������ ������ ������� � �������.\n";
			userString = getUserString();
			answerString = createAnswerString(userString);
			system("pause");
			break;
		case 2:
			cout << "������ ����� ������� ����� �����������.\n";
			userString = "";
			answerString = "";
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


void printMenu(string origStr, string answStr) {
	cout << "������������ ������ #3 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� 2 - String ������\n"
		"================����================\n";
	cout << "�������� ������: ";
	if (origStr.length() != 0) cout << origStr << endl;
	else cout << "�� �������\n";
	cout << "������, ������������ �� �������: ";
	if (answStr.length() != 0) cout << answStr << endl;
	else cout << " �� ����� ���� ��������\n";
	cout << "====================================\n";
	cout << "�������, �����: \n"
		"1) ������ ������.\n"
		"2) �������� ������.\n"
		"3) �����.\n"
		"��� �����: ";
}


string insertionSort(string str) {
	for (int i = 1; i < str.length(); i++) {
		int j = i - 1;
		while (j >= 0 && str[j] > str[j + 1]) {
			swap(str[j], str[j + 1]);
			j--;
		}
	}
	return str;
}


string getUserString() {
	string userString;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, userString);
	return userString;
}


string findLetters(string word) {
	std::transform(word.begin(), word.end(), word.begin(), toupper);
	string letters = "";
	while (word.find_first_not_of(letters) != string::npos) {
		letters.push_back(word[word.find_first_not_of(letters)]);
	}
	letters = insertionSort(letters);
	return letters;
}


string createAnswerString(string originaString) {
	while (originaString[0] == ' ' || originaString[0] == ',') {
		originaString.erase(0, 1);
	}

	string tempWord = "";

	string firstWord;
	firstWord = originaString.substr(0, originaString.find_first_of(" "));
	originaString.erase(0, originaString.find_first_of(" "));
	string lettersOfFirstWord = findLetters(firstWord);

	string wordsBeforeFirst = "";
	string wordsAfterFirst = "";

	for (unsigned i = originaString.find_first_not_of(" "); i < originaString.length();) {
		tempWord = originaString.substr(i, originaString.find_first_of(" ", i) - i);
		if (tempWord[tempWord.length() - 1] == ',') {
			tempWord.pop_back();
			if (wordsAfterFirst[wordsAfterFirst.length() - 1] == ' ') {
				wordsAfterFirst.pop_back();
			}
			wordsAfterFirst += ", ";
		}
		if (findLetters(tempWord) == lettersOfFirstWord) {
			wordsBeforeFirst += tempWord + ' ';
		}
		else {
			wordsAfterFirst += tempWord + ' ';
		}
		originaString.erase(i, originaString.find_first_of(" ", i) - i);
		i = originaString.find_first_not_of(" ");
	}
	firstWord += ' ';
	string answerString = wordsBeforeFirst + firstWord + wordsAfterFirst;
	return answerString;
}