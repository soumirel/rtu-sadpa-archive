#pragma once

#include "Hash.h"
#include "Binary.h"


void synchronizeTableWithFile(string binFileName, HashTable* table)
{
	ifstream binFile;
	binFile.open(binFileName, ios::in | ios::binary);
	HashTableCell* cell = new HashTableCell();
	binFile.seekg(0, ios::beg);

	binFile.read((char*)cell, sizeof(HashTableCell));
	while (!binFile.eof())
	{
		table->add(cell);
		binFile.read((char*)cell, sizeof(HashTableCell));
	}
	binFile.close();
}


void deleteRecordByKeyInBoth(string binFileName, HashTable* table, const char* recordKey)
{
	deleteRecordByKey(binFileName, recordKey);
	table->remove(recordKey);
}


char* getRecord(string binFileName, HashTable* table, const char* recordKey)
{
	int number = table->getRecordNumber(recordKey);
	char* record = getRecordByNumber(binFileName, number);
	char result[8];
	strcpy_s(result, record);
	return result;
}