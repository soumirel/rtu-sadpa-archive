#include <iostream>
#include <locale.h>
#include <malloc.h>
using namespace std;


void printMenu(long* array, int size, bool isFilled);
void fillArray(long* array, int size);
void printArray(long* array, int size, bool isFilled);
int findIndex(long* array, int size, long digit);
int findHighestDigit(int vaule);
long* insertElement(long* array, int size, long element, int digit);
long* deleteElements(long* array, int size, int digit);


int main() {
	setlocale(LC_ALL, "Russian");
	//Главные переменные.
	long* mainArray = 0;
	int actualSize = 0;
	//Служебные переменные.
	long numDeletedElems = 0;
	int foundIndex;
	bool isArrayFilled = false;
	//Переменные для пользовательского ввода.
	int userСhoice = -1;
	int userDigit;
	long userElement;
	while (userСhoice != 0) { // Главный меню-цикл.
		printMenu(mainArray, actualSize, isArrayFilled);
		cin >> userСhoice;
		switch (userСhoice) {
		case 1: // Кейс заполнения массива.
			cout << "Введите кол-во элементов в массиве: ";
			cin >> actualSize;
			if (actualSize <= 0) {
				cout << "Ошибка ввода размерности массива!\n";
			}
			else {
				cout << "Введите элементы массива: ";
				mainArray = new long[actualSize];
				fillArray(mainArray, actualSize);
				isArrayFilled = true;
			}
			system("pause");
			break;
		case 2: // Кейс поиска индекса.
			if (!isArrayFilled) {
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			}
			else {
				cout << "Введите искомую цифру:";
				cin >> userDigit;
				foundIndex = findIndex(mainArray, actualSize, userDigit);
				if (foundIndex != -1){
					cout << "Искомый индекс: " << foundIndex << "\n";
				}
				else{
					cout << "Ничего не найдено :(\n";
				}
			}
			system("pause");
			break;
		case 3: // Кейс вставки элемента.
			if (!isArrayFilled) 
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			else {
				cout << "Введите цифру, по которой будет происходить поиск элемента: ";
				cin >> userDigit;
				cout << "Введите эллемент, который хотите вставить: ";
				cin >> userElement;
				mainArray = insertElement(mainArray, actualSize, userElement, userDigit);
				numDeletedElems = actualSize - (_msize(mainArray) / sizeof(mainArray[0]));
				if (numDeletedElems != 0) {
					cout << "Массив обновлён.\n";
					actualSize += 1;
				}
				else {
					cout << "По введённому значению ничего не найдено, некуда добавлять элемент :(\n";
				}
			}
			system("pause");
			break;
		case 4: //Кейс удаления элемента(ов).
			if (!isArrayFilled) 
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			else {
				cout << "Введите цифру, по которой будет происходить выбор элементов: ";
				cin >> userDigit;
				mainArray = deleteElements(mainArray, actualSize, userDigit);
				if (mainArray != 0) {
					numDeletedElems = actualSize - (_msize(mainArray) / sizeof mainArray[0]);
					if (numDeletedElems != 0) {
						cout << "Массив обновлён.\n";
						actualSize -= numDeletedElems;
					}
					else {
						cout << "По введённому значению ничего не найдено\n"
							"Нечего удалять.\n";
					}
				}
				else {
					isArrayFilled = false;
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
Процедура отображения меню и массива.
Аргументы - 1) Массив, вместе с которым выводится меню,
			2) Размерность массива,
			3) Булево значение "заполнен ли массив?"
*/
void printMenu(long* array, int size, bool isFilled) {
	system("cls");
	cout << "Практическая работа #1 ИКБО-03-21 Мазанов А.Е. Вариант 17\n\n"
		"Задание 2 - Динамический массив\n"
		"================Меню================\n";
	if (isFilled && size != 0) {
		cout << "\n";
		printArray(array, size, isFilled);
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
Процедура заполнения массива.
Аргументы - 1) Массив, который нужно заполнить,
			2) Размерность массива,
*/
void fillArray(long* array, int size) {
	for (int i = 0; i < size; i++) {
		cin >> array[i];
	}
}


/*
Процедура вывода массива в консоль.
Аргументы - 1) Массив, который нужно вывести,
			2) Размерность массива,
			3) Булево значение "заполнен ли массив?".
*/
void printArray(long* array, int size, bool isFilled) {
	if (!isFilled) {
		cout << "Ошибка! Массив пуст. Заполните массив и попробуйте снова.\n";
	}
	else {
		cout << "Текущий массив: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}
		cout << "\n";
	}
}


/*
Функция поиска индекса.
Аргументы - 1) Массив, в котором происх. поиск,
			2) Размерность массива,
			3) Цифра для поиска.
Возр.знач - 1) Индекс, если найден,
			2) -1 если не найден.
*/
int findIndex(long* array, int size, long digit) {
	for (int i = 0; i < size; i++) {
		if (findHighestDigit(array[i]) == digit) {
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
Функция вставки элемента в массив.
Аргументы - 1) Массив для вставки,
			2) Ращзмерность массива,
			3) Элемент для вставки,
			4) Цифра для поиска.
Возвр.знач - 1) Указатель на новый массив.
*/
long* insertElement(long* array, int size, long element, int digit) {
	int index = findIndex(array, size, digit);
	if (index != -1) {
		array = (long*)realloc(array, sizeof(long) * (++size));
;		for (int i = size - 1; i >= index; i--) {
			array[i + 1] = array[i];
		}
		array[index] = element;
	}
	return array;
}

/*
Функция удаления элемента(ов) в массиве.
Аргументы - 1) Массив для вставки,
			2) Ращзмерность массива,
			3) Цифра для поиска.
Возвр.знач - 1) Указатель на новый массив, если имеет длину,
			 2) 0, если были удалены все элементы.
*/
long* deleteElements(long* array, int size, int digit) {
	int deletedCounter = 0;
	for (int i = 0; i < size; i++) {
		if (findHighestDigit(array[i]) == digit) {
			deletedCounter += 1;
			for (int k = i; k < size; k++) {
				array[k] = array[k + 1];
			}
			array = (long*)realloc(array, sizeof(long) * (--size));
			i -= 1;
		}
	}
	if (size != 0) {
		return array;
	}
	else {
		return 0;
	}
}