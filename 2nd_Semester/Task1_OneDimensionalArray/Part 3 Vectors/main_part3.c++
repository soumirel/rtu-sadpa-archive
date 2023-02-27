#include <iostream>
#include <locale.h>
#include <vector>
using namespace std;


void printMenu(vector<long>& vec, bool isFilled);
void fillVector(vector<long>& vec, int size);
void printVector(vector<long>& vec, bool isFilled);
int findIndex(vector<long>& vec, long digit);
int findHighestDigit(int vaule);
int insertElement(vector<long>& vec, long element, int digit);
bool deleteElements(vector<long>& vec, int digit);


int main() {
	setlocale(LC_ALL, "Russian");
	//Главные переменные.
	vector<long> mainVector{};
	//Служебные переменные.
	int foundIndex;
	bool isVectorFilled = false;
	//Переменные для пользовательского ввода.
	int userSize = 0;
	int userСhoice = -1;
	int userDigit;
	long userElement;
	while (userСhoice != 0) { // Главный меню-цикл.
		printMenu(mainVector, isVectorFilled);
		cin >> userСhoice;
		switch (userСhoice) {
		case 1: // Кейс заполнения массива.
			cout << "Введите кол-во элементов в массиве: ";
			cin >> userSize;
			if (userSize <= 0) {
				cout << "Ошибка ввода размерности массива!\n";
			}
			else {
				cout << "Введите элементы массива: ";
				fillVector(mainVector, userSize);
				isVectorFilled = true;
			}
			system("pause");
			break;
		case 2: // Кейс поиска индекса.
			if (!isVectorFilled)
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			else {
				cout << "Введите искомую цифру:";
				cin >> userDigit;
				foundIndex = findIndex(mainVector, userDigit);
				if (foundIndex != -1)
					cout << "Искомый индекс: " << foundIndex << "\n";
				else
					cout << "Ничего не найдено :(\n";
			}
			system("pause");
			break;
		case 3: // Кейс вставки элемента.
			if (!isVectorFilled)
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			else {
				cout << "Введите цифру, по которой будет происходить поиск элемента: ";
				cin >> userDigit;
				cout << "Введите эллемент, который хотите вставить: ";
				cin >> userElement;
				if (insertElement(mainVector, userElement, userDigit) == -1) {
					cout << "По введённому значению ничего не найдено, некуда добавлять элемент :(\n";
				}
				else {
					cout << "Массив обновлён.\n";
				}

			}
			system("pause");
			break;
		case 4: //Кейс удаления элемента(ов).
			if (!isVectorFilled)
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			else {
				cout << "Введите цифру, по которой будет происходить выбор элементов: ";
				cin >> userDigit;
				if (deleteElements(mainVector, userDigit)) {
					cout << "Массив обновлён.\n";
				}
				else {
					cout << "По введённому значению ничего не найдено\n"
						"Нечего удалять.\n";
				}
				if (mainVector.size() == 0) {
					isVectorFilled = false;
					cout << "Вследстсвие удаления массив оказался пуст.\n";
				}
			}
			system("pause");
			break;
		case 0: // Кейс выхода.
			userСhoice = 0;
			cout << "До свидания!\n";
			system("pause");
			break;
		default:
			cout << "Я не понимаю вас, повторите ввод\n";
			system("pause");
			break;
		}
	}
	return 0;
}


/*
Процедура отображения меню и вектора.
Аргументы - 1) Вектор, вместе с которым выводится меню,
			2) Булево значение "заполнен ли вектор?"
*/
void printMenu(vector<long>& vec, bool isFilled) {
	system("cls");
	cout << "Практическая работа #1 ИКБО-03-21 Мазанов А.Е. Вариант 17\n\n"
		"Задание 3 - Вектор\n"
		"================Меню================\n";
	if (isFilled) {
		cout << "\n";
		printVector(vec, isFilled);
		cout << "\n";
	}
	else {
		cout << "\nТекущий массив: Пуст\n\n";
	}
	cout << "1) Заполнить массив\n"
		"2) Найти индекс элемента массива, старшая цифра значения которого равна заданной.\n"
		"3) Вставить новый элемент в массив перед элементом массива, старшая цифра значения которого равна заданной\n"
		"4) Удалить все элементы массива, старшая цифра значений которых равна заданной.\n"
		"0) Выход\n"
		"Ваш выбор: ";
}


/*
Процедура заполнения вектора.
Аргументы - 1) Вектор, который нужно заполнить,
			2) Размерность вектора,
*/
void fillVector(vector<long>& vec, int size) {
	vec.clear();
	long elem;
	for (int i = 0; i < size; i++) {
		cin >> elem;
		vec.push_back(elem);
	}
}


/*
Процедура вывода вектора в консоль.
Аргументы - 1) Вектора, который нужно вывести,
			2) Булево значение "заполнен ли вектор?".
*/
void printVector(vector<long>& vec, bool isFilled) {
	if (!isFilled)
		cout << "Ошибка! Массив пуст. Заполните массив и попробуйте снова.\n";
	else {
		cout << "Текущий массив: ";
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i] << " ";
		}
		cout << "\n";
	}
}


/*
Функция поиска индекса.
Аргументы - 1) Вектор, в котором происх. поиск,
			2) Цифра для поиска.
Возр.знач - 1) Индекс, если найден,
			2) -1 если не найден.
*/
int findIndex(vector<long>& vec, long digit) {
	for (int i = 0; i < vec.size(); i++) {
		if (findHighestDigit(vec[i]) == digit) {
			return i;
		}
	}
	return -1;
}


/*
Функция поиска старшей цифры числа.
Аргументы - 1) Число, в котором необходим поиск.
Возвр.знач - 1) Старшая цифра числа.
*/
int findHighestDigit(int vaule) {
	while (vaule > 9) {
		vaule /= 10;
	}
	return vaule;
}


/*
Функция вставки элемента в вектор.
Аргументы - 1) Вектор для вставки,
			2) Элемент для вставки,
			3) Цифра для поиска.
Возвр.знач - 1) Индекс куда вставлен элемент, если успех,
			 2) -1, если вставка не произошла.
*/
int insertElement(vector<long>& vec, long element, int digit) {
	int index = findIndex(vec, digit);
	if (index != -1) {
		vec.insert(vec.begin() + index, element);
	}
	return index;
}


/*
Процедура удаления элемента(ов) в векторе.
Аргументы - 1) Вектор для вставки,
			2) Цифра для поиска.
Возвр.знач - 1) true, если успех,
			 2) false, если не произошло удаление.
*/
bool deleteElements(vector<long>& vec, int digit) {
	bool isDeletedSmth = false;
	for (int i = 0; i < vec.size(); i++) {
		if (findHighestDigit(vec[i]) == digit) {
			vec.erase(vec.begin() + i);
			isDeletedSmth = true;
			i -= 1;
		}
	}
	return isDeletedSmth;
}