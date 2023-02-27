#pragma once

#include "Hash.h"
#include "Binary.h"
#include "HashBinary.h"

void testHeshT()
{
	unsigned startSize = 3;
	HashTable* newTable = new HashTable(startSize);
	string binFileName = "test.bin";

	//тест 1 - добавление элемента без коллизии
	cout << "\n---Тест 1 - добавление элемента без коллизии-- - \n";
	string test1Key = "10.10";
	string test1Value = "Aaaa B.";
	newTable->add(test1Key.c_str(), test1Value.c_str(), 0);
	addRecord(binFileName, test1Key.c_str(), test1Value.c_str(), 0);
	if (strcmp(newTable->get(test1Key.c_str()), test1Value.c_str()) != 0)
	{
		throw std::exception("Ошибка в: Тест 1");
	}
	newTable->printTable();

	//тест 2 - добавление элемента с возникновением коллизии
	cout << "\n---Тест 2 - добавление элемента с возникновением коллизии---\n";
	string test2Key = "10.20";
	string test2Value = "Bbbb C.";
	newTable->add(test2Key.c_str(), test2Value.c_str(), 1);
	addRecord(binFileName, test2Key.c_str(), test2Value.c_str(), 1);
	if (strcmp(newTable->get(test2Key.c_str()), test2Value.c_str()) != 0)
	{
		throw std::exception("Ошибка в: Тест 2");
	}
	newTable->printTable();

	//тест 3 - добавление элемента с возникающих рехэшированием
	cout << "\n---Тест 3 - добавление элемента с возникающих рехэшированием---\n";
	string test3Key = "20.20";
	string test3Value = "Cccc D.";
	newTable->add(test3Key.c_str(), test3Value.c_str(), 2);
	addRecord(binFileName, test3Key.c_str(), test3Value.c_str(), 2);
	if (strcmp(newTable->get(test3Key.c_str()), test3Value.c_str()) != 0
		|| startSize * 2 != newTable->getSize())
	{
		throw std::exception("Ошибка в: Тест 3");
	}
	newTable->printTable();

	//тест 4 - получение элемента, который есть в таблице
	cout << "\n---Тест 4 - получение элемента, который есть в таблице---\n";

	string test4Key = "20.20";
	string test4Value = "Cccc D.";
	char* returnValue = getRecord(binFileName, newTable, test4Key.c_str());
	//strcpy_s(returnValue, getRecord(binFileName, newTable, test4Key.c_str()));

	if (strcmp(returnValue, test4Value.c_str()) != 0)
	{
		throw std::exception("Ошибка в: Тест 4");
	}
	cout << "найдено значение " << newTable->get(test4Key.c_str()) << '\n';

	//тест 5 - получение несуществующего элемента
	cout << "\n---Тест 5 - получение несуществующего элемента---\n";
	try
	{
		string test5Key = "30.30";
		getRecord(binFileName, newTable, test5Key.c_str());
		throw std::exception("Ошибка в: Тест 5");
	}
	catch (const std::exception& invArg)
	{
		//Всё нормально - метод вернул исключение о том, что ничего не нашел
		cout << "Ошибка: " << invArg.what() << '\n';
	}
	newTable->printTable();

	//тест 6 - удаление существующего элемента
	cout << "\n---Тест 6 - удаление существующего элемента---\n";
	try
	{
		string test6Key = "20.20";
		deleteRecordByKeyInBoth(binFileName, newTable, test6Key.c_str());
	}
	catch (const std::exception& invArg)
	{
		throw std::exception("Ошибка в: Тест 6");
	}
	newTable->printTable();

	//тест 7 - удаление несуществующего элемента
	cout << "\n---Тест 7 - удаление несуществующего элемента---\n";
	try
	{
		string test7Key = "30.30";
		deleteRecordByKeyInBoth(binFileName, newTable, test7Key.c_str());
		throw std::exception("Ошибка в: Тест 7");
	}
	catch (const std::exception& invArg)
	{
		//Всё нормально - метод вернул исключение о том, что ничего не нашел
		cout << "Ошибка: " << invArg.what() << '\n';
	}
	newTable->printTable();

	//тест 8 - получение элемента, располагающегося после удалённого элемента (с одинаковыми хэшами)
	cout << "\n---Тест 8 - получение элемента, располагающегося после удалённого элемента (с одинаковыми хэшами)---\n";
	string test8Key = "20.20";
	string test8Value = "Dddd E.";
	newTable->add(test8Key.c_str(), test8Value.c_str(), 3);
	addRecord(binFileName, test8Key.c_str(), test8Value.c_str(), 3);
	if (strcmp(getRecord(binFileName, newTable, test8Key.c_str()),
		test8Value.c_str()) != 0)
	{
		throw std::exception("Ошибка в: Тест 8");
	}
	newTable->printTable();

	cout << "Тестирование успешно!\n";
}
