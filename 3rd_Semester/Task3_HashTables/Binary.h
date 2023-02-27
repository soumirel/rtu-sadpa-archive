#pragma once

#include "Hash.h"
#include <fstream>
#include <istream>

using namespace std;

bool isFileExist(string fileName)
{
	ifstream file;
	file.open(fileName);
	char a[3];
	return file.good();
}


bool tryOpenFile(string fileName, char type)
{
	ifstream file;
	if (type == 't')
		file.open(fileName);
	if (type == 'b')
		file.open(fileName, ios::binary);
	if (file.is_open())
	{
		if (!file.good())
		{
			cout << "Ошибка с файлом " << fileName << '\n';
		}
		file.close();
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}


void printBinFile(string binFileName)
{
	ifstream binFile;
	binFile.open(binFileName, ios::in | ios::binary);
	HashTableCell cell;
	binFile.read((char*)&cell, sizeof(cell));
	cout << "Содержимое бинарного файла:\n";
	while (!binFile.eof())
	{
		cout << cell.selfIndexInBinaryFile << " "
			<< cell.key_date << " " << cell.name << '\n';
		binFile.read((char*)&cell, sizeof(cell));
	}
	binFile.close();
}


char* getRecordByNumber(string binFileName, int number)
{
	ifstream binFile;
	binFile.open(binFileName, ios::in | ios::binary);
	HashTableCell cell;
	binFile.seekg(sizeof(HashTableCell) * (number), ios::beg);
	binFile.read((char*)&cell, sizeof(HashTableCell));
	binFile.close();
	char name[8];
	strcpy_s(name, cell.name);
	return name;
}


bool deleteRecordByKey(string binFileName, const char* recordKey)
{
	HashTableCell lastRecord;
	fstream binFile;

	binFile.open(binFileName, ios::in | ios::out | ios::binary);
	binFile.seekg(-(int)sizeof(HashTableCell), ios::end);
	binFile.read((char*)&lastRecord, sizeof(HashTableCell));

	binFile.seekg(0, ios::beg);
	HashTableCell currentRecord;
	while (binFile.good())
	{
		binFile.read((char*)&currentRecord, sizeof(HashTableCell));
		if (strcmp(currentRecord.key_date, recordKey) == 0)
		{
			lastRecord.selfIndexInBinaryFile = currentRecord.selfIndexInBinaryFile;
			lastRecord.isCellDeleted = true;
			binFile.seekg(-(int)sizeof(HashTableCell), ios::cur);
			binFile.write(reinterpret_cast<const char*>(&lastRecord),
				sizeof(HashTableCell));
			binFile.close();
			return true;
		}
	}
	binFile.close();
	return false;
}



void addRecord(string binFileName, const char* date, const char* name, int recordsAmount)
{
	ofstream binFile;
	binFile.open(binFileName, ios::out | ios::binary | std::ios::app);
	HashTableCell* cell = new HashTableCell(date, name, recordsAmount);
	cell->isAddressOpen = false;
	binFile.write((char*)cell, sizeof(HashTableCell));
}


void printFriendCell(HashTableCell cell)
{
	cout << cell.key_date << " день рождения у " << cell.name << '\n';
}


void generateBinFile(string binFileName, int recordsAmount)
{
	ofstream binFile;
	binFile.open(binFileName, ios::out | ios::binary);

	HashTableCell* currentCell = new HashTableCell();
	for (int i = 0; i < recordsAmount; i++)
	{
		int day = getRandomInt(1, 30);
		int month = getRandomInt(1, 12);
		string key_date;
		if (day > 9)
		{
			key_date += to_string(day);
		}
		else
		{
			key_date += '0' + to_string(day);
		}
		key_date += '.';
		if (month > 9)
		{
			key_date += to_string(month);
		}
		else
		{
			key_date += '0' + to_string(month);
		}
		strcpy_s(currentCell->key_date, key_date.c_str());
		string name = names.at(getRandomInt(0, names.size() - 1)) +
			" " + surnames.at(getRandomInt(0, surnames.size() - 1));
		strcpy_s(currentCell->name, name.c_str());
		currentCell->selfIndexInBinaryFile = i;
		binFile.write((char*)currentCell, sizeof(HashTableCell));
	}
	binFile.close();
}
