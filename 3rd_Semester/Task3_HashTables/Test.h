#pragma once

#include "Hash.h"
#include "Binary.h"
#include "HashBinary.h"

void testHeshT()
{
	unsigned startSize = 3;
	HashTable* newTable = new HashTable(startSize);
	string binFileName = "test.bin";

	//���� 1 - ���������� �������� ��� ��������
	cout << "\n---���� 1 - ���������� �������� ��� ��������-- - \n";
	string test1Key = "10.10";
	string test1Value = "Aaaa B.";
	newTable->add(test1Key.c_str(), test1Value.c_str(), 0);
	addRecord(binFileName, test1Key.c_str(), test1Value.c_str(), 0);
	if (strcmp(newTable->get(test1Key.c_str()), test1Value.c_str()) != 0)
	{
		throw std::exception("������ �: ���� 1");
	}
	newTable->printTable();

	//���� 2 - ���������� �������� � �������������� ��������
	cout << "\n---���� 2 - ���������� �������� � �������������� ��������---\n";
	string test2Key = "10.20";
	string test2Value = "Bbbb C.";
	newTable->add(test2Key.c_str(), test2Value.c_str(), 1);
	addRecord(binFileName, test2Key.c_str(), test2Value.c_str(), 1);
	if (strcmp(newTable->get(test2Key.c_str()), test2Value.c_str()) != 0)
	{
		throw std::exception("������ �: ���� 2");
	}
	newTable->printTable();

	//���� 3 - ���������� �������� � ����������� ��������������
	cout << "\n---���� 3 - ���������� �������� � ����������� ��������������---\n";
	string test3Key = "20.20";
	string test3Value = "Cccc D.";
	newTable->add(test3Key.c_str(), test3Value.c_str(), 2);
	addRecord(binFileName, test3Key.c_str(), test3Value.c_str(), 2);
	if (strcmp(newTable->get(test3Key.c_str()), test3Value.c_str()) != 0
		|| startSize * 2 != newTable->getSize())
	{
		throw std::exception("������ �: ���� 3");
	}
	newTable->printTable();

	//���� 4 - ��������� ��������, ������� ���� � �������
	cout << "\n---���� 4 - ��������� ��������, ������� ���� � �������---\n";

	string test4Key = "20.20";
	string test4Value = "Cccc D.";
	char* returnValue = getRecord(binFileName, newTable, test4Key.c_str());
	//strcpy_s(returnValue, getRecord(binFileName, newTable, test4Key.c_str()));

	if (strcmp(returnValue, test4Value.c_str()) != 0)
	{
		throw std::exception("������ �: ���� 4");
	}
	cout << "������� �������� " << newTable->get(test4Key.c_str()) << '\n';

	//���� 5 - ��������� ��������������� ��������
	cout << "\n---���� 5 - ��������� ��������������� ��������---\n";
	try
	{
		string test5Key = "30.30";
		getRecord(binFileName, newTable, test5Key.c_str());
		throw std::exception("������ �: ���� 5");
	}
	catch (const std::exception& invArg)
	{
		//�� ��������� - ����� ������ ���������� � ���, ��� ������ �� �����
		cout << "������: " << invArg.what() << '\n';
	}
	newTable->printTable();

	//���� 6 - �������� ������������� ��������
	cout << "\n---���� 6 - �������� ������������� ��������---\n";
	try
	{
		string test6Key = "20.20";
		deleteRecordByKeyInBoth(binFileName, newTable, test6Key.c_str());
	}
	catch (const std::exception& invArg)
	{
		throw std::exception("������ �: ���� 6");
	}
	newTable->printTable();

	//���� 7 - �������� ��������������� ��������
	cout << "\n---���� 7 - �������� ��������������� ��������---\n";
	try
	{
		string test7Key = "30.30";
		deleteRecordByKeyInBoth(binFileName, newTable, test7Key.c_str());
		throw std::exception("������ �: ���� 7");
	}
	catch (const std::exception& invArg)
	{
		//�� ��������� - ����� ������ ���������� � ���, ��� ������ �� �����
		cout << "������: " << invArg.what() << '\n';
	}
	newTable->printTable();

	//���� 8 - ��������� ��������, ���������������� ����� ��������� �������� (� ����������� ������)
	cout << "\n---���� 8 - ��������� ��������, ���������������� ����� ��������� �������� (� ����������� ������)---\n";
	string test8Key = "20.20";
	string test8Value = "Dddd E.";
	newTable->add(test8Key.c_str(), test8Value.c_str(), 3);
	addRecord(binFileName, test8Key.c_str(), test8Value.c_str(), 3);
	if (strcmp(getRecord(binFileName, newTable, test8Key.c_str()),
		test8Value.c_str()) != 0)
	{
		throw std::exception("������ �: ���� 8");
	}
	newTable->printTable();

	cout << "������������ �������!\n";
}
