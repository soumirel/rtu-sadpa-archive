#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


int hashFunction(const char key[6], unsigned tableSize);


struct HashTableCell
{
	char key_date[6];
	char name[8];
	int selfIndexInBinaryFile;
	bool isAddressOpen;
	bool isCellDeleted;

	HashTableCell(const char* key_date, const char* name, int index = -1)
	{
		strcpy_s(this->key_date, key_date);
		strcpy_s(this->name, name);
		selfIndexInBinaryFile = index;
		isAddressOpen = true;
		isCellDeleted = false;
	}

	HashTableCell()
	{
		key_date[5] = '\0';
		name[5] = '\0';
		selfIndexInBinaryFile = -1;
		isAddressOpen = true;
		isCellDeleted = false;
	}
};

struct HashTable
{
private:
	unsigned size = 5;
	unsigned closedAddressesAmount;
	HashTableCell* table;

	void resizeTable();

public:

	HashTable(unsigned size);

	unsigned getSize();

	char* get(const char* key);

	int getRecordNumber(const char* key);

	void add(const char* key, const char* value, int indexInFile);

	void add(HashTableCell* cell);

	void remove(const char* key);

	void printTable();
};


HashTable::HashTable(unsigned size = 5)
{
	this->size = size;
	closedAddressesAmount = 0;
	table = new HashTableCell[size];
}

unsigned HashTable::getSize()
{
	return size;
}


char* HashTable::get(const char* key)
{
	int startIndex = hashFunction(key, size);
	int index = startIndex;
	while (strcmp(table[index].key_date, key) != 0)
	{
		index++;
		index %= size;
		if (startIndex == index)
		{
			break;
		}
	}
	if (table[index].isAddressOpen == false
		&& table[index].isCellDeleted == false
		&& strcmp(table[index].key_date, key) == 0)
	{
		return table[index].name;
	}
	else
	{
		throw std::invalid_argument("Ничего не найдено\n");
	}
}


int HashTable::getRecordNumber(const char* key)
{
	int startIndex = hashFunction(key, size);
	int index = startIndex;
	while (strcmp(table[index].key_date, key) != 0 &&
		table[index].isAddressOpen == false || 
		(strcmp(table[index].key_date, key) == 0 && table[index].isCellDeleted == true))
	{
		index++;
		index %= size;
		if (startIndex == index)
		{
			break;
		}
	}
	if (table[index].isAddressOpen == false
		&& table[index].isCellDeleted == false
		&& strcmp(table[index].key_date, key) == 0)
	{
		return table[index].selfIndexInBinaryFile;
	}
	else
	{
		throw std::invalid_argument("Ничего не найдено\n");
	}
}


void HashTable::add(HashTableCell* cell)
{
	this->add(cell->key_date, cell->name, cell->selfIndexInBinaryFile);
}


void HashTable::add(const char* key, const char* value, int indexInFile)
{
	int startIndex = hashFunction(key, size);
	int index = startIndex;
	bool collisionMessage = false;
	while (table[index].isAddressOpen == false)
	{
		if (!collisionMessage)
		{
			cout << "\nПроизошла коллизия.\n";
			collisionMessage = true;
		}
		index++;
		if (index >= size)
		{
			index %= size;
		}
		if (startIndex == index)
		{
			break;
		}
	}

	if (collisionMessage)
	{
		cout << "Коллизия устранена с индекса " << startIndex << '\n';
	}

	strcpy_s(table[index].key_date, key);
	strcpy_s(table[index].name, value);
	table[index].isAddressOpen = false;
	table[index].selfIndexInBinaryFile = indexInFile;

	closedAddressesAmount++;

	cout << "Элемент {" << key << ":" << value << "} вставлен по индексу " << index << '\n';

	if ((closedAddressesAmount / (double)size) > 0.75)
	{
		cout << "\nКоэфициент нагруженности привысил 0.75.\n"
			"Произведено увеличение таблицы вдвое,"
			"произведено рехэширование\n\n"
			"Логи при прихэшировании:\n";
		closedAddressesAmount = 0;
		this->resizeTable();
		cout << '\n';
		
	}
}


void HashTable::remove(const char* key)
{
	int startIndex = hashFunction(key, size);
	int index = startIndex;
	while (strcmp(table[index].key_date, key) != 0 &&
		table[index].isAddressOpen == false)
	{
		index++;
		index %= size;
		if (startIndex == index)
		{
			break;
		}
	}
	if (strcmp(table[index].key_date, key) == 0 &&
		table[index].isCellDeleted == false)
	{
		table[index].isCellDeleted = true;

		cout << "Элемент {" << key << ":" << table[index].name << "} удалён с индекса " << index << '\n';
	}
	else
	{
		throw std::invalid_argument("Ничего не найдено\n");
	}
}


void HashTable::resizeTable()
{
	unsigned newSize = size * 2;
	HashTableCell* newTable = new HashTableCell[newSize];

	for (int i = 0; i < size; i++)
	{
		if (table[i].isCellDeleted == false && table[i].isAddressOpen == false)
		{
			int index = hashFunction(table[i].key_date, newSize);
			while (newTable[index].isAddressOpen == false)
			{
				index++;
				index %= newSize;
			}
			strcpy_s(newTable[index].key_date, table[i].key_date);
			strcpy_s(newTable[index].name, table[i].name);
			newTable[index].isAddressOpen = false;
			newTable[index].selfIndexInBinaryFile =
				table[i].selfIndexInBinaryFile;
			closedAddressesAmount++;
		}
	}
	delete[] table;
	table = newTable;
	size = newSize;
}

void HashTable::printTable()
{
	int indexFieldSize = to_string(size).length();
	int fileIndexFiledSize = to_string(closedAddressesAmount).length();
	string horizontalDelimeter = "";
	for (int i = 0; i < indexFieldSize + fileIndexFiledSize + 25; i++)
	{
		horizontalDelimeter += "=";
	}

	cout << horizontalDelimeter << '\n';
	for (int i = 0; i < size; i++)
	{
		cout << "| " << setw(indexFieldSize)
			<< i << " | ";
		if (table[i].isAddressOpen != true && table[i].isCellDeleted != true)
		{
			cout << table[i].key_date << " | "
				<< table[i].name << " | "
				<< setw(fileIndexFiledSize)
				<< table[i].selfIndexInBinaryFile;
		}
		else
		{
			cout << setw(5) << "" << " | " 
				<< setw(7) << "" << " | "
				<< setw(fileIndexFiledSize) << "";
		}
		cout << " |" << '\n' << horizontalDelimeter << '\n';
	}
}


int hashFunction(const char key[6], unsigned tableSize)
{
	int day = (key[0] - '0') * 10 + (key[1] - '0');
	int month = (key[3] - '0') * 10 + (key[4] - '0');
	int hashed = abs(sin(day) + cos(month)) * 10000 / 1;
	return hashed % tableSize;
}


vector<string> names
{
	"Вася", "Петя", "Гоша", "Дима", "Саша",
	"Лиза", "Анна", "Лена", "Крис", "Маня"
};
vector<string> surnames
{
	"П.", "Ж.", "А.", "Г.", "Д.", "П.", "Н."
};


int getRandomInt(int left, int right)
{
	return left + rand() % (right - left + 1);
}


HashTable* generateTable(int recordsAmount, int startSize)
{
	HashTable* newTable = new HashTable(startSize);
	for (int i = 0; i < recordsAmount; i++)
	{
		int day = getRandomInt(1, 30);
		int month = getRandomInt(1, 12);
		string date;
		if (day > 9)
		{
			date += to_string(day);
		}
		else
		{
			date += '0' + to_string(day);
		}
		date += '.';
		if (month > 9)
		{
			date += to_string(month);
		}
		else
		{
			date += '0' + to_string(month);
		}
		string name = names.at(getRandomInt(0, names.size() - 1)) +
			" " + surnames.at(getRandomInt(0, surnames.size() - 1));
		newTable->add(date.c_str(), name.c_str(), i);
	}
	return newTable;
}

