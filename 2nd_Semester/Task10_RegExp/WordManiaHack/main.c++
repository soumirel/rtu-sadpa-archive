// ������ �������� ���� - ����������������
#include "Trie.h"
#include "StringEncoder.h"

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

void printMenu();
void wordsManiaTraversal(size_t trieCell, size_t currentPosition, bool checkedCells[], string gamefield, string resultWord);
void WordsmaniaCheat(string& gamefield);
bool stringComparator(string firstS, string secondS);
void printHackResult();


Trie mainTrie;
StringEncoder encoder;
set<string> Res;
vector<string> Output;

int main()
{
	setlocale(LC_ALL, "Russian");
	mainTrie.loadDictionary("Dictonary.txt");

	// ������� ����������
	string gamefield = "";

	//���������� ��� ����������������� ������.
	int userMenuChoice = -1;
	

	// ������� ����-����.
	while (userMenuChoice != 0)
	{
		system("cls");
		printMenu();

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice)
		{
		case 1:
			cout << "������� ������� ���� � ������� (16 ��������): ";
			cin >> gamefield;
			encoder.encodeString(gamefield, encoder.ConsoleSample);
			WordsmaniaCheat(gamefield);
			printHackResult();
			system("pause");
			break;

		case 0:
			cout << "\n�� ��������!\n";
			userMenuChoice = 0;

			cout << '\n';
			system("pause");
			break;

		default:
			cout << "\n� �� ������� ���.\n";
			cin.clear();

			cout << '\n';
			system("pause");
			break;
		}
	}

	return 0;
}


void printMenu()
{
	cout << "������������ ������ #10 ����-03-21 ������� �.�. ������� 17\n\n"
		"������� - ���������� ���������.\n"
		"~~~~~~~~~~~~~~~~~����~~~~~~~~~~~~~~~\n";

	cout << "\n������� [1], ����� ��������� ��� ��� ���� ����������\n"
		"������� [0], ����� ��������� ������ ���������.\n";
	cout << "\n��� �����: ";
}


void wordsManiaTraversal(size_t trieCell, size_t currentPosition, bool checkedCells[], string gamefield, string resultWord)
{
	bool bannedWays[11] = { false };

	for (int i = -2; i <= 2; i += 2)
	{
		bannedWays[i + 5] = true;
	}

	if (currentPosition % 4 == 0)
	{
		for (int i = -5; i <= 3; i += 4)
		{
			bannedWays[i + 5] = true;
		}
	}

	if (currentPosition < 4)
	{
		for (int i = -5; i <= -3; i++)
		{
			bannedWays[i + 5] = true;
		}
	}

	if (currentPosition % 4 == 3)
	{
		for (int i = -3; i <= 5; i += 4)
		{
			bannedWays[i + 5] = true;
		}
	}

	if (currentPosition >= 12)
	{
		for (int i = 3; i <= 5; i++)
		{
			bannedWays[i + 5] = true;
		}
	}

	for (int i = -5; i <= 5; i++) 
	{
		if (bannedWays[i + 5])
		{
			continue;
		}

		int nextPosition = currentPosition + i;

		if (!checkedCells[nextPosition]) 
		{
			if (mainTrie.trie[trieCell].child[gamefield[nextPosition]] != 0) 
			{
				checkedCells[nextPosition] = true;

				wordsManiaTraversal(mainTrie.trie[trieCell].child[gamefield[nextPosition]],
					nextPosition, checkedCells, gamefield, resultWord + gamefield[nextPosition]);

				checkedCells[nextPosition] = false;
			}
		}

		if (mainTrie.trie[trieCell].isLeaf) 
		{
			Res.insert(resultWord);
		}
	}
}


void WordsmaniaCheat(string& gamefield)
{
	bool checkedCells[16] = { false };
	for (size_t i = 0; i < 16; i++) 
	{
		if (mainTrie.trie[0].child[gamefield[i]] != 0)
		{
			checkedCells[i] = true;
			wordsManiaTraversal(mainTrie.trie[0].child[gamefield[i]], i,
				checkedCells, gamefield, gamefield.substr(i, 1));
			checkedCells[i] = false;
		}
	}
}


void printHackResult()
{
	cout << "��� ����� �� ������ ������� ����:\n";

	for (auto& token : Res) 
	{
		Output.push_back(token);
	}
	Res.clear();

	sort(Output.begin(), Output.end(), stringComparator);
	size_t tokenIterator = 0;
	for (auto& token : Output) 
	{
		cout << ++tokenIterator << ". ";
		for (auto& tokenOfToken : token)
		{
			cout << encoder.FstreamSample[tokenOfToken];
		}
		cout << endl;
	}
	Output.clear();
}


bool stringComparator(string firstS, string secondS)
{
	if (firstS.size() >= secondS.size()) 
	{
		return false;
	}
	else
	{
		return true;
	}
}